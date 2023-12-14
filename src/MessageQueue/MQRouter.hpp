#ifndef ECHOOCPP_MQROUTER_HPP
#define ECHOOCPP_MQROUTER_HPP
#include <zmq.hpp>
#include <thread>

class MQRouter {

public:
  MQRouter() = delete;
  MQRouter(std::shared_ptr<zmq::context_t> tContext, const std::string& tAddress, const std::string &tIdentity);
  ~MQRouter() {
    this->mClientSocket.close();
  }
  void init();
  std::function<void()> mMain;
  zmq::socket_t mClientSocket;
  zmq::socket_t mWorkerSocket;

  void send(const std::string& identity, const std::string &tPalyload);
  void addWorker(const std::string& tIdentity);
private:
  std::shared_ptr<zmq::context_t> mContext;
  std::unordered_map<std::string,zmq::socket_t> mWorks;
//  const std::string mWorkerRouterAddress = "inproc://router_worker";
  const std::string mWorkerRouterAddress = "tcp://localhost:5555";

};

#endif // ECHOOCPP_MQROUTER_HPP
