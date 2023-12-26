#ifndef ECHOOCPP_CORESYSTEM_HPP
#define ECHOOCPP_CORESYSTEM_HPP

#include "../../src/MessageQueue/MQRouter.hpp"
#include "../../src/WebsocketComponent/Server/WebsocketServer.hpp"

namespace App
{
class CoreSystem
{
public:
  CoreSystem();
  void init();
private:
  std::unique_ptr<Components::WebsocketServer> mWebsocketServer;
  std::unique_ptr<MQRouter> mCoreRouterPtr;
};



} // namespace App

#endif
