#include "OCPPManager.hpp"

bool OCPP201::OCPPManager::init()
{
  this->mConfigureManager.init();
  this->mMQRouterPtr->init();
  this->mThreadPoll = std::make_unique<ThreadPool>(5);
  this->mMQRouterPtr->setReceiveCallBack([this](const RouterProtobufMessage &tMessage)
                                         { this->receiveMessageHandler(tMessage); });

  // test connectors
  for (auto i = 0; i < 3; i++) {
    this->mEVSEs.emplace_back();
    this->mEVSEs.at(i).id = i;
  }
  return true;
}

void OCPP201::OCPPManager::start()
{
  this->mMQRouterPtr->start();
}
void OCPP201::OCPPManager::receiveMessageHandler(const RouterProtobufMessage &tMessage)
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
    if (!this->mOCPP201MessageManager->mBootNotificationManager.isBooting)
    {
      this->mOCPP201MessageManager->mBootNotificationManager.setConfigure(this->mConfigureManager.getBaseInfo());
      this->mThreadPoll->enqueue([this, tMessage]()
                                 {
                                   this->mOCPP201MessageManager->mBootNotificationManager.isBooting = true;
                                   this->mOCPP201MessageManager->mBootNotificationManager.bootFinish = true;
                                   // set dest
                                   this->mOCPP201MessageManager->mStatusNotificationManager.mDest = tMessage.source();
                                   this->mOCPP201MessageManager->mHeartBeatManager.mDest = tMessage.source();
                                   while (this->mOCPP201MessageManager->mBootNotificationManager.getBootInterval() && this->mOCPP201MessageManager->mBootNotificationManager.isBooting) {
                                     std::this_thread::sleep_for(std::chrono::seconds(1));
                                     this->send(this->mOCPP201MessageManager->mBootNotificationManager.getRequestMessage(tMessage.source()), [this](const std::string &tMessageConf)
                                                {
                                                  OCPP201::BootNotificationResponse bootNotificationResponse = nlohmann::json::parse(tMessageConf);
                                                  this->mOCPP201MessageManager->mBootNotificationManager.setBootInterval(bootNotificationResponse.getInterval());
                                                  switch (bootNotificationResponse.getStatus()) {
                                                  case OCPP201::RegistrationStatusEnumType::Accepted:
                                                    this->mOCPP201MessageManager->mBootNotificationManager.isBooting = false;
                                                    this->mOCPP201MessageManager->mBootNotificationManager.bootFinish = true;
                                                    // init heartbeat Timer
                                                    this->mOCPP201MessageManager->mHeartBeatManager.mInterval = bootNotificationResponse.getInterval();
                                                    this->mThreadPoll->enqueue([this](){
                                                      this->mOCPP201MessageManager->mHeartBeatManager.setHeartbeatHandler([&](){
                                                        this->send(this->mOCPP201MessageManager->mHeartBeatManager.getRequestMessage(), [this](const std::string &tMessageConf) {
                                                          //TODO heartbeat response

                                                        });
                                                      });
                                                      // start heartbeat timer
                                                      this->mOCPP201MessageManager->mHeartBeatManager.start();
                                                      // send statusnotification for each connector
                                                      std::for_each(this->mEVSEs.begin(), this->mEVSEs.end(), [this](const OCPP201::EVSE &tEVSE){
                                                        if (tEVSE.id!=0) {
                                                          std::for_each(tEVSE.mConnectors.begin(), tEVSE.mConnectors.end(), [this](const OCPP201::Connector &tConnector){
                                                            this->send(this->mOCPP201MessageManager->mStatusNotificationManager.getRequestMessage(tConnector), [](const std::string &tMessageConf){});
                                                          });
                                                        }
                                                      });

                                                      //TODO offline meesage

                                                    });
                                                    break;
                                                    // 1. To inform the Charging Station that it is not yet accepted by the CSMS: Pending status.
                                                    // 2. To give the CSMS a way to retrieve or set certain configuration information.
                                                    // 3. To give the CSMS a way of limiting the load on the CSMS after e.g. a reboot of the CSMS.
                                                  case OCPP201::RegistrationStatusEnumType::Pending:
                                                    this->mOCPP201MessageManager->mBootNotificationManager.isBooting = true;
                                                    this->mOCPP201MessageManager->mBootNotificationManager.bootFinish = false;
                                                    break;
                                                  case OCPP201::RegistrationStatusEnumType::Rejected:
                                                    this->mOCPP201MessageManager->mBootNotificationManager.isBooting = false;
                                                    this->mOCPP201MessageManager->mBootNotificationManager.bootFinish = false;
                                                    break;
                                                  }
                                                }
                                     );
                                   }
                                 });
    }
    break;
  case ROUTER_METHODS_NETWORK_OFFLINE:
    this->mOCPP201MessageManager->mBootNotificationManager.release();
    this->mOCPP201MessageManager->mHeartBeatManager.stop();
    break;
  default:
    break;
  }
}

