#include "Helper.hpp"


namespace OCPP {
std::optional<OCPP::MessageCallRequest> Helper::checkMessageReq(const std::string &tMessage) {
  std::smatch matches;
  if (std::regex_match(tMessage, matches, this->mPattern)) {
    OCPP::MessageCallRequest messageCall;
    messageCall.setMessageId(matches[2].str());
    messageCall.setAction(matches[3].str());
    messageCall.setPayload(matches[4].str());
    return std::optional<OCPP::MessageCallRequest>{std::move(messageCall)};
  }
  return std::nullopt;

}
std::optional<OCPP::MessageCallResponse>
Helper::checkMessageConf(const std::string &tMessage) {
  std::smatch matches;
  if (std::regex_match(tMessage, matches, this->mPatternConf)) {
    OCPP::MessageCallResponse messageCallResponse;
    messageCallResponse.setMessageId(matches[2].str());
    messageCallResponse.setPayload(matches[3].str());

    return std::optional<OCPP::MessageCallResponse>{std::move(messageCallResponse)};
  }
  return std::nullopt;
}

std::optional<std::string> Helper::checkOCPPJsonSchema(OCPP201::OCPP201Type tType, const std::string &tJson, OCPP201::MessageMethod tMethod) {
  nlohmann::json_schema::json_validator  jsonValidator;
  if (tMethod == OCPP201::MessageMethod::Request) {
    bool jsonSchemasExist = true;
    if (! this->mOCPP201JsonSchemasReq.contains(tType)){
      std::stringstream strStream;
      strStream << (std::filesystem::current_path().parent_path()/"OCPP_201_JSON_schemas").string() << "/" << magic_enum::enum_name(tType) <<   magic_enum::enum_name(tMethod) << ".json";
//      auto fileContent = System_IO::readFromFile(strStream.str());
//      if (fileContent.has_value()) {
//        this->mOCPP201JsonSchemasReq[tType] = fileContent.value();
//      } else {
//        jsonSchemasExist = false;
//      }
    }
    if (jsonSchemasExist) {
      std::stringstream strStream;
      try {
        jsonValidator.set_root_schema(nlohmann::json::parse(this->mOCPP201JsonSchemasReq[tType]));
      } catch (const std::exception &e) {
        strStream << "Validation of schema failed, here is why: " << e.what() << "\n";
        std::cerr << strStream.str() << std::endl;
        return strStream.str();
      }

      try {
        jsonValidator.validate(nlohmann::json::parse(tJson)); // validate the document - uses the default throwing error-handler
        return std::nullopt;
      } catch (const std::exception &e) {
        strStream << "Validation failed, here is why: " << e.what() << "\n";
        std::cerr << strStream.str() << std::endl;
        return strStream.str();
      }
    }


  } else if (tMethod == OCPP201::MessageMethod::Response) {
    bool jsonSchemasExist = true;
    if (! this->mOCPP201JsonSchemasConf.contains(tType)){
      std::stringstream strStream;
      strStream << (std::filesystem::current_path().parent_path()/"OCPP_201_JSON_schemas").string() << "/" << magic_enum::enum_name(tType) <<   magic_enum::enum_name(tMethod) << ".json";
//      auto fileContent = System_IO::readFromFile(strStream.str());
//      if (fileContent.has_value()) {
//        this->mOCPP201JsonSchemasConf[tType] = fileContent.value();
//      } else {
//        jsonSchemasExist = false;
//      }
    }
    if (jsonSchemasExist) {
      std::stringstream strStream;
      try {
        jsonValidator.set_root_schema(nlohmann::json::parse(this->mOCPP201JsonSchemasConf[tType]));
      } catch (const std::exception &e) {
        strStream << "Validation of schema failed, here is why: " << e.what() << "\n";
        std::cerr << strStream.str() << std::endl;
        return strStream.str();
      }

      try {
        jsonValidator.validate(nlohmann::json::parse(tJson)); // validate the document - uses the default throwing error-handler
        return std::nullopt;
      } catch (const std::exception &e) {
        strStream << "Validation failed, here is why: " << e.what() << "\n";
        std::cerr << strStream.str() << std::endl;
        return strStream.str();
      }
    }
  }
  return "Internal error when check json schema";
}

} // namespace OCPP201