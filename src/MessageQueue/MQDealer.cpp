#include "MQDealer.hpp"
#include <thread>
#include <utility>
MQDealer::MQDealer(zmq::context_t *tContext, const std::string &tAddress, const std::string &tIdentity) {
  if (tContext != nullptr) {
    this->mDealer = std::make_unique<zmq::socket_t>(*tContext, zmq::socket_type::dealer);
  }
  this->mIdentity = tIdentity;
  this->mAddress = tAddress;
}

void MQDealer::send(const std::string &tPayload) {
  this->mDealer->send(zmq::message_t(this->mIdentity), zmq::send_flags::sndmore);
  this->mDealer->send(zmq::message_t(tPayload), zmq::send_flags::none);
}

void MQDealer::init() {
  this->mDealer->set(zmq::sockopt::routing_id, this->mIdentity);
}

void MQDealer::start() {
  this->mDealer->connect(this->mAddress);
  this->mReceiveThread = std::make_unique<std::thread>([this](){
    this->mStatus = MessageQueueStatus::RUNNING;
    while (this->mStatus == MessageQueueStatus::RUNNING) {
      zmq::message_t request;
        auto dataFrame = this->mDealer->recv(request, zmq::recv_flags::none);
      if (dataFrame.has_value()) {
        InternalRouterMessage message;
        if (message.ParseFromArray(request.data(), static_cast<int>(request.size()))) {
          if (this->mReceiveCallback) {
            this->mReceiveCallback(message);
          }
        }
      }
    }
  });
  this->mReceiveThread->detach();
}

void MQDealer::stop() {
  this->mStatus = MessageQueueStatus::CLOSE;
}
//void MQDealer::setReceiveCallBack(std::function<void(const std::string&, const std::string &)> &&tCallback) {
//  this->mReceiveCallback = std::move(tCallback);
//}
MQDealer::~MQDealer() {
  this->mStatus = MessageQueueStatus::CLOSE;
}
void MQDealer::send(const InternalRouterMessage &tPayload) {
  this->mDealer->send(zmq::message_t(this->mIdentity), zmq::send_flags::sndmore);
  this->mDealer->send(zmq::message_t(tPayload.SerializeAsString()), zmq::send_flags::none);
}


void MQDealer::setReceiveCallBack(
    std::function<void(const InternalRouterMessage &)> &&tCallback) {
  this->mReceiveCallback = std::move(tCallback);
}
