#include <zmq.hpp>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  zmq::context_t context(1);
  zmq::socket_t dealer(context, zmq::socket_type::dealer);
  std::string identity = "Client1";
  if (argc == 2) {
    identity = argv[1];
    std::cout << identity << std::endl;
  }
  dealer.set(zmq::sockopt::routing_id, identity);

  // dealer.setsockopt(ZMQ_IDENTITY, identity.c_str(), identity.size());
  dealer.connect("tcp://localhost:5556");


int i = 0;
  while (1) {
      dealer.send(zmq::message_t(identity), zmq::send_flags::sndmore);
        dealer.send(zmq::message_t(std::string("request" + std::to_string(i))));
        i++;

        zmq::message_t reply;
        dealer.recv(&reply);

        std::string reply_str(static_cast<char*>(reply.data()), reply.size());
        std::cout << "Received reply: " << reply_str << std::endl;
        zmq_sleep(1);
  }

  return 0;
}


