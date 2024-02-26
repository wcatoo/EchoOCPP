#include "OCPPManager.hpp"

OCPP::OCPPManager::OCPPManager(zmq::context_t *tContext,
                               const std::string &tAddress)
{
  this->mMQRouterPtr = std::make_unique<MQDealer>(tContext, tAddress, "OCPP201");
}

bool OCPP::OCPPManager::init()
{
  this->mMQRouterPtr->init();
  this->mThreadPoll = std::make_shared<ThreadPool>(5);
  this->mMQRouterPtr->setReceiveCallBack([this](const RouterProtobufMessage &tMessage)
                                         { this->receiveMessageHandler(tMessage); });

  // test connectors
  for (auto i = 0; i < 3; i++) {
    this->mEVSEs.emplace_back();
    this->mEVSEs.at(i).id = i;
  }

  // shared interface
  this->mOCPP201MessageManager->setSendMessage([this](const RouterProtobufMessage& message, std::function<void(const std::string&)> callback) {
    this->send(message,callback);
  });
  this->mOCPP201MessageManager->setThreadPoolRef(this->mThreadPoll);

  return true;
}

void OCPP::OCPPManager::start()
{
  this->mMQRouterPtr->start();
}
void OCPP::OCPPManager::receiveMessageHandler(const RouterProtobufMessage &tMessage)
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
  case ROUTER_METHODS_NOTIFY_REALTIME_DATA:
    break;
  case ROUTER_METHODS_GET_REALTIME_DATA:
    break;
  case ROUTER_METHODS_NETWORK_ONLINE:
    if (this->mOCPP201MessageManager == nullptr) {
      this->mOCPP201MessageManager = std::make_unique<OCPP201::MessageManager>();
    }
    this->mOCPP201MessageManager->bootHandler(tMessage);
    break;
  case ROUTER_METHODS_NETWORK_OFFLINE:
    this->mOCPP201MessageManager->mBootNotificationManager.release();
    this->mOCPP201MessageManager->mHeartbeatManager.stop();
    break;
  default:
    break;
  }
}

void OCPP::OCPPManager::OCPP201RequestHandler(const std::string &tUUID, const std::string &tSource, OCPP201::OCPP201Type tType, const std::string &tMessage ) {
  switch (tType) {
  case OCPP201::OCPP201Type::GetBaseReport:
//    try {
//      OCPP201::GetBaseReportRequest getBaseReportRequest = nlohmann::json::parse(tMessage);
//      OCPP201::GetBaseReportResponse response;
//      if (getBaseReportRequest.getReportBase() == OCPP201::ReportBaseEnumType::SummaryInventory) {
//        //TODO summary reject
//        response.status = OCPP201::GenericDeviceModelStatusEnumType::Rejected;
//      } else {
//        this->mThreadPoll->enqueue([this,tSource,&getBaseReportRequest]() {
//          auto configNum = this->mConfigureManager.getVariableManager().mComponentManager.componentVariable.size();
//          int seqBegin = 0;
//          RouterProtobufMessage routerProtobufMessage;
//          routerProtobufMessage.set_source("OCPP201");
//          routerProtobufMessage.set_dest(tSource);
//          routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
//          routerProtobufMessage.set_message_type(MessageType::REQUEST);
//          routerProtobufMessage.set_ocpp_type("NotifyReport");
//          while (seqBegin < configNum) {
//            auto result = this->mConfigureManager.getVariableManager().getNotifyRequestInventory(getBaseReportRequest.getRequestId(), seqBegin,
//                                                                                                 seqBegin + 4 >= configNum, getBaseReportRequest.getReportBase());
//            routerProtobufMessage.set_data(result.serializeMessage());
//            routerProtobufMessage.set_uuid(result.getMessageId());
//            this->send(routerProtobufMessage);
//            seqBegin += 4;
//          }
//        });
//        response.status = OCPP201::GenericDeviceModelStatusEnumType::Accepted;
//      }
//      response.setMessageId(tUUID);
//      response.setPayload(Utility::toJsonString<OCPP201::GetBaseReportResponse>(response));
//      RouterProtobufMessage routerProtobufMessage;
//      routerProtobufMessage.set_uuid(tUUID);
//      routerProtobufMessage.set_source("OCPP201");
//      routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
//      routerProtobufMessage.set_ocpp_type("GetBaseReport");
//      routerProtobufMessage.set_dest(tSource);
//      routerProtobufMessage.set_data(response.serializeMessage());
//      this->send(routerProtobufMessage, [](const std::string &t){});
//    } catch (std::exception &e) {
//      this->sendOCPPError(tUUID, tSource, ProtocolError::InternalError,"GetBaseReportRequest parse failed");
//    }
    break;
  case OCPP201::OCPP201Type::GetVariables:
//    try {
//      OCPP201::GetVariablesRequest getVariablesRequest = nlohmann::json::parse(tMessage);
//      OCPP201::ComponentType componentType("DeviceDataCtrlr");
//      OCPP201::VariableType variableType("ItemsPerMessage", "GetVariables");
//      int numMessageGetVariable;
//      std::string numMessageGetVariableStr;
//      try {
//        numMessageGetVariableStr = this->mConfigureManager.getVariableManager().getVariableAttributeValue(componentType, variableType, OCPP201::AttributeEnumType::Actual);
//        numMessageGetVariable = std::stoi(numMessageGetVariableStr);
//      } catch (std::exception &e) {
//        numMessageGetVariable = 0;
//      }
//      if (getVariablesRequest.getVariableData.size() > numMessageGetVariable) {
//        this->sendOCPPError(tUUID, tSource, ProtocolError::OccurrenceConstraintViolation,"The number should be less than " + numMessageGetVariableStr + "; The number of requesting is " + std::to_string(getVariablesRequest.getVariableData.size()));
//        return;
//      } else if (numMessageGetVariable == 0) {
//        this->sendOCPPError(tUUID, tSource, ProtocolError::InternalError,"ItemsPerMessageNumber should not equal to 0");
//        return;
//      }
//      auto result = this->mConfigureManager.getVariableManager().getVariableRequestHandler(getVariablesRequest);
//      result.setMessageId(tUUID);
//      result.setPayload(Utility::toJsonString<OCPP201::GetVariablesResponse>(result));
//      RouterProtobufMessage routerProtobufMessage;
//      routerProtobufMessage.set_uuid(tUUID) ;
//      routerProtobufMessage.set_dest(tSource);
//      routerProtobufMessage.set_message_type(MessageType::RESPONSE);
//      routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
//      routerProtobufMessage.set_data(result.serializeMessage());
//      routerProtobufMessage.set_ocpp_type("GetVariable");
//      this->send(routerProtobufMessage,[](const std::string &t){});
//    } catch (std::exception &e) {
//      this->sendOCPPError(tUUID, tSource, ProtocolError::InternalError,"ItemsPerMessageNumber is loss or parse failed");
//    }
    break;
  case OCPP201::OCPP201Type::SetVariables:
    try {
//      auto result = this->

    } catch (std::exception &e) {
//      this->sendOCPPError(tUUID, OCPP::ProtocolError::InternalError, "Parse set variable failed");
    }
    break;
  case OCPP201::OCPP201Type::SetNetworkProfile:
//            SetNetworkProfileRequest request = nlohmann::json::parse(tMessage);
    break;
  default:
    break;
  }

}