void OCPP201::OCPPManager::OCPP201RequestHandler(const std::string &tUUID, OCPP201::OCPP201Type tType, const std::string &tMessage) {
  switch (tType) {
  case OCPP201::OCPP201Type::GetVariables:
    try {
      OCPP201::GetVariablesRequest getVariablesRequest = nlohmann::json::parse(tMessage);
      for (const auto &request : getVariablesRequest.getVariableData) {
      }
    } catch (std::exception &e) {

    }
    break;
  case OCPP201::OCPP201Type::SetVariables:
    try {
      OCPP201::SetVariablesRequest request = nlohmann::json::parse(tMessage);
//      request.
//      nlohmann::json tmpConfigJson = this->mConfigureManager.getVariables();
      for (OCPP201::SetVariableDataType types : request.setVariableData) {
//        if (tmpConfigJson.contains(types.))
      }
    } catch (std::exception &e) {
      this->sendOCPPError("websocket", OCPP::ProtocolError::InternalError, "Parse set variable failed");
    }
    break;
  case OCPP201::OCPP201Type::SetNetworkProfile:
//            SetNetworkProfileRequest request = nlohmann::json::parse(tMessage);
    break;
  default:
    break;
  }

}

void OCPP201::OCPPManager::OCPP201MessageHandler(const RouterProtobufMessage &tMessage)
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
          {
            // TODO message call process
          }
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
          {
            auto callback = this->mMessageCallback[messageConf->getMessageId()];
            {
              std::lock_guard<std::mutex> lock(this->mMessageTimeoutTraceMutex);
              // clear trace record
              this->mMessageCallback.erase(messageConf->getMessageId());
              this->mOCPPMessageType.erase(messageConf->getMessageId());
              std::for_each(this->mMessageTimeoutTrace.begin(), this->mMessageTimeoutTrace.end(), [&](const auto &entry)
              {
                if (std::equal(messageConf.value().getMessageId().begin(), messageConf.value().getMessageId().end(), entry.second.begin(), entry.second.end())) {
                  this->mMessageTimeoutTrace.erase(entry.first);
                  return;
                } });
            }
            if (callback)
              callback(messageConf->getPayload());
          }
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
    this->sendOCPPError(tMessage.source(), ProtocolError::FormatViolation, errorInfo);
  }
}

bool OCPP201::OCPPManager::sendOCPPError(const std::string &tResource, ProtocolError tError, const std::string &tDetail, std::function<void()> tCallback)
{
  RouterProtobufMessage routerProtobufMessage;
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
OCPP201::OCPPManager::OCPPManager(zmq::context_t *tContext,
                                  const std::string &tAddress)
{
  this->mMQRouterPtr = std::make_unique<MQDealer>(tContext, tAddress, "OCPP201");
}
bool OCPP201::OCPPManager::send(
    const RouterProtobufMessage &tMessage,
    std::function<void(const std::string &)> tCallback,
    bool isResponse)
{
  if (!this->mMessageCallback.contains(tMessage.uuid()))
  {
    if (!isResponse)
    {
      {
        std::lock_guard<std::mutex> lock(this->mMessageTimeoutTraceMutex);
        this->mMessageCallback[tMessage.uuid()] = tCallback;
        this->mMessageTimeoutTrace[std::chrono::system_clock::now()] = tMessage.uuid();
        if (tMessage.method() == RouterMethods::ROUTER_METHODS_OCPP201)
        {
//            std::cout << magic_enum::enum_cast<OCPP201Type>(tMessage.ocpp_type()).value() << std::endl << std::endl;
          this->mOCPPMessageType[tMessage.uuid()] = magic_enum::enum_cast<OCPP201::OCPP201Type>(tMessage.ocpp_type()).value();
        }
      }
    }
    this->mMQRouterPtr->send(tMessage);
    return true;
  }
  return false;
}

void OCPP201::OCPPManager::setBaseInfo(BaseInfoType tType, const std::string &tValue)
{
  switch (tType)
  {
  case BaseInfoType::Model:
    this->mConfigureManager.getBaseInfo().model = tValue;
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