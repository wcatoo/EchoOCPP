//#include "src/MessageQueue/MQRouter.hpp"
//#include <iostream>
//#include <unistd.h>
//
//int main(void) {
//  std::string tmp = "tcp://*:5555";
//  MQRouter mqRouter(2, tmp);
//  mqRouter.mMain = [&](){
//    while (true) {
//      zmq::message_t identity;
//      zmq::message_t message;
//
////      // Send the identity frame
////      mqRouter.mClientSocket.send(zmq::message_t(std::string("Client1")), zmq::send_flags::sndmore);
//      mqRouter.mClientSocket.send(zmq::message_t(std::string("message1")), zmq::send_flags::none);
//
//      // Send the reply frame
//    }
//
//  };
//
//
//  mqRouter.mMain();
//}

#include <zmq.hpp>
#include <iostream>
#include <string>

int main() {
  zmq::context_t context(1);
  zmq::socket_t router(context, ZMQ_ROUTER);
  router.bind("tcp://*:5555");

  while (true) {
    zmq::message_t identity;
    zmq::message_t message;
//
    // Receive identity frame
    router.recv(&identity);

    router.recv(&message);
    // Receive message frame
    router.recv(&message);
    std::string receivedMsg(static_cast<char*>(message.data()), message.size());

    std::cout << "Received message from client " << static_cast<char *>(identity.data())<< receivedMsg << std::endl;


    // Send the identity frame
    router.send(zmq::message_t(std::string("Client1")), ZMQ_SNDMORE);

    // Send the reply frame
    router.send(zmq::message_t(std::string("123")));
    zmq_sleep(1);
  }

  return 0;
}
