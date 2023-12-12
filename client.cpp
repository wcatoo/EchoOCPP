#include <zmq.hpp>
#include <iostream>
#include <string>

int main() {
  zmq::context_t context(1);
  zmq::socket_t dealer(context, ZMQ_DEALER);
  std::string identity = "Client1";
  dealer.setsockopt(ZMQ_IDENTITY, identity.c_str(), identity.size());
  dealer.connect("tcp://localhost:5555");


  while (1) {
    for (int i = 0; i < 5; ++i) {
        std::string request_msg = "Request " + std::to_string(i);

        zmq::message_t request(request_msg.size());
        memcpy(request.data(), request_msg.data(), request_msg.size());

        dealer.send(request);

        zmq::message_t reply;
        dealer.recv(&reply);

        std::string reply_str(static_cast<char*>(reply.data()), reply.size());
        std::cout << "Received reply: " << reply_str << std::endl;
    }
  }

  return 0;
}


