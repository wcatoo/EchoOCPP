//#ifndef ECHOOCPP_CHARGEPOINT_HPP
//#define ECHOOCPP_CHARGEPOINT_HPP
#pragma once
#include "../../src/OCPP/ChargeStation/OCPPManager.hpp"
#include "WebsocketClientManager.hpp"
#include "../../src/MessageQueue/MQRouter.hpp"

class ChargePoint {
public:
  void init();


  std::vector<OCPP201::Connector> mConnectors;
private:

  std::unique_ptr<OCPP::OCPPManager> mOCPPManager{nullptr};
  std::unique_ptr<Components::WebsocketClientManager> mWebsocketManager;
  zmq::context_t mZMQContext;
  std::unique_ptr<MQRouter> mCoreRouter{nullptr};

};

//#endif // ECHOOCPP_CHARGEPOINT_HPP
