
#ifndef MESSAGECALLBASE_HPP
#define MESSAGECALLBASE_HPP
#include <uuid/uuid.h>
#include <string>
#include <nlohmann/json.hpp>
#include <sstream>

namespace OCPP201
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

static inline std::string generateMessageId()
{
  uuid_t uuid;
  uuid_generate(uuid);

  char uuidStr[36];
  uuid_unparse(uuid, uuidStr);
  return uuidStr;
}

class MessageCall {
protected:
  std::string mMessageId{};
  std::string mAction{};
  nlohmann::json mPayload{};
  std::stringstream stream{};

public:
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
  std::string serializeMessage() {
    stream.clear();
    stream << '[' << 2 << ",\"" <<  generateMessageId() << "\",\"" << this->mAction << "\"," << this->mPayload << "]";
    return stream.str();
  }
};

class MessageCallResponse {
protected:
  std::string mMessageId{};
  int mAction{};
  nlohmann::json mPayload{};
  std::stringstream stream{};
public:
  virtual void messageParse() = 0;
};

class MessageErrorResponse {
public:
  std::string serializeMessage() {
    stream.clear();
    stream << '[' << 4 << ",\"" <<  this->mMessageId << "\",\"" << magic_enum::enum_name<ProtocolError>(this->mErrorCode) << "\",\"" << this->mErrorDescription << "\"," << this->mErrorDetails << "]";
    return stream.str();
  }

  void setErrorCode(ProtocolError tErrorCode) {
    this->mErrorCode = tErrorCode;
  }
  void setErrorDetails(nlohmann::json &tJson) {
    this->mErrorDetails = tJson;
  }
  void setErrorDescription(const std::string & tErrorDescription) {
    this->mErrorDescription = tErrorDescription;
  }
  void setMessageId(const std::string &tMessageId) {
    this->mMessageId = tMessageId;
  }

protected:
  std::string mMessageId{};
  ProtocolError mErrorCode{ProtocolError::NotSupported};
  nlohmann::json mErrorDetails{};
  std::string mErrorDescription{};
  std::stringstream stream{};
};

} // namespace OCPP201
#endif
