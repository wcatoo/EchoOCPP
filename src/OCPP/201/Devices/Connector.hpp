#ifndef ECHOOCPP_CONNECTOR_HPP
#define ECHOOCPP_CONNECTOR_HPP
#include "Enumerations.hpp"
#include "Meter.hpp"

namespace OCPP201 {
    class Connector {
    public:
        int mConnectorId{0};
        int mEVSEId{0};
        OCPP201::ConnectorEnumType mConnectorType{OCPP201::ConnectorEnumType::Unknown};
        OCPP201::ConnectorStatusEnumType mConnectorStatus{OCPP201::ConnectorStatusEnumType::Unavailable};
        Meter mMeter{};
    };
}




#endif // ECHOOCPP_CONNECTOR_HPP
