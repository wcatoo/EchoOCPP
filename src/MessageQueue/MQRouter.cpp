#include "MQRouter.hpp"
#include <iostream>
MQRouter::MQRouter(std::shared_ptr<zmq::context_t> tContext, const std::string &tAddress, const std::string &tIdentity) {
  this->mContext = tContext;
  this->mClientSocket = zmq::socket_t(*(this->mContext), zmq::socket_type::router);
  this->mClientSocket.set(zmq::sockopt::routing_id, tIdentity);
  this->mClientSocket.bind(tAddress);
  // zmq::context_t contex(199);
  this->mWorkerSocket = zmq::socket_t(*(this->mContext), zmq::socket_type::router);
  this->mWorkerSocket.bind("inproc://router_worker");
}

void MQRouter::send(std::string identity, const std::string &tPalyload) {
  this->mClientSocket.send(zmq::message_t(std::move(identity)), zmq::send_flags::sndmore);
  this->mClientSocket.send(zmq::message_t(tPalyload), zmq::send_flags::none);
}

void MQRouter::init() {
  std::thread th1([this](){
  int n = 0;
  while (1) {
    zmq::message_t id;
    zmq::message_t request;
    std::cout << "wait" << std::endl;
    this->mClientSocket.recv(id, zmq::recv_flags::none);
    // empty frame
    this->mClientSocket.recv(request, zmq::recv_flags::none);
    this->mClientSocket.recv(request, zmq::recv_flags::none);
        std::string reply_str(static_cast<char*>(request.data()), request.size());
        std::cout << "Received reply: " << reply_str << std::endl;

    this->mClientSocket.send(id, zmq::send_flags::sndmore);
    this->mClientSocket.send(request, zmq::send_flags::none);
    

    // std::cout << "send" << std::endl;
    // this->send("Client1", "request");
     zmq_sleep(1);
  }
  });
  th1.join();
}