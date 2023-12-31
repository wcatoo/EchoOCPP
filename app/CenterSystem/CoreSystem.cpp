#include "CoreSystem.hpp"

CenterSystem::CoreSystem::CoreSystem() {

}

void CenterSystem::CoreSystem::init() {
  auto zmqContext = std::make_shared<zmq::context_t>(1);
  this->mCoreRouterPtr = std::make_unique<MQRouter>(zmqContext, "tcp://*:5556", "CoreRouter");
  this->mCoreRouterPtr->addWorker("OCPP201", [](RouterProtobufMessage t){std::cout << "test add worker" << std::endl;});
  this->mWebsocketServer = std::make_unique<Components::WebsocketServer>();
  this->mWebsocketServer->setOnOpen([](){std::cout << "Server open" << std::endl;});
  this->mWebsocketServer->setOnMessage([](const std::string &tMessage){
  });
}


void CenterSystem::CoreSystem::run() {
  this->mCoreRouterPtr->init();
  this->mWebsocketServer->init();
  std::thread threadWebsocket([this](){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    this->mWebsocketServer->run();
  });
  threadWebsocket.detach();
}