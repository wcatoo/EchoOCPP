#ifndef ECHOOCPP_MQDEALER_HPP
#define ECHOOCPP_MQDEALER_HPP
#include <zmq.hpp>
#include "./protobufMessage.pb.h"

class MQDealer {
public:
  MQDealer() = default;
  MQDealer(const std::string &tAddress, const std::string &identiry);
  void init();
  void run();
  void send(const std::string &tPlayload);
  void setReceiveCallBack(std::function<void(const std::string &)>);
private:
  std::unique_ptr<zmq::socket_t> mDealer{};
  std::string mIdentity{};
  std::unique_ptr<std::thread> mReceiveThread{};
  std::function<void(const std::string &)> mReceiveCallback{};
};

#endif // ECHOOCPP_MQDEALER_HPP
