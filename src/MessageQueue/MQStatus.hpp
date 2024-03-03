#ifndef ECHOOCPP_MQSTATUS_HPP
#define ECHOOCPP_MQSTATUS_HPP

#include <functional>
#include "protobufMessage.pb.h"

enum class MessageQueueStatus {
  RUNNING,
  CLOSE
};


class RouterPackage {
public:
  InternalRouterMessage message;
  std::function<void(const std::string&)> tGetReturnSuccessCallback{nullptr};
  std::function<void()> tGetResponseFailedCallback{nullptr};
};
#endif // ECHOOCPP_MQSTATUS_HPP
