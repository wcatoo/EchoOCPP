
#ifndef ECHOOCPP_CORESYSTEM_CPP
#define ECHOOCPP_CORESYSTEM_CPP

#include "CoreSystem.hpp"
namespace EndPointer {

void CoreSystem::init() {
  zmq::context_t context(1);
  this->mWebsocketClient = std::make_unique<Components::WebsocketClient>("ws://127.0.0.1:8888");
  this->mWebsocketClient->init();
}
void CoreSystem::run() {
  this->mWebsocketClient->run();
}
}
#endif
