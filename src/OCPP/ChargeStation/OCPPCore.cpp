#include "OCPPCore.hpp"

OCPP::OCPPCore::OCPPCore(zmq::context_t *tContext,
                               const std::string &tAddress)
{
  this->mMQRouterPtr = std::make_unique<MQDealer>(tContext, tAddress, "OCPP");
}

bool OCPP::OCPPCore::init()
{
  this->mMQRouterPtr->init();
  this->mThreadPoll = std::make_shared<ThreadPool>(5);
  this->mMQRouterPtr->setReceiveCallBack([this](const InternalRouterMessage &tMessage)
                                         { this->receiveMessageHandler(tMessage); });

  // shared interface
  this->mOCPP201MessageManager->setSendMessage([this](RouterPackage &&tPackage) {
    this->send(tPackage);
  });
  this->mOCPP201MessageManager->setSendOCPPError([this](MessageErrorResponse &errorResponse, const ZMQIdentify &tSource){
    this->sendOCPPError(errorResponse, tSource);
  });
  this->mOCPP201MessageManager->setIsUUIDExist([this](const std::string &tUUID) -> bool {
    return this->isUUIDExist(tUUID);
                              });
  this->mOCPP201MessageManager->setThreadPoolRef(this->mThreadPoll);

  return true;
}

void OCPP::OCPPCore::start()
{
  this->mMQRouterPtr->start();
}
void OCPP::OCPPCore::receiveMessageHandler(const InternalRouterMessage &tMessage)
{
  switch (tMessage.method())
  {
  case ROUTER_METHODS_OCPP201:
    this->mThreadPoll->enqueue([this, tMessage]()
                               { this->OCPP201MessageHandler(tMessage); });
    break;
  case ROUTER_METHODS_WRITE_DATABASE:
    break;
  case ROUTER_METHODS_READ_DATABASE:
    break;
  case ROUTER_METHODS_NETWORK_ONLINE:
    if (this->mOCPP201MessageManager == nullptr) {
      this->mOCPP201MessageManager = std::make_unique<OCPP201::MessageManager>();
    }
    this->mOCPP201MessageManager->bootHandler(tMessage);
    break;
  case ROUTER_METHODS_NETWORK_OFFLINE:
//    this->mOCPP201MessageManager->mBootNotificationManager.release();
//    this->mOCPP201MessageManager->mHeartbeatManager.stop();
    break;
  default:
    break;
  }
}

void OCPP::OCPPCore::OCPP201RequestHandler(const std::string &tUUID, const ZMQIdentify tSource, OCPP201::OCPP201Type tType, const std::string &tMessage ) {
  switch (tType) {
  case OCPP201::OCPP201Type::GetBaseReport:
    this->mOCPP201MessageManager->getBaseReportHandler(tUUID,tSource,tMessage);
    break;
  case OCPP201::OCPP201Type::GetVariables:
    this->mOCPP201MessageManager->getVariableHandler(tUUID,tSource,tMessage);
    break;
  case OCPP201::OCPP201Type::SetVariables:
    this->mOCPP201MessageManager->setVariableHandler(tUUID, tSource,tMessage);
    break;
  case OCPP201::OCPP201Type::SetNetworkProfile:
//            SetNetworkProfileRequest request = nlohmann::json::parse(tMessage);
    break;
  default:
    break;
  }

}

void OCPP::OCPPCore::OCPP201MessageHandler(const InternalRouterMessage &tMessage)
{
  std::string errorInfo;
  if (tMessage.message_type() == ::MessageType::REQUEST)
  {
    if (auto messageCall = mHelper.checkMessageReq(tMessage.ocpp_data().data()); messageCall.has_value())
    {
      auto checkAction =
          magic_enum::enum_cast<OCPP201::OCPP201Type>(messageCall->getAction());
      if (checkAction.has_value())
      {
        if (auto result = this->mHelper.checkOCPPJsonSchema(
              checkAction.value(), messageCall->getPayload(),
              OCPP201::MessageMethod::Request);
            result.has_value() && result.value().empty())
        {
          this->OCPP201RequestHandler(tMessage.uuid(), tMessage.source(), checkAction.value(), messageCall->getPayload());
        }
        else
        {
          errorInfo = result.value();
        }
      }
      else
      {
        errorInfo = "Invalid Action key -> " +
                    messageCall->getAction();
      }
    }
    else
    {
      errorInfo = "Request message format error";
    }
  }
  else if (tMessage.message_type() == ::MessageType::RESPONSE)
  {
    if (auto messageConf = this->mHelper.checkMessageConf(tMessage.ocpp_data().data()); messageConf.has_value())
    {
      if (this->mRouterPackagesTrace.contains(messageConf.value().getMessageId()))
      {
        if (auto result = this->mHelper.checkOCPPJsonSchema(this->mOCPPMessageType[messageConf.value().getMessageId()], messageConf.value().getPayload(), OCPP201::MessageMethod::Response);
            result.has_value() && result.value().empty())
        {
          auto callback = this->mRouterPackagesTrace[messageConf->getMessageId()].tGetReturnSuccessCallback;

          if (callback)
            callback(messageConf->getPayload());
        }
        else
        {
          errorInfo = result.value();
        }
      }
    }
    else
    {
      errorInfo = "Response message format error";
    }
  }
  if (!errorInfo.empty())
  {
    MessageErrorResponse messageErrorResponse;
    messageErrorResponse.setMessageId(tMessage.uuid());
    messageErrorResponse.setErrorDetails(nlohmann::json::object());
    messageErrorResponse.setErrorDescription(errorInfo);
    messageErrorResponse.setErrorCode(ProtocolError::FormatViolation);
    this->sendOCPPError(messageErrorResponse, tMessage.source());
  }
}

