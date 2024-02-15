#ifndef ECHOOCPP_CHARGEPOINT_HPP
#define ECHOOCPP_CHARGEPOINT_HPP
#include "../../src/OCPP/201/Devices/Connector.hpp"
#include "../../src/OCPP/ChargePoint/OCPPManager.hpp"
#include "WebsocketClientManager.hpp"
#include "../../src/MessageQueue/MQRouter.hpp"

class ChargePoint {
public:
  void init();


  std::vector<OCPP201::Connector> mConnectors;
private:

  std::unique_ptr<OCPP201::OCPPManager> mOCPPManager{nullptr};
  std::unique_ptr<Components::WebsocketClientManager> mWebsocketManager;
  zmq::context_t mZMQContext;
  std::unique_ptr<MQRouter> mCoreRouter{nullptr};

};

#endif // ECHOOCPP_CHARGEPOINT_HPP
