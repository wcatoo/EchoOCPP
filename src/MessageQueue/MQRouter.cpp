#include "MQRouter.hpp"
#include <iostream>
#include <utility>
MQRouter::MQRouter(zmq::context_t *tContext, const std::string &tAddress, const std::string &tIdentity)
{
    this->mContext = tContext;
    this->mAddress = tAddress;
    this->mIdentity = tIdentity;
//    this->mWorkerSocket = zmq::socket_t(*(this->mContext), zmq::socket_type::router);
}

void MQRouter::send(const std::string& identity, const std::string &tPalyload)
{
  this->mDealerSocket.send(zmq::message_t(identity), zmq::send_flags::sndmore);
  this->mDealerSocket.send(zmq::message_t(tPalyload), zmq::send_flags::none);
}

void MQRouter::run() {

  this->startCoreRouterFunction();

}
void MQRouter::stop() {
}

void MQRouter::init()
{
  try {
    this->mDealerSocket = zmq::socket_t(*(this->mContext), zmq::socket_type::router);
    this->mDealerSocket.set(zmq::sockopt::routing_id, this->mIdentity);
    this->mDealerSocket.bind(this->mAddress);
  } catch (std::exception &e) {
    throw e.what();
  }

//  std::thread th1([this]() {
//    zmq::pollitem_t items [] = {
//        { this->mDealerSocket, 0, ZMQ_POLLIN, 0 },
////        { this->mWorkerSocket, 0, ZMQ_POLLIN, 0 }
//    };
//    while (true) {
//      zmq::message_t id;
//      zmq::message_t request;
//      zmq::poll (items, 2, std::chrono::milliseconds(-1));
//
//      if (items[0].revents & ZMQ_POLLIN) {
//        bool isFrameBroken = false;
//        auto idReturn = this->mDealerSocket.recv(id, zmq::recv_flags::none);
//        std::string idStr(static_cast<char*>(id.data()), id.size());
//        if (!idReturn.has_value()) {
//          isFrameBroken = true;
//        }
////       empty frame
//        auto emptyFrame = this->mDealerSocket.recv(request, zmq::recv_flags::none);
//        if (!emptyFrame.has_value()) {
//          isFrameBroken = true;
//        }
//        auto dataFrame = this->mDealerSocket.recv(request, zmq::recv_flags::none);
//        if (!dataFrame.has_value()) {
//          isFrameBroken = true;
//        }
//        RouterProtobufMessage RouterMessage;
//        if (RouterMessage.ParseFromArray(request.data(), static_cast<int>(request.size())) && !isFrameBroken) {
////          this->mWorkerSocket.send(zmq::message_t(RouterMessage.dest()), zmq::send_flags::sndmore);
////          this->mWorkerSocket.send(request, zmq::send_flags::none);
//        }
//      }
//      if (items[1].revents & ZMQ_POLLIN) {
//        bool isFrameBroken = false;
//        auto idReturn = this->mWorkerSocket.recv(id, zmq::recv_flags::none);
//        std::string idStr(static_cast<char*>(id.data()), id.size());
//        if (!idReturn.has_value()) {
//          isFrameBroken = true;
//        }
//        // empty frame
//        // i don't know why there is not a empty frame
////      auto emptyFrame = this->mClientSocket.recv(request, zmq::recv_flags::none);
////      if (!emptyFrame.has_value()) {
////        isResultBroken = true;
////      }
//        auto dataFrame = this->mWorkerSocket.recv(request, zmq::recv_flags::none);
//        if (!dataFrame.has_value()) {
//          isFrameBroken = true;
//        }
//        if (!isFrameBroken) {
//          RouterProtobufMessage RouterMessage;
//          if (RouterMessage.ParseFromArray(request.data(), static_cast<int>(request.size())) && !isFrameBroken) {
//            this->mDealerSocket.send(zmq::message_t(RouterMessage.dest()), zmq::send_flags::sndmore);
//            this->mDealerSocket.send(request, zmq::send_flags::none);
//          }
//        }
//      }
//    } });
//  th1.detach();
}
/**
 * start running core router thread
 */
void MQRouter::startCoreRouterFunction() {
  if (this->mCoreRouterFunction != nullptr) {
    this->mCoreRouterThreadPtr = std::make_unique<std::thread>(this->mCoreRouterFunction);
    this->mCoreRouterThreadPtr->detach();
  }
}
void MQRouter::stopCoreRouterFunction() {}

//void MQRouter::addWorker(const std::string &tIdentity, std::function<void(RouterProtobufMessage&)> tCallback) {
//  this->mWorkers[tIdentity] = zmq::socket_t (*(this->mContext), zmq::socket_type::dealer);
//  this->mWorkers[tIdentity].set(zmq::sockopt::routing_id, tIdentity);
//  this->mWorkers[tIdentity].connect(this->mWorkerRouterAddress);
//  // TODO worker function
//  std::thread th([&](){
//    while (true) {
//      zmq::message_t requestData;
//      auto dataFrame = this->mWorkers[tIdentity].recv(requestData, zmq::recv_flags::none);
//      RouterProtobufMessage rcvMessage;
//      if (rcvMessage.ParseFromArray(requestData.data(), static_cast<int>(requestData.size())) && tCallback) {
//        tCallback(rcvMessage);
//      }
//      if (dataFrame.has_value()) {
//        RouterProtobufMessage routerProtobufMessage;
//        routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
//        routerProtobufMessage.set_dest("Client1");
//        routerProtobufMessage.set_resource("Client1");
//        routerProtobufMessage.set_data("worker had received data");
//        this->mWorkers[tIdentity].send((zmq::message_t(routerProtobufMessage.SerializeAsString())), zmq::send_flags::none);
//
//      }
//    }
//  });
//  th.detach();
//
//}