#ifndef ECHOOCPP_REALTIMEDATA_HPP
#define ECHOOCPP_REALTIMEDATA_HPP
#include "EVSE.hpp"
#include <vector>

class RealTimeDataManager {
public:
  RealTimeDataManager() = default;
  OCPP201::BootReasonEnumType bootReason{OCPP201::BootReasonEnumType::Unknown};
  std::vector<EVSE> chargingStation;







  friend void from_json(const nlohmann::json &json, RealTimeDataManager &data) {
    if (json.contains("chargingStation") && json.at("chargingStation").is_array()) {
      data.chargingStation = json.at("chargingStation").get<std::vector<EVSE>>();
    } else {
      data.chargingStation = std::vector<EVSE>();

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
        {"chargingStation", data.chargingStation}
      };
  }
};

#endif // ECHOOCPP_REALTIMEDATA_HPP
