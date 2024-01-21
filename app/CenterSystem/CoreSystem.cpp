#include "CoreSystem.hpp"

CenterSystem::CoreSystem::CoreSystem() {

}

void CenterSystem::CoreSystem::init() {
//  auto zmqContext = make_shared<zmq::context_t>(1);
//  this->mCoreRouterPtr = std::make_unique<MQRouter>(zmqContext, "inproc://coreRouter", "CoreRouter");
//  this->mCoreRouterPtr->addWorker("OCPP201", [](RouterProtobufMessage t){std::cout << "test add worker" << std::endl;});
//  this->mWebsocketDealerPtr = std::make_unique<MQDealer>(zmqContext, "inproc://coreRouter", "Websocket");
  this->mWebsocketDealerPtr->init();
  this->mWebsocketServer = std::make_unique<Components::WebsocketServer>();
  this->mWebsocketServer->setOnOpen([this](){

  });
  this->mWebsocketServer->setOnMessage([this](Components::WebsocketOnMessageInfo tMessage){
    RouterProtobufMessage routerProtobufMessage;
    routerProtobufMessage.set_dest("OCPP201");
    routerProtobufMessage.set_data(tMessage.getPayload());
    routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
    routerProtobufMessage.set_resource("/");

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
  std::thread websocketDealerThread([this]() { this->mWebsocketDealerPtr->start();
  });
  websocketDealerThread.join();
}