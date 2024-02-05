#ifndef ECHOOCPP_CHARGEPOINT_HPP
#define ECHOOCPP_CHARGEPOINT_HPP
#include "../../src/Devices/Connector.hpp"
#include "../../src/OCPP201/ChargePoint/OCPPManager.hpp"
#include "../../src/WebsocketComponent/Client/WebsocketClientManager.hpp"

class ChargePoint {
public:
  void init();


  std::vector<Connector> mConnectors;
private:

  std::unique_ptr<OCPP201::OCPPManager> mOCPPManager{nullptr};
  std::unique_ptr<Component::WebsocketClientManager> mWebsocketManager;

};

#endif // ECHOOCPP_CHARGEPOINT_HPP
