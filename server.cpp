#include "app/EndPointer/ChargePoint.hpp"


int main(void) {
//  std::shared_ptr<zmq::context_t> context = std::make_shared<zmq::context_t>(2);
//  MQDealer mqDealer(context, "tcp://localhost:8888", "test");
//
//  mqDealer.init();
//  mqDealer.start();
//  while (true) {
//        RouterProtobufMessage message;
//        message.set_dest("test");
//        message.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
//        message.set_data("hello zmq");
//    mqDealer.send(message.SerializeAsString());
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//  }
//   zmq::context_t context(2);

//   zmq::socket_t socket(context, zmq::socket_type::dealer);
//   socket.set(zmq::sockopt::routing_id, "test");
//   socket.connect("tcp://localhost:8888");


//   std::thread th([&](){
//     while (true) {
//       zmq::message_t id;
//       zmq::message_t request;
//       auto idReturn = socket.recv(id, zmq::recv_flags::none);

//       auto dataFrame = socket.recv(request, zmq::recv_flags::none);
//       if (dataFrame.has_value()) {
//         RouterProtobufMessage message;
//         if (message.ParseFromArray(request.data(), static_cast<int>(request.size()))) {
//           std::cout <<message.data() << std::endl;

// //          if (this->mReceiveCallback) {
// //            this->mReceiveCallback(message.resource(), message.SerializeAsString());
// //          }
//         }
//       }
//     }

//   });
//   th.detach();

  // while (true) {
  //   std::this_thread::sleep_for(std::chrono::seconds(2));
  //   RouterProtobufMessage message;
  //   message.set_dest("test");
  //   message.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
  //   message.set_data("hello zmq");
  //   socket.send(zmq::message_t("test"), zmq::send_flags::sndmore);
  //   socket.send(zmq::message_t(message.SerializeAsString()), zmq::send_flags::none);

  // }
  int sec = 1;


  std::thread timer([&](){

while (1) {

    std::this_thread::sleep_for(std::chrono::seconds(sec));
    std::cout << "timer: " << sec << std::endl;
}
  });
  timer.detach();

  std::this_thread::sleep_for(std::chrono::seconds(10));
  sec = 5;
  std::this_thread::sleep_for(std::chrono::seconds(10));





}

