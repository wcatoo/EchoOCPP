
#ifndef ECHOOCPP_EVSE_HPP
#define ECHOOCPP_EVSE_HPP
#include "Connector.hpp"

class EVSE {
public:
  EVSE() = default;
  int id;
  std::vector<Connector> mConnectors;
  friend void from_json(const nlohmann::json &json, EVSE &data) {
    if (json.contains("EVSE") && json.at("EVSE").is_array()) {
      data.mConnectors = json.at("EVSE").get<std::vector<Connector>>();
    } else {
      data.mConnectors = std::vector<Connector>();
    }
    if (json.contains("id") && json.at("id").is_number_integer()) {
      data.id = json.at("id").get<int>();
    } else {
      data.id = 0;
    }
  }

  friend void to_json(nlohmann::json &json, const EVSE &data) {
    json = nlohmann::json {
      {"id", data.id},
      {"connectors", data.mConnectors}
    };
  }

};


#endif // ECHOOCPP_EVSE_HPP
