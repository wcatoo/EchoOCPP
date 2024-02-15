#include "OCPPManager.hpp"

bool OCPP201::OCPPManager::init()
{
  this->mConfigureManager.init();
  this->mMQRouterPtr->init();
  this->mThreadPoll = std::make_unique<ThreadPool>(5);
  this->mMQRouterPtr->setReceiveCallBack([this](const RouterProtobufMessage &tMessage)
                                         { this->receiveMessageHandler(tMessage); });

  this->mBootNotificationManager = std::make_unique<BootNotificationManager>(this->mConfigureManager.getBaseInfo().model, this->mConfigureManager.getBaseInfo().vendorName);
  // test connectors
  for (auto i = 0; i < 3; i++) {
      this->mConnectors.emplace_back();
  }
  return true;
}

void OCPP201::OCPPManager::start()
{
  this->mMQRouterPtr->start();
}
void OCPP201::OCPPManager::receiveMessageHandler(const RouterProtobufMessage &tMessage)
{
    std::cout <<"OCPP201 <<< " << tMessage.data() << std::endl;

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
    if (this->mBootNotificationManager->isBooting == false)
    {
      this->mThreadPoll->enqueue([this, tMessage]()
                                 {
                                   this->mBootNotificationManager->isBooting = true;
                                   this->mBootNotificationManager->bootFinish = false;
                                   // set dest
                                   this->mStatusNotificationManager.mDest = tMessage.source();
                                    this->mHeartbeatManager.mDest = tMessage.source();
                                     while (this->mBootNotificationManager->getBootInterval() && this->mBootNotificationManager->isBooting) {
                                       std::this_thread::sleep_for(std::chrono::seconds(1));
                                     this->send(this->mBootNotificationManager->getRequestMessage(tMessage.source()), [this](const std::string &tMessageConf)
                                     {
                                       BootNotificationResponse bootNotificationResponse = nlohmann::json::parse(tMessageConf);
                                       this->mBootNotificationManager->setBootInterval(bootNotificationResponse.getInterval());
                                       switch (bootNotificationResponse.getStatus()) {
                                       case RegistrationStatusEnumType::Accepted:
                                         this->mBootNotificationManager->isBooting = false;
                                         this->mBootNotificationManager->bootFinish = true;
                                         // init heartbeat Timer
                                         this->mHeartbeatManager.mInterval = bootNotificationResponse.getInterval();
                                         this->mThreadPoll->enqueue([this](){
                                          this->mHeartbeatManager.setHeartbeatHandler([&](){
                                            this->send(this->mHeartbeatManager.getRequestMessage(), [this](const std::string &tMessageConf) {
                                              //TODO heartbeat response

                                            });
                                          });
                                          // start heartbeat timer
                                          this->mHeartbeatManager.start();
                                          // send statusnotification for each connector
                                          std::for_each(this->mConnectors.begin(), this->mConnectors.end(), [this](const Connector &tConnector){
                                            this->send(this->mStatusNotificationManager.getRequestMessage(tConnector), [](const std::string &tMessageConf){});
                                          });

                                          //TODO offline meesage

                                          });
                                         break;
                                         // 1. To inform the Charging Station that it is not yet accepted by the CSMS: Pending status.
                                         // 2. To give the CSMS a way to retrieve or set certain configuration information.
                                         // 3. To give the CSMS a way of limiting the load on the CSMS after e.g. a reboot of the CSMS.
                                       case RegistrationStatusEnumType::Pending:
                                         this->mBootNotificationManager->isBooting = true;
                                         this->mBootNotificationManager->bootFinish = false;
                                         break;
                                       case RegistrationStatusEnumType::Rejected:
                                         this->mBootNotificationManager->isBooting = false;
                                         this->mBootNotificationManager->bootFinish = false;
                                         break;
                                       }
                                     }
                                     );
                                   }
                                   });
    }
    break;
  case ROUTER_METHODS_NETWORK_OFFLINE:
    this->mBootNotificationManager.release();
    this->mHeartbeatManager.stop();
    break;
  default:
    break;
  }
}

void OCPP201::OCPPManager::OCPP201RequestHandler(const std::string &tUUID, OCPP201Type tType, const std::string &tMessage) {
    switch (tType) {
        case OCPP201Type::SetVariables:
            break;
        case OCPP201Type::SetNetworkProfile:
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
          magic_enum::enum_cast<OCPP201Type>(messageCall->getAction());
      if (checkAction.has_value())
      {
        if (auto result = this->mHelper.checkOCPPJsonSchema(
                checkAction.value(), messageCall->getPayload(),
                MessageMethod::Request);
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
        if (auto result = this->mHelper.checkOCPPJsonSchema(this->mOCPPMessageType[messageConf.value().getMessageId()], messageConf.value().getPayload(), MessageMethod::Response);
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
          this->mOCPPMessageType[tMessage.uuid()] = magic_enum::enum_cast<OCPP201Type>(tMessage.ocpp_type()).value();
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