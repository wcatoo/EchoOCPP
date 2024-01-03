//
// Created by 杨帆 on 2024/1/3.
//

#include "Helper.hpp"

namespace OCPP201 {
bool Helper::checkOCPPMessageFormat(const std::string &tMessage) {
  std::smatch matches;

  return std::regex_match(tMessage, matches, this->mPattern);

}
} // namespace OCPP201