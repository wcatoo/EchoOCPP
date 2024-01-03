//
// Created by 杨帆 on 2024/1/3.
//

#ifndef ECHOOCPP_OCPPROUTER_HPP
#define ECHOOCPP_OCPPROUTER_HPP

#include "../../MessageQueue/MQRouter.hpp"
namespace OCPP201 {


/**
 * OCPP router ->  receive message from websocket -> ocpp2.0.1 process -> send to worker or websocket
 * Message from websocket -> client message
 * Message from worker -> worker message
 */
class OCPPRouter{
public:
  OCPPRouter() = delete;
  OCPPRouter(const std::string& tAddress, const std::string &tIdentity);
  ~OCPPRouter() {
    if (this->mClientSocket != nullptr) {
      this->mClientSocket->close();
    }
    if (this->mWorkerSocket != nullptr) {
      this->mWorkerSocket->close();
    }
  }
  void init();
  void start();
  void stop();

private:
  std::unique_ptr<zmq::socket_t> mClientSocket;
  std::unique_ptr<zmq::socket_t> mWorkerSocket;
  zmq::context_t mContext;

};

}

#endif // ECHOOCPP_OCPPROUTER_HPP
