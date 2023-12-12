#ifndef ECHOOCPP_MQROUTER_HPP
#define ECHOOCPP_MQROUTER_HPP
#include <zmq.hpp>

class MQRouter {
public:
  MQRouter() = delete;
  MQRouter(int tContext, const std::string& tAddress);
  ~MQRouter() {
    this->mClientSocket.close();
  }
  std::function<void()> mMain;

  zmq::socket_t mClientSocket;
private:
  zmq::context_t mContext;

};

#endif // ECHOOCPP_MQROUTER_HPP
