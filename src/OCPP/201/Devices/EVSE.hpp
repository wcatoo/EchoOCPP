
#ifndef ECHOOCPP_EVSE_HPP
#define ECHOOCPP_EVSE_HPP
#include "Connector.hpp"
#include "Meter.hpp"

namespace OCPP201 {
class EVSE {
public:
  int id;
  std::vector<Connector> mConnectors;
};

}

#endif // ECHOOCPP_EVSE_HPP
