

#ifndef ECHOOCPP_CORESYSTEM_HPP
#define ECHOOCPP_CORESYSTEM_HPP
//#include "../../src/MessageQueue/MQDealer.hpp"
#include "../../src/MessageQueue/MQRouter.hpp"
#include "../../src/OCPP/ChargeStation/OCPPCore.hpp"
#include "../../src/WebsocketComponent/Client/WebsocketClient.hpp"
#include <memory>

namespace EndPointer {
class CoreSystem {
public:
  CoreSystem() = default;
  void init();
  void run();
  void stop();
private:
  std::unique_ptr<MQRouter> mCoreRouter{nullptr};
  std::unique_ptr<std::vector<Components::WebsocketClient>> mWebsocketClients{nullptr};
  std::unique_ptr<OCPP201::OCPPManager> mOCPP201Manager{nullptr};
  std::unique_ptr<zmq::context_t> mZMQContext;
};


}
#endif // ECHOOCPP_CORESYSTEM_HPP
