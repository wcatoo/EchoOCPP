//#ifndef ECHOOCPP_CHARGEPOINT_HPP
//#define ECHOOCPP_CHARGEPOINT_HPP
#pragma once
#include "../../src/MessageQueue/MQRouter.hpp"
#include "../../src/OCPP/ChargeStation/OCPPCore.hpp"
#include "WebsocketClientManager.hpp"

class ChargePoint {
public:
  void init();


  std::vector<Connector> mConnectors;
private:

  std::unique_ptr<OCPP::OCPPCore> mOCPPManager{nullptr};
  std::unique_ptr<Components::WebsocketClientManager> mWebsocketManager;
  zmq::context_t mZMQContext;
  std::unique_ptr<MQRouter> mCoreRouter{nullptr};

};

//#endif // ECHOOCPP_CHARGEPOINT_HPP
