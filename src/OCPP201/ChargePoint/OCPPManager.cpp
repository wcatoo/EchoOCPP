#include "OCPPManager.hpp"


void OCPP201::OCPPManager::init() {
  auto zmqContext = std::make_shared<zmq::context_t>(2);
  this->mWebsocketDealerPtr = std::make_unique<MQDealer>(zmqContext.get(), "inproc://CoreRouter", "OCPP201Worker");
  this->mWebsocketDealerPtr->init();
  this->mThreadPoll = std::make_unique<ThreadPool>(5);

  this->mWebsocketDealerPtr->setReceiveCallBack([this](const std::string& tResource, const std::string & tMessage){
    if (tResource.find("websocket")) {
      this->receiveMessageHandler(tResource, tMessage);
    }
  });
}



void OCPP201::OCPPManager::start() {
  this->mWebsocketDealerPtr->start();
}

void OCPP201::OCPPManager::receiveMessageHandler(const std::string &tResource,
                                                 const std::string & tMessage) {
  if (auto messageCall = mHelper.checkMessageReq(tMessage); messageCall.has_value()) {
    auto checkAction = magic_enum::enum_cast<OCPP201Type>(messageCall->getAction());
    if (checkAction.has_value()) {
      if (auto result = this->mHelper.checkOCPPJsonSchema(checkAction.value(), messageCall->getPayload(), MessageMethod::Request);
          result.has_value() && result.value().empty()){
        {
          // TODO message call process

        }
      } else {
        this->sendOCPPError(tResource, ProtocolError::FormatViolation, result.value());
      }
    } else {
      this->sendOCPPError(tResource, ProtocolError::FormatViolation, "Invalid Action key -> " + messageCall->getAction());
    }
  } else if (auto messageConf = this->mHelper.checkMessageConf(tMessage); messageConf.has_value()) {
    if (this->mMessagesTrace.contains(messageConf.value().getMessageId())) {
      if (auto result = this->mHelper.checkOCPPJsonSchema(this->mMessagesTrace[messageConf.value().getMessageId()].first, messageConf.value().getPayload(), MessageMethod::Response);
          result.has_value() && result.value().empty()){
        {
          auto callback = this->mMessagesTrace[messageConf->getMessageId()].second;
          {
            std::lock_guard<std::mutex> lock(this->mMessageTimeoutTraceMutex);
            this->mMessagesTrace.erase(messageConf->getMessageId());
            std::for_each(this->mMessageTimeoutTrace.begin(), this->mMessageTimeoutTrace.end(), [&](const auto &entry){
              if (std::equal(messageConf.value().getMessageId().begin(), messageConf.value().getMessageId().end(), entry.second.begin(), entry.second.end())) {
                this->mMessageTimeoutTrace.erase(entry.first);
                return;
              }
            });
          }
          if (callback) {
            callback();
          }
        }
      } else {
        this->sendOCPPError(tResource, ProtocolError::FormatViolation, result.value());
      }
    }
  } else {
    this->sendOCPPError(tResource, ProtocolError::FormatViolation, "");
    return;
  }
}
bool OCPP201::OCPPManager::send(OCPP201Type tType, MessageCall *tCall, std::function<void()> tCallback) {
  if (tCall == nullptr) {
    return false;
  }
  if (!this->mMessagesTrace.contains(tCall->getMessageId())) {
    {
      std::lock_guard<std::mutex> lock(this->mMessageTimeoutTraceMutex);
      this->mMessagesTrace[tCall->getMessageId()] = std::pair<OCPP201Type, std::function<void()>>(tType, tCallback);
      this->mMessageTimeoutTrace[std::chrono::system_clock::now()] = tCall->getMessageId();
    }
    this->mWebsocketDealerPtr->send(tCall->serializeMessage());
    return true;
  }
  return false;
}
bool OCPP201::OCPPManager::sendOCPPError(const std::string & tResource, ProtocolError tError, const std::string &tDetail, std::function<void()> tCallback) {
  RouterProtobufMessage routerProtobufMessage;
  routerProtobufMessage.set_source(tResource);
  routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
  routerProtobufMessage.set_dest("websocket:"+tResource);
  MessageErrorResponse messageErrorResponse;
  messageErrorResponse.setErrorCode(ProtocolError::FormatViolation);
  messageErrorResponse.setErrorDescription(tDetail);
  nlohmann::json j = nlohmann::json::object();
  messageErrorResponse.setErrorDetails(j);
  routerProtobufMessage.set_data(messageErrorResponse.serializeMessage());
  this->mWebsocketDealerPtr->send(routerProtobufMessage);
  return true;
}
