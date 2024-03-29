#pragma once
#include "Utilies/Utilies.hpp"
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <format>

namespace OCPP
{
enum class ProtocolError {
  FormatViolation,
  GenericError,
  InternalError,
  MessageTypeNotSupported,
  NotImplemented,
  NotSupported,
  OccurrenceConstraintViolation,
  PropertyConstraintViolation,
  RpcFrameworkError,
  SecurityError,
  TypeConstraintViolation
};

class MessageBase {
private:
  std::string MessageTypeId;
  std::string mMessageId;
  std::optional<std::string> mAction;
  std::optional<nlohmann::json> tPayload;
  std::optional<std::string> mErrorCode;
  std::optional<std::string> mErrorDescription;
  std::optional<nlohmann::json> mErrorDetails;
public:
//  inline std::string toString() {
//    return std::format("[{},{},{},{,}{,}]", MessageTypeId, mMessageId, mAction.has_value()?mAction)
////
//  }


};



class MessageCallRequest {
protected:
  std::string mMessageId;
  std::string mAction;
  nlohmann::json mPayload;
  std::stringstream stream;

public:
  virtual std::string toString(){
      return this->build();
  };
  void setMessageId(const std::string & tId) {
    this->mMessageId = tId;
  }
  void setAction(const std::string & tAction) {
    this->mAction = tAction;
  }

  void setPayload(const std::string &tPayload) {
    this->mPayload = tPayload;
  }
  std::string getMessageId() {
    return this->mMessageId;
  }
  std::string getAction() {
    return this->mAction;
  }
  std::string getPayload() {
      return to_string(this->mPayload);
  }
  [[nodiscard]]std::string build() {
    stream.str("");
    this->mMessageId = Utility::generateMessageId();
    stream << '[' << 2 << ",\"" <<  this->mMessageId << "\",\"" << this->mAction << "\"," << this->mPayload << "]";
    return stream.str();
  }
};

class MessageCallResponse {
protected:
  std::string mMessageId{};
  nlohmann::json mPayload{};
  std::stringstream stream{};
public:
  virtual std::string toString(){return this->build();};

  void setMessageId(const std::string & tId) {
    this->mMessageId = tId;
  }

  void setPayload(const std::string &tPayload) {
    this->mPayload = tPayload;
  }
  std::string getPayload() {
      return to_string(this->mPayload);
  }

  std::string getMessageId() {
    return this->mMessageId;
  }
  std::string build() {
    stream.str("");
    stream << '[' << 3 << ",\"" << this->mMessageId << "\",\"" << this->mPayload << ']' << std::endl;
    return stream.str();
  }
};

class MessageErrorResponse {
public:
  std::string serializeMessage() {
    stream.str("");
    stream << '[' << 4 << ",\"" <<  this->mMessageId << "\",\"" << magic_enum::enum_name<ProtocolError>(this->mErrorCode) << "\",\"" << this->mErrorDescription << "\"," << this->mErrorDetails << "]";
    return stream.str();
  }
  void buildMessageId() {
    this->mMessageId = Utility::generateMessageId();
  }
  void setErrorCode(ProtocolError tErrorCode) {
    this->mErrorCode = tErrorCode;
  }
  void setErrorDetails(nlohmann::json &&tJson) {
    this->mErrorDetails = tJson;
  }
  void setErrorDescription(const std::string & tErrorDescription) {
    this->mErrorDescription = tErrorDescription;
  }
  void setMessageId(const std::string &tMessageId) {
    this->mMessageId = tMessageId;
  }
  std::string getMessageId() const {
    return this->mMessageId;
  }

protected:
  std::string mMessageId{};
  ProtocolError mErrorCode{ProtocolError::NotSupported};
  nlohmann::json mErrorDetails{};
  std::string mErrorDescription{};
  std::stringstream stream{};
};

}
