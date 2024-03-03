#ifndef ECHOOCPP_CONNECTOR_HPP
#define ECHOOCPP_CONNECTOR_HPP
#include "../OCPP/201/DataType/Enumerations.hpp"
#include "Meter.hpp"
#include <nlohmann/json.hpp>
#include <magic_enum.hpp>

class Connector {
public:
  Connector() = default;
    int mConnectorId{0};
    bool isPlugIn{false};
    bool isCharging{false};
    OCPP201::ConnectorEnumType mConnectorType{OCPP201::ConnectorEnumType::Unknown};
    OCPP201::ConnectorStatusEnumType mConnectorStatus{OCPP201::ConnectorStatusEnumType::Unavailable};
    Meter mMeter{};
    friend void from_json(const nlohmann::json &json, Connector &data) {
      if (json.contains("connectorId") && json.at("connectorId").is_number_integer()) {
        json.at("connectorId").get_to(data.mConnectorId);
      }

      if (json.contains("status") && json.at("status").is_string()) {
        auto tmp = magic_enum::enum_cast<OCPP201::ConnectorStatusEnumType>(json.at("status"));
        if (tmp.has_value()) {
          data.mConnectorStatus = tmp.value();
        } else {
          data.mConnectorStatus = OCPP201::ConnectorStatusEnumType::Available;
        }
      } else {
        data.mConnectorStatus = OCPP201::ConnectorStatusEnumType::Available;
      }
    }

    friend void to_json(nlohmann::json &json, const Connector &data) {
      json = nlohmann::json {
        {"connectorId", data.mConnectorId},
        {"status", magic_enum::enum_name(data.mConnectorStatus)}
      };
    }
};




#endif // ECHOOCPP_CONNECTOR_HPP
