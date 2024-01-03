//
// Created by 杨帆 on 2024/1/3.
//

#ifndef ECHOOCPP_HELPER_HPP
#define ECHOOCPP_HELPER_HPP
#include <regex>
#include <string_view>

namespace OCPP201 {

class Helper {
public:

  bool checkOCPPMessageFormat(const std::string &tMessage);
private:
  std::regex mPattern{"\\[(\\d),\"([\\w-]+)\",\"(.+)\",(.+)\\]"};

};

} // namespace OCPP201

#endif // ECHOOCPP_HELPER_HPP
