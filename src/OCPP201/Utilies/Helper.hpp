//
// Created by 杨帆 on 2024/1/3.
//

#ifndef ECHOOCPP_HELPER_HPP
#define ECHOOCPP_HELPER_HPP
#include <regex>
#include <string_view>
#include <optional>
#include <magic_enum.hpp>

#include <json-schema-validator/json-schema-validator.hpp>

#include "../Message/MessageBase.hpp"

namespace OCPP201 {

class Helper {
public:

  std::optional<MessageCall> checkMessageReq(const std::string &tMessage);
  std::optional<MessageCallResponse> checkMessageConf(const std::string &tMessage);

private:
  std::regex mPattern{R"lit(\s*\[(\d)\s*,\s*"([\w-]+)"\s*,\s*"([\w]+)"\s*,\s*(.+)\s*\])lit"};
  std::regex mPatternConf{R"lit(\s*\[\s*(\d+)\s*,\s*"([\w-]+)"\s*,\s*(.+)\s*\]\s*)lit"};


};

} // namespace OCPP201

#endif // ECHOOCPP_HELPER_HPP
