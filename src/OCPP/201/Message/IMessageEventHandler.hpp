#ifndef ECHOOCPP_IMESSAGEEVENT_HPP
#define ECHOOCPP_IMESSAGEEVENT_HPP
#include "MessageBase.hpp"

class IMessageEventHandler {
public:
  virtual void requestEventHandler() = 0;
  virtual void sendRequest(){};
};

#endif // ECHOOCPP_IMESSAGEEVENT_HPP
