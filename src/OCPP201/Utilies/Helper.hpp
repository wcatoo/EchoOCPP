
#ifndef ECHOOCPP_HELPER_HPP
#define ECHOOCPP_HELPER_HPP
#include <regex>
#include <string_view>
#include <optional>
#include <fstream>

#include <nlohmann/json-schema.hpp>
#include <magic_enum.hpp>

#include "../Message/MessageBase.hpp"
#include "../DataType/Datatypes.hpp"

namespace OCPP201 {

class Helper {
public:

  std::optional<MessageCall> checkMessageReq(const std::string &tMessage);
  std::optional<MessageCallResponse> checkMessageConf(const std::string &tMessage);
  std::optional<std::string> checkOCPPJsonSchema(OCPP201Type tType, const std::string &tJson, MessageMethod tMethod);

  static std::optional<std::string> readFromFile(const std::filesystem::path & tPath);
  static void writeToFile(const std::string &fileContext, const std::filesystem::path &tPath);

private:
  std::regex mPattern{R"lit(\s*\[(\d)\s*,\s*"([\w-]+)"\s*,\s*"([\w]+)"\s*,\s*(.+)\s*\])lit"};
  std::regex mPatternConf{R"lit(\s*\[\s*(\d+)\s*,\s*"([\w-]+)"\s*,\s*(.+)\s*\]\s*)lit"};
  std::unordered_map<OCPP201Type, std::string> mOCPP201JsonSchemasReq{};
  std::unordered_map<OCPP201Type, std::string> mOCPP201JsonSchemasConf{};

};

} // namespace OCPP201

#endif // ECHOOCPP_HELPER_HPP
