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

std::optional<std::string> readJsonSchema(std::filesystem::path tPath) {
  std::string fileContent{};
  std::filesystem::path rootPath =
      std::filesystem::current_path().parent_path();
  std::filesystem::path schemasDir = "OCPP_201_JSON_schemas";
  std::filesystem::path schemasFile = "AuthorizeRequest.json";
  std::ifstream inputFile{rootPath / schemasDir / schemasFile};
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

bool Helper::checkOCPPJsonSchema(OCPP201Type tType, const std::string &tJson, MessageMethod tMethod) {
  bool isValidJson{false};
  if (tMethod == MessageMethod::Request) {
    bool jsonSchemasExist = true;
    if (auto isfinded = this->mOCPP201JsonSchemasReq.find(tType) ;
        this->mOCPP201JsonSchemasReq.end() != isfinded) {
      std::stringstream strStream;
      strStream << (std::filesystem::current_path().parent_path()/"OCPP_201_JSON_schema").string() << magic_enum::enum_name(tType) << magic_enum::enum_name(tMethod) << ".json";
      auto fileContent = readJsonSchema(strStream.str());
      if (fileContent.has_value()) {
        this->mOCPP201JsonSchemasReq[tType] = fileContent.value();
      } else {
        jsonSchemasExist = false;
      }
    }
    if (jsonSchemasExist) {
      isValidJson = true;
    }
  } else if (tMethod == MessageMethod::Response) {
    bool jsonSchemasExist = true;
    if (auto isfinded = this->mOCPP201JsonSchemasConf.find(tType) ;
        this->mOCPP201JsonSchemasConf.end() != isfinded) {
      std::stringstream strStream;
      strStream << (std::filesystem::current_path().parent_path()/"OCPP_201_JSON_schema").string() << magic_enum::enum_name(tType) << magic_enum::enum_name(tMethod) << ".json";
      auto fileContent = readJsonSchema(strStream.str());
      if (fileContent.has_value()) {
        this->mOCPP201JsonSchemasConf[tType] = fileContent.value();
      } else {
        jsonSchemasExist = false;
      }
    }
    if (jsonSchemasExist) {
      isValidJson = true;
    }

  }

  return isValidJson;

}

} // namespace OCPP201