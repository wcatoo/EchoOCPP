
#ifndef ECHOOCPP_HELPER_HPP
#define ECHOOCPP_HELPER_HPP
#include <regex>
#include <string_view>
#include <optional>
#include <fstream>

#include <nlohmann/json-schema.hpp>
#include <magic_enum.hpp>

#include "../MessageBase.hpp"
#include "../201/DataType/Datatypes.hpp"
#include "../../System/IO.hpp"

namespace OCPP {


class Helper {
public:

  std::optional<OCPP::MessageCallRequest> checkMessageReq(const std::string &tMessage);
  std::optional<OCPP::MessageCallResponse> checkMessageConf(const std::string &tMessage);
  std::optional<std::string> checkOCPPJsonSchema(OCPP201::OCPP201Type tType, const std::string &tJson, OCPP201::MessageMethod tMethod);


private:
  std::regex mPattern{R"lit(\s*\[(\d)\s*,\s*"([\w-]+)"\s*,\s*"([\w]+)"\s*,\s*(.+)\s*\])lit"};
  std::regex mPatternConf{R"lit(\s*\[\s*(\d+)\s*,\s*"([\w-]+)"\s*,\s*(.+)\s*\]\s*)lit"};
  std::unordered_map<OCPP201::OCPP201Type, std::string> mOCPP201JsonSchemasReq{};
  std::unordered_map<OCPP201::OCPP201Type, std::string> mOCPP201JsonSchemasConf{};

};

} // namespace OCPP201

#endif // ECHOOCPP_HELPER_HPP
