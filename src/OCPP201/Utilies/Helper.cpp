#include "Helper.hpp"


namespace OCPP201 {
std::optional<MessageCall> Helper::checkMessageReq(const std::string &tMessage) {
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
std::optional<MessageCallResponse>
Helper::checkMessageConf(const std::string &tMessage) {
  std::smatch matches;
  if (std::regex_match(tMessage, matches, this->mPatternConf)) {
    MessageCallResponse messageCallResponse;
    messageCallResponse.setMessageId(matches[2].str());
    messageCallResponse.setPayload(matches[3].str());

    return std::optional<MessageCallResponse>{std::move(messageCallResponse)};
  }
  return std::nullopt;
}

std::optional<std::string> Helper::readFromFile(const std::filesystem::path &tPath){
  std::string fileContent{};
//  std::filesystem::path rootPath =
//      std::filesystem::current_path().parent_path();
  std::ifstream inputFile{tPath};
  inputFile.seekg(0, std::ios::end);
  std::streampos fileSize = inputFile.tellg();
  inputFile.seekg(0, std::ios::beg);
  fileContent.resize(static_cast<size_t>(fileSize));
  inputFile.read(&fileContent[0], fileSize);
  inputFile.close();
  if (fileContent.empty()) {
    return std::nullopt;
  }
  return fileContent;

}
void Helper::writeToFile(const std::string &fileContext,
                         const std::filesystem::path &tPath) {
  std::ofstream outputFile(tPath);
  if (outputFile.good()) {
    outputFile << fileContext;
    outputFile.close();
  }
  outputFile.good()
}

std::optional<std::string> Helper::checkOCPPJsonSchema(OCPP201Type tType, const std::string &tJson, MessageMethod tMethod) {
  nlohmann::json_schema::json_validator  jsonValidator;
  if (tMethod == MessageMethod::Request) {
    bool jsonSchemasExist = true;
    if (! this->mOCPP201JsonSchemasReq.contains(tType)){
      std::stringstream strStream;
      strStream << (std::filesystem::current_path().parent_path()/"OCPP_201_JSON_schemas").string() << "/" << magic_enum::enum_name(tType) <<   magic_enum::enum_name(tMethod) << ".json";
      auto fileContent = this->readFromFile(strStream.str());
      if (fileContent.has_value()) {
        this->mOCPP201JsonSchemasReq[tType] = fileContent.value();
      } else {
        jsonSchemasExist = false;
      }
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


  } else if (tMethod == MessageMethod::Response) {
    bool jsonSchemasExist = true;
    if (! this->mOCPP201JsonSchemasConf.contains(tType)){
      std::stringstream strStream;
      strStream << (std::filesystem::current_path().parent_path()/"OCPP_201_JSON_schemas").string() << "/" << magic_enum::enum_name(tType) <<   magic_enum::enum_name(tMethod) << ".json";
      auto fileContent = this->readFromFile(strStream.str());
      if (fileContent.has_value()) {
        this->mOCPP201JsonSchemasConf[tType] = fileContent.value();
      } else {
        jsonSchemasExist = false;
      }
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