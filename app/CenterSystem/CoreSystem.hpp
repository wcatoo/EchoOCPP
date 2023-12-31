#ifndef ECHOOCPP_CORESYSTEM_HPP
#define ECHOOCPP_CORESYSTEM_HPP

#include "../../src/MessageQueue/MQRouter.hpp"
#include "../../src/WebsocketComponent/Server/WebsocketServer.hpp"
#include "../../src/MessageQueue/MQDealer.hpp"

namespace CenterSystem
{
class CoreSystem
{
public:
  CoreSystem();
  void init();
  void run();
private:
  std::unique_ptr<Components::WebsocketServer> mWebsocketServer;
  std::unique_ptr<MQRouter> mCoreRouterPtr;
  std::unique_ptr<MQDealer> mWebsocketDealer;
  MQDealer dealer;
};



} // namespace App

#endif