void OCPP::OCPPManager::OCPP201MessageHandler(const RouterProtobufMessage &tMessage)
{
  std::string errorInfo;
  if (tMessage.message_type() == ::MessageType::REQUEST)
  {
    if (auto messageCall = mHelper.checkMessageReq(tMessage.data()); messageCall.has_value())
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
    if (auto messageConf = this->mHelper.checkMessageConf(tMessage.data()); messageConf.has_value())
    {
      if (this->mMessageCallback.contains(messageConf.value().getMessageId()))
      {
        if (auto result = this->mHelper.checkOCPPJsonSchema(this->mOCPPMessageType[messageConf.value().getMessageId()], messageConf.value().getPayload(), OCPP201::MessageMethod::Response);
            result.has_value() && result.value().empty())
        {
          auto callback = this->mMessageCallback[messageConf->getMessageId()];

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
    this->sendOCPPError(tMessage.uuid(), tMessage.source(), ProtocolError::FormatViolation, errorInfo);
  }
}

bool OCPP::OCPPManager::sendOCPPError(const std::string &tUUID, const std::string &tResource, ProtocolError tError, const std::string &tDetail, std::function<void()> tCallback)
{
  RouterProtobufMessage routerProtobufMessage;
  routerProtobufMessage.set_uuid(tUUID);
  routerProtobufMessage.set_source(tResource);
  routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
  routerProtobufMessage.set_dest(tResource);
  routerProtobufMessage.set_message_type(::MessageType::REQUEST);
  MessageErrorResponse messageErrorResponse;
  messageErrorResponse.setErrorCode(ProtocolError::FormatViolation);
  messageErrorResponse.setErrorDescription(tDetail);
  nlohmann::json j = nlohmann::json::object();
  messageErrorResponse.setErrorDetails(j);
  routerProtobufMessage.set_uuid(messageErrorResponse.getMessageId());
  routerProtobufMessage.set_data(messageErrorResponse.serializeMessage());
  this->mMQRouterPtr->send(routerProtobufMessage);
  return true;
}

bool OCPP::OCPPManager::send(
    const RouterProtobufMessage &tMessage,
    std::function<void(const std::string &)> tCallback)
{
  if (!this->mMessageCallback.contains(tMessage.uuid()))
  {
    {
      std::lock_guard<std::mutex> lock(this->mMessageTimeoutTraceMutex);
      this->mMessageCallback[tMessage.uuid()] = tCallback;
      this->mMessageTimeoutTrace[std::chrono::system_clock::now()] = tMessage.uuid();
      if (tMessage.method() == RouterMethods::ROUTER_METHODS_OCPP201)
      {
        this->mOCPPMessageType[tMessage.uuid()] = magic_enum::enum_cast<OCPP201::OCPP201Type>(tMessage.ocpp_type()).value();
      }
    }
  } else {
    {
      std::lock_guard<std::mutex> lock(this->mMessageTimeoutTraceMutex);
      // clear trace record
      this->mMessageCallback.erase(tMessage.uuid());
      this->mOCPPMessageType.erase(tMessage.uuid());
      std::for_each(this->mMessageTimeoutTrace.begin(), this->mMessageTimeoutTrace.end(), [&](const auto &entry)
      {
        if (std::equal(tMessage.uuid().begin(), tMessage.uuid().end(), entry.second.begin(), entry.second.end())) {
          this->mMessageTimeoutTrace.erase(entry.first);
        } });
    }
  }
  this->mMQRouterPtr->send(tMessage);
  return false;
}

void OCPP::OCPPManager::setBaseInfo(BaseInfoType tType, const std::string &tValue)
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