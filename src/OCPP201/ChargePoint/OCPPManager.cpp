#include "OCPPManager.hpp"


void OCPP201::OCPPManager::init() {
  auto zmqContext = std::make_shared<zmq::context_t>(2);
  this->mWebsocketDealerPtr = std::make_unique<MQDealer>(zmqContext, "inproc://CoreRouter", "OCPP201Worker");
  this->mWebsocketDealerPtr->init();

}



void OCPP201::OCPPManager::start() {

  this->mWebsocketDealerPtr->start();

}

void OCPP201::OCPPManager::receiveMessageHandler(const std::string & tMessage) {


}
