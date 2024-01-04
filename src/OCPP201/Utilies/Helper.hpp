//
// Created by 杨帆 on 2024/1/3.
//

#ifndef ECHOOCPP_HELPER_HPP
#define ECHOOCPP_HELPER_HPP
#include <regex>
#include <string_view>
#include <optional>
#include <magic_enum.hpp>
#include "../Message/MessageBase.hpp"

namespace OCPP201 {

class Helper {
public:

  std::optional<MessageCall> checkMessageCallValid(const std::string &tMessage);

private:
  std::regex mPattern{R"lit(\[(\d),"([\w-]+)","([\w]+)",(.+)\])lit"};

};

} // namespace OCPP201

#endif // ECHOOCPP_HELPER_HPP
