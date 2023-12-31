#include "MQDealer.hpp"
#include <thread>
MQDealer::MQDealer(const std::string &tAddress, const std::string &tIdentity) {
  zmq::context_t context(2);
  this->mIdentity = tIdentity;
  this->mDealer = std::make_unique<zmq::socket_t>(context, zmq::socket_type::dealer);
  this->mDealer->set(zmq::sockopt::routing_id, this->mIdentity);
  this->mDealer->connect(tAddress);
}

void MQDealer::send(const std::string &tPayload) {
  this->mDealer->send(zmq::message_t(this->mIdentity), zmq::send_flags::sndmore);
  this->mDealer->send(zmq::message_t(tPayload), zmq::send_flags::none);
}
void MQDealer::init() {
  this->mReceiveThread = std::make_unique<std::thread>([this](){
    zmq::message_t id;
    zmq::message_t request;
    auto idReturn = this->mDealer->recv(id, zmq::recv_flags::none);

    auto dataFrame = this->mDealer->recv(request, zmq::recv_flags::none);
    if (dataFrame.has_value()) {
      RouterProtobufMessage message;
      if (message.ParseFromArray(request.data(), static_cast<int>(request.size()))) {
        if (this->mReceiveCallback) {
          this->mReceiveCallback(message.SerializeAsString());
        }

      }


    }

  });
}
void MQDealer::run() {
  this->mReceiveThread->join();
}

void MQDealer::setReceiveCallBack(std::function<void(const std::string &)> tCallback) {
  this->mReceiveCallback = tCallback;
}
