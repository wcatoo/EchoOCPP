
#ifndef ECHOOCPP_CORESYSTEM_CPP
#define ECHOOCPP_CORESYSTEM_CPP

#include "CoreSystem.hpp"
namespace EndPointer {

void CoreSystem::init() {
  // init core router
  this->mZMQContext = std::make_unique<zmq::context_t>(zmq::context_t(1));
  this->mCoreRouter = std::make_unique<MQRouter>(this->mZMQContext.get(), "inproc://coreRouter", "CoreRouter");

  this->mCoreRouter->setCoreRouterFunction([this](){
    zmq::pollitem_t  items[] = {
        {this->mCoreRouter->mDealerSocket, 0, ZMQ_POLLIN, 0}
    };
    zmq::message_t id;
    zmq::message_t request;
    while (true) {
      id.rebuild();
      request.rebuild();
      std::cout << "start polling " << std::endl;
      zmq::poll(items, 1, std::chrono::milliseconds(-1));
      std::cout << "rcv data " << std::endl;
      if (items[0].revents & ZMQ_POLLIN) {
        bool isFrameBroken = false;
        auto idReturn = this->mCoreRouter->mDealerSocket.recv(id, zmq::recv_flags::none);
        std::string idStr(static_cast<char*>(id.data()), id.size());
        if (!idReturn.has_value()) {
          isFrameBroken = true;
        }
        //       empty frame
        auto emptyFrame = this->mCoreRouter->mDealerSocket.recv(request, zmq::recv_flags::none);
        if (!emptyFrame.has_value()) {
          isFrameBroken = true;
        }
        auto dataFrame = this->mCoreRouter->mDealerSocket.recv(request, zmq::recv_flags::none);
        if (!dataFrame.has_value()) {
          isFrameBroken = true;
        }
        RouterProtobufMessage routerMessage;
        if (routerMessage.ParseFromArray(request.data(), static_cast<int>(request.size())) && !isFrameBroken) {
          this->mCoreRouter->mDealerSocket.send(zmq::message_t(routerMessage.dest()), zmq::send_flags::sndmore);
          this->mCoreRouter->mDealerSocket.send(request, zmq::send_flags::none);
        }
      }
    }
  });
  this->mCoreRouter->init();

}
void CoreSystem::run() {
  // run core router thread
  this->mCoreRouter->startCoreRouterFunction();
//  std::shared_ptr<zmq::context_t> context = std::make_shared<zmq::context_t>(2);
//  MQDealer mqDealer(this->mZMQContext.get(), "inproc://coreRouter", "test");

//  mqDealer.init();
//  mqDealer.start();
//  while (true) {
//    RouterProtobufMessage message;
//    message.set_dest("test");
//    message.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
//    message.set_data("hello zmq");
//    mqDealer.send(message.SerializeAsString());
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//  }
}



}
#endif
