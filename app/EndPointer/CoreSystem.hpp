

#ifndef ECHOOCPP_CORESYSTEM_HPP
#define ECHOOCPP_CORESYSTEM_HPP
#include "../../src/MessageQueue/MQDealer.hpp"
#include "../../src/WebsocketComponent/Client/WebsocketClient.hpp"
#include <memory>

namespace EndPointer {
class CoreSystem {
public:
  CoreSystem() = default;
  void init();
  void run();
private:
  std::unique_ptr<Components::WebsocketClient> mWebsocketClient;
  std::unique_ptr<MQDealer> mMessageQueueDealer;
};


}
#endif // ECHOOCPP_CORESYSTEM_HPP
