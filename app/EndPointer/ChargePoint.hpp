#ifndef ECHOOCPP_CHARGEPOINT_HPP
#define ECHOOCPP_CHARGEPOINT_HPP
#include "../../src/Devices/Connector.hpp"
#include "../../src/OCPP201/ChargePoint/OCPPManager.hpp"

class ChargePoint {
public:
  void init();


private:

  std::unique_ptr<OCPP201::OCPPManager> mOCPPManager{nullptr};




};

#endif // ECHOOCPP_CHARGEPOINT_HPP
