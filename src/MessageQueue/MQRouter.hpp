#ifndef ECHOOCPP_MQROUTER_HPP
#define ECHOOCPP_MQROUTER_HPP
#include <thread>
#include "./protobufMessage.pb.h"
#include <zmq.hpp>

/**
 * Message queue for router
 */
class MQRouter {

public:
  /**
   *
   * @param tContext zmq context
   * @param tAddress bind address to zmq
   * @param tIdentity ID for this router
   */
  MQRouter(zmq::context_t *tContext, const std::string& tAddress, const std::string &tIdentity);
  ~MQRouter() {
    this->mDealerSocket.close();
  }
  void init();
  void run();
  void stop();

  void setCoreRouterFunction(const std::function<void()>& tCoreRouter) {
    this->mCoreRouterFunction = tCoreRouter;
  }
  void startCoreRouterFunction();
  [[deprecated("not completion")]]void stopCoreRouterFunction();

  std::function<void()> mMain;
  zmq::socket_t mDealerSocket;
//  zmq::socket_t mWorkerSocket;

  void send(const std::string& identity, const std::string &tPalyload);
//  void addWorker(const std::string& tIdentity, std::function<void(RouterProtobufMessage&)>);
private:
 zmq::context_t *mContext;
//  std::unordered_map<std::string,zmq::socket_t> mWorkers;
  const std::string mWorkerRouterAddress = "inproc://router_worker";
//  const std::string mWorkerRouterAddress = "tcp://localhost:5555";
  std::string mIdentity;
  std::string mAddress;
  std::unique_ptr<std::thread> mCoreRouterThreadPtr{nullptr};
  std::function<void()> mCoreRouterFunction{nullptr};

};

#endif // ECHOOCPP_MQROUTER_HPP
