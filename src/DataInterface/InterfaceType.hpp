#ifndef ECHOOCPP_INTERFACETYPE_HPP
#define ECHOOCPP_INTERFACETYPE_HPP
#include <nlohmann/json.hpp>
#include <magic_enum.hpp>

enum class StatusCode {
  Accept,
  Reject,
  Schedule
};

class InterfaceResponse {
public:
  InterfaceResponse() = default;
  StatusCode statusCode;
  friend void to_json(nlohmann::json &json, const InterfaceResponse &data) {
    json = nlohmann::json {
        {"statusCode", magic_enum::enum_name(data.statusCode)}
    };
  }

  friend void from_json(const nlohmann::json &json, InterfaceResponse &data) {
    if (json.contains("statusCode") && json.at("statusCode").is_string()) {
      auto tmp = magic_enum::enum_cast<StatusCode>(json.at("statusCode"));
      data.statusCode = tmp.has_value() ? tmp.value() : StatusCode::Reject;
    }
  }

};

#endif // ECHOOCPP_INTERFACETYPE_HPP