bool OCPP::OCPPCore::sendOCPPError(MessageErrorResponse &tErrorResponse, const ZMQIdentify tDest)
{
  InternalRouterMessage routerProtobufMessage;
  routerProtobufMessage.set_uuid(tErrorResponse.getMessageId());
  routerProtobufMessage.set_source(ZMQIdentify::ocpp);
  routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
  routerProtobufMessage.set_dest(tDest);
  routerProtobufMessage.set_message_type(::MessageType::RESPONSE);
  routerProtobufMessage.mutable_ocpp_data()->set_data(tErrorResponse.serializeMessage());

  this->mMQRouterPtr->send(routerProtobufMessage);
  return true;
}
void OCPP::OCPPCore::send(RouterPackage &&tPackage) {
  if (!this->mRouterPackagesTrace.contains(tPackage.message.uuid())) {
    {
      std::lock_guard<std::mutex> lock(this->mMessageTimeoutTraceMutex);
      if (tPackage.message.method() == RouterMethods::ROUTER_METHODS_OCPP201)
      {
        this->mOCPPMessageType[tPackage.message.uuid()] = magic_enum::enum_cast<OCPP201::OCPP201Type>(tPackage.message.ocpp_data().ocpp_type()).value();
      }
      this->mMessageTimeoutTrace[std::chrono::system_clock::now()] = tPackage.message.uuid();
      this->mRouterPackagesTrace[tPackage.message.uuid()] = std::move(tPackage);
    }
  } else {
    {
      // response message
      std::lock_guard<std::mutex> lock(this->mMessageTimeoutTraceMutex);
      // clear trace record
      this->mRouterPackagesTrace.erase(tPackage.message.uuid());
      if (tPackage.message.method() == RouterMethods::ROUTER_METHODS_OCPP201) {
        this->mOCPPMessageType.erase(tPackage.message.uuid());
      }
      std::for_each(this->mMessageTimeoutTrace.begin(), this->mMessageTimeoutTrace.end(), [&](const auto &entry)
      {
        if (std::equal(tPackage.message.uuid().begin(), tPackage.message.uuid().end(), entry.second.begin(), entry.second.end())) {
          this->mMessageTimeoutTrace.erase(entry.first);
        } });
    }
  }
  this->mMQRouterPtr->send(tPackage.message);

}
void OCPP::OCPPCore::send(RouterPackage &tPackage) {
  this->send(std::move(tPackage));
}
//bool OCPP::OCPPCore::send(
//    const InternalRouterMessage &tMessage,
//    std::function<void(const std::string &)> tCallback)
//{
//  // request message
//  if (!this->mMessageCallback.contains(tMessage.uuid()))
//  {
//    {
//      std::lock_guard<std::mutex> lock(this->mMessageTimeoutTraceMutex);
//      this->mMessageCallback[tMessage.uuid()] = tCallback;
//      this->mMessageTimeoutTrace[std::chrono::system_clock::now()] = tMessage.uuid();
//      if (tMessage.method() == RouterMethods::ROUTER_METHODS_OCPP201)
//      {
//        this->mOCPPMessageType[tMessage.uuid()] = magic_enum::enum_cast<OCPP201::OCPP201Type>(tMessage.ocpp_data().ocpp_type()).value();
//      }
//    }
//  } else {
//    {
//      // response message
//      std::lock_guard<std::mutex> lock(this->mMessageTimeoutTraceMutex);
//      // clear trace record
//      this->mMessageCallback.erase(tMessage.uuid());
//      this->mOCPPMessageType.erase(tMessage.uuid());
//      std::for_each(this->mMessageTimeoutTrace.begin(), this->mMessageTimeoutTrace.end(), [&](const auto &entry)
//      {
//        if (std::equal(tMessage.uuid().begin(), tMessage.uuid().end(), entry.second.begin(), entry.second.end())) {
//          this->mMessageTimeoutTrace.erase(entry.first);
//        } });
//    }
//  }
//  this->mMQRouterPtr->send(tMessage);
//  return false;
//}

void OCPP::OCPPCore::setBaseInfo(BaseInfoType tType, const std::string &tValue)
{
  switch (tType)
  {
  case BaseInfoType::Model:
//    this->mConfigureManager.getBaseInfo().model = tValue;
    // this->mBaseConfigureInfo.model = tValue;
    break;
    //  case BaseInfoType::VendorName:
    //    this->mBaseConfigureInfo.vendorName = tValue;
    //    break;
    //  case BaseInfoType::SerialNumber:
    //    this->mBaseConfigureInfo.serialNumber = tValue;
    //    break;
    //  case BaseInfoType::FirmwareVersion:
    //    this->mBaseConfigureInfo.firmwareVersion = tValue;
    //    break;
  default:
    break;
  }
  this->mThreadPoll->enqueue([this]()
                             {
                               // this->mHelper->writeToFile()
                             });
}
bool OCPP::OCPPCore::isUUIDExist(const std::string & tUUID) {
  return this->mRouterPackagesTrace.contains(tUUID);
}
