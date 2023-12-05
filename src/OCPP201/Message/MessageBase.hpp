
#ifndef MESSAGECALLBASE_HPP
#define MESSAGECALLBASE_HPP
#include <uuid/uuid.h>
#include <string>
#include <nlohmann/json.hpp>
#include <sstream>

namespace OCPP201
{
class MessageCall {
protected:
  std::string mMessageId{};
  std::string mAction{};
  nlohmann::json mPayload{};
  std::stringstream stream{};
  static inline std::string generateMessageId()
  {
    uuid_t uuid;
    uuid_generate(uuid);

    char uuidStr[36];
    uuid_unparse(uuid, uuidStr);
    return uuidStr;
  }

public:
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

class MessageCallResult {
protected:
  nlohmann::json mPayload;
public:
  virtual void parseMessage() = 0;
};

} // namespace OCPP201
#endif
