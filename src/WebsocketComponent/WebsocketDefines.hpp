#ifndef ECHOOCPP_WEBSOCKETDEFINES_HPP
#define ECHOOCPP_WEBSOCKETDEFINES_HPP

#include <string>
#include <iostream>

namespace Components {
enum class WebsocketStatus {
  OPEN,
  CLOSE
};
class WebsocketOnMessageInfo {
public:
  WebsocketOnMessageInfo() {
    mResource = "";
    mMessage = "";
  }
  ~WebsocketOnMessageInfo() {
  }
  void reset() {
    this->mMessage = "";
    this->mResource = "";
  }

  std::string getPayload() {
    return this->mMessage;
  }

  std::string getResource() {
    return this->mResource;
  }

  void setMessage(const std::string & tMessage) {
    this->mMessage = tMessage;
  }
  void setResource(const std::string & tResource) {
    this->mResource = tResource;
  }
private:
  std::string mMessage;
  std::string mResource;
};


}
#endif // ECHOOCPP_WEBSOCKETDEFINES_HPP
