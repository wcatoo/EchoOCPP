#include "Helper.hpp"

namespace OCPP201 {
std::optional<MessageCall> Helper::checkMessageCallValid(const std::string &tMessage) {
  std::smatch matches;
  if (std::regex_match(tMessage, matches, this->mPattern)) {
    MessageCall messageCall;
    messageCall.setMessageId(matches[2].str());
    messageCall.setAction(matches[3].str());
    messageCall.setPayload(matches[4].str());
    return std::optional<MessageCall>{std::move(messageCall)};
  }
  return std::nullopt;

}





} // namespace OCPP201