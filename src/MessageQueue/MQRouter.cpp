#include "MQRouter.hpp"
#include <iostream>
#include <utility>
MQRouter::MQRouter(std::shared_ptr<zmq::context_t> tContext, const std::string &tAddress, const std::string &tIdentity)
{
  this->mContext = std::move(tContext);
  this->mClientSocket = zmq::socket_t(*(this->mContext), zmq::socket_type::router);
  this->mClientSocket.set(zmq::sockopt::routing_id, tIdentity);
  this->mClientSocket.bind(tAddress);
  this->mWorkerSocket = zmq::socket_t(*(this->mContext), zmq::socket_type::router);
  this->mWorkerSocket.bind(this->mWorkerRouterAddress);
}

void MQRouter::send(const std::string& identity, const std::string &tPalyload)
{
  this->mClientSocket.send(zmq::message_t(identity), zmq::send_flags::sndmore);
  this->mClientSocket.send(zmq::message_t(tPalyload), zmq::send_flags::none);
}

void MQRouter::init()
{
  std::thread th1([this]()
                  {
  int n = 0;
  while (1) {
    zmq::pollitem_t items [] = {
      { this->mClientSocket, 0, ZMQ_POLLIN, 0 },
      { this->mWorkerSocket, 0, ZMQ_POLLIN, 0 }
    };
    zmq::message_t id;
    zmq::message_t request;
    zmq::poll (items, 2, std::chrono::milliseconds(-1));

    // receive message from client. format of message is 
    // (destination),(message)
    // worker%101%[2,"04d90767-8292-4be6-8c16-cc69d370635a","Authorize",{"idTag":"6ACA6EDC"}]
    if (items[0].revents & ZMQ_POLLIN) {
      bool isResultBroken = false;
      auto idReturn = this->mClientSocket.recv(id, zmq::recv_flags::none);
      std::string idStr(static_cast<char*>(id.data()), id.size());
//      std::cout << "id: " << idStr << std::endl;
      if (!idReturn.has_value()) {
        isResultBroken = true;
      }
//       empty frame
      auto emptyFrame = this->mClientSocket.recv(request, zmq::recv_flags::none);
      if (!emptyFrame.has_value()) {
        isResultBroken = true;
      }
      auto dataFrame = this->mClientSocket.recv(request, zmq::recv_flags::none);
      if (!dataFrame.has_value()) {
        isResultBroken = true;
      }

      if (!isResultBroken) {
        std::string reqStr(static_cast<char*>(request.data()), request.size());
        std::string des = reqStr.substr(0, reqStr.find("%101%"));
//        std::cout << des << std::endl;

        this->mWorkerSocket.send(zmq::message_t(des), zmq::send_flags::sndmore);
        this->mWorkerSocket.send(request, zmq::send_flags::none);
      }
    }
    if (items[1].revents & ZMQ_POLLIN) {
      bool isResultBroken = false;
      auto idReturn = this->mWorkerSocket.recv(id, zmq::recv_flags::none);
      std::string idStr(static_cast<char*>(id.data()), id.size());
//      std::cout << "id: " << idStr << std::endl;
      if (!idReturn.has_value()) {
        isResultBroken = true;
      }
      // empty frame
//      auto emptyFrame = this->mClientSocket.recv(request, zmq::recv_flags::none);
//      if (!emptyFrame.has_value()) {
//        isResultBroken = true;
//      }
      auto dataFrame = this->mWorkerSocket.recv(request, zmq::recv_flags::none);
      if (!dataFrame.has_value()) {
        isResultBroken = true;
      }

      if (!isResultBroken) {
        std::string reqStr(static_cast<char*>(request.data()), request.size());
        std::string des = reqStr.substr(0, reqStr.find("%101%"));
//        std::cout << des << std::endl;

        this->mClientSocket.send(zmq::message_t(des), zmq::send_flags::sndmore);
        this->mClientSocket.send(request, zmq::send_flags::none);
      }
    }

  } });
  th1.join();
}


void MQRouter::addWorker(const std::string &tIdentity) {
  this->mWorks[tIdentity] = zmq::socket_t (*(this->mContext), zmq::socket_type::dealer);
  this->mWorks[tIdentity].set(zmq::sockopt::routing_id, tIdentity);
  this->mWorks[tIdentity].connect(this->mWorkerRouterAddress);

  std::thread th([&](){
    while (true) {
          zmq::message_t id;
          zmq::message_t request;
          auto idReturn = this->mWorks[tIdentity].recv(id, zmq::recv_flags::none);
          std::string idStr(static_cast<char *>(id.data()), id.size());
          this->mWorks[tIdentity].send(
              zmq::message_t(std::string("Client1%101%worker receive message")),
              zmq::send_flags::none);
        }
  });
  th.detach();

}