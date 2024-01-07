#include "OCPPManager.hpp"


void OCPP201::OCPPManager::init() {
  auto zmqContext = std::make_shared<zmq::context_t>(2);
  this->mWebsocketDealerPtr = std::make_unique<MQDealer>(zmqContext, "inproc://CoreRouter", "OCPP201Worker");
  this->mWebsocketDealerPtr->init();
  this->mWebsocketDealerPtr->setReceiveCallBack([](const std::string& tResource, const std::string & tMessage){});

}



void OCPP201::OCPPManager::start() {

  this->mWebsocketDealerPtr->start();

}

void OCPP201::OCPPManager::receiveMessageHandler(const std::string &tResource,
                                                 const std::string & tMessage) {
  if (auto messageCall =
          mHelper.checkMessageReq(tMessage)  != std::nullopt) {
    auto t = messageCall;
  } else if (auto messageConf = this->mHelper.checkMessageConf(tMessage) != std::nullopt) {

  } else {
    RouterProtobufMessage routerProtobufMessage;
    routerProtobufMessage.set_resource(tResource);
    routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
    routerProtobufMessage.set_dest("websocket:"+tResource);
    MessageErrorResponse messageErrorResponse;
    messageErrorResponse.setErrorCode(ProtocolError::FormatViolation);
    messageErrorResponse.setErrorDescription("");
    nlohmann::json j = nlohmann::json::object();
    messageErrorResponse.setErrorDetails(j);
    routerProtobufMessage.set_data(messageErrorResponse.serializeMessage());
    this->mWebsocketDealerPtr->send(routerProtobufMessage);
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
