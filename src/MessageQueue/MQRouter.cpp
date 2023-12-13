#include "MQRouter.hpp"
#include <iostream>
MQRouter::MQRouter(std::shared_ptr<zmq::context_t> tContext, const std::string &tAddress, const std::string &tIdentity)
{
  this->mContext = tContext;
  this->mClientSocket = zmq::socket_t(*(this->mContext), zmq::socket_type::router);
  this->mClientSocket.set(zmq::sockopt::routing_id, tIdentity);
  this->mClientSocket.bind(tAddress);
  this->mWorkerSocket = zmq::socket_t(*(this->mContext), zmq::socket_type::router);
  this->mWorkerSocket.bind("inproc://router_worker");
}

void MQRouter::send(std::string identity, const std::string &tPalyload)
{
  this->mClientSocket.send(zmq::message_t(std::move(identity)), zmq::send_flags::sndmore);
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
    zmq::poll (items, 1, std::chrono::milliseconds(-1));

    // receive message from client. format of message is 
    // (destination),(message)
    // worker,[2,"04d90767-8292-4be6-8c16-cc69d370635a","Authorize",{"idTag":"6ACA6EDC"}]
    if (items[0].revents & ZMQ_POLLIN) {
      this->mClientSocket.recv(id, zmq::recv_flags::none);
      // empty frame
      this->mClientSocket.recv(request, zmq::recv_flags::none);
      this->mClientSocket.recv(request, zmq::recv_flags::none);

      std::string reqStr(static_cast<char*>(request.data()), request.size());
      std::string des = reqStr.substr(0, reqStr.find("%101%"));
      std::cout << des << std::endl;

    // auto currentTimePoint = std::chrono::system_clock::now();

    // std::time_t time = std::chrono::system_clock::to_time_t(currentTimePoint);
    // std::tm timeStruct = *std::localtime(&time);
    // std::cout << std::put_time(&timeStruct, "%Y-%m-%d %H:%M:%S") << ".";
    // auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTimePoint.time_since_epoch()) % 1000;

    // std::string reply_str(static_cast<char*>(request.data()), request.size());
    // std::cout << std::setw(3) << std::setfill('0') << milliseconds.count() << " " <<reply_str <<std::endl;

      this->mClientSocket.send(id, zmq::send_flags::sndmore);
      this->mClientSocket.send(request, zmq::send_flags::none);

    }
    if (items[1].revents & ZMQ_POLLIN) {
      std::cout << "item1" << std::endl;
    }

  } });
  th1.join();
}


void MQRouter::addWorker(const std::string &tIdentity) {
  mWorks[tIdentity] = zmq::socket_t (*(this->mContext), zmq::socket_type::dealer);

}