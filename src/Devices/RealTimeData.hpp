#ifndef ECHOOCPP_REALTIMEDATA_HPP
#define ECHOOCPP_REALTIMEDATA_HPP
#include "EVSE.hpp"
#include <vector>

class RealTimeDataManager {
public:
  RealTimeDataManager() = default;
  OCPP201::BootReasonEnumType bootReason{OCPP201::BootReasonEnumType::Unknown};
  std::vector<EVSE> EVSEs;

  friend void from_json(const nlohmann::json &json, RealTimeDataManager &data) {
    if (json.contains("chargingStation") && json.at("chargingStation").is_array()) {
      data.EVSEs = json.at("chargingStation").get<std::vector<EVSE>>();
    } else {
      data.EVSEs = std::vector<EVSE>();
    }
    if (json.contains("bootReason") && json.at("bootReason").is_string()) {
      auto tmp = magic_enum::enum_cast<OCPP201::BootReasonEnumType>(json.at("bootReason"));
      if (tmp.has_value()) {
        data.bootReason = tmp.value();
      } else {
        data.bootReason = OCPP201::BootReasonEnumType::Unknown;
      }
    } else {
      data.bootReason = OCPP201::BootReasonEnumType::Unknown;
    }
  }

  friend void to_json(nlohmann::json &json, const RealTimeDataManager &data) {
      json = nlohmann::json {
        {"bootReason", magic_enum::enum_name(data.bootReason)},
        {"chargingStation", data.EVSEs}
      };
  }
};

#endif // ECHOOCPP_REALTIMEDATA_HPP
