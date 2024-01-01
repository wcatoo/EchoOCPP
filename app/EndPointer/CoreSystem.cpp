
#ifndef ECHOOCPP_CORESYSTEM_CPP
#define ECHOOCPP_CORESYSTEM_CPP

#include "CoreSystem.hpp"
namespace EndPointer {

void CoreSystem::init() {
//  zmq::context_t context(1);
  this->mWebsocketClient = std::make_unique<Components::WebsocketClient>();
  this->mWebsocketClient->init();
}
void CoreSystem::run() {
  this->mWebsocketClient->run();
}



}
#endif
