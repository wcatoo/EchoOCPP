//#include <iostream>
//#include <string>
//#include <unistd.h>
//#include <thread>
//#include <zmq.hpp>
//
//int main ()
//{
//  //  Prepare our context and socket
//  zmq::context_t context (1);
//  zmq::socket_t socket (context, zmq::socket_type::req);
//
//  std::cout << "Connecting to hello world server..." << std::endl;
//  socket.connect ("tcp://localhost:5556");
//
//  while (true) {
//    socket.send(zmq::message_t(std::string("hello")), zmq::send_flags::sndmore);
//    socket.send(zmq::message_t(std::string("message world")), zmq::send_flags::none);
//    std::this_thread::sleep_for(std::chrono::seconds(2));
//    zmq::message_t req ;
//    socket.recv(req, zmq::recv_flags::none);
//    std::string id = std::string(static_cast<char*>(req.data()));
//    std::cout << id << std::endl;
//    socket.recv(req, zmq::recv_flags::none);
//    std::string msg = std::string(static_cast<char*>(req.data()));
//    std::cout << msg << std::endl;
//
//  }
//
//
//
//  //  Do 10 requests, waiting each time for a response
////  for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
////    zmq::message_t request (5);
////    memcpy (request.data (), "Hello", 5);
////    std::cout << "Sending Hello " << request_nbr << "..." << std::endl;
////    socket.send (request, zmq::send_flags::none);
////
////    sleep(1);
////    //  Get the reply.
////    zmq::message_t reply;
////    socket.recv (reply, zmq::recv_flags::none);
////    std::cout << "Received World " << request_nbr << std::endl;
////  }
//  return 0;

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

//    // Send a message to the server
//    std::string message = "Request " + std::to_string(i);
//    zmq::message_t msg(message.size());
//    memcpy(msg.data(), message.data(), message.size());
//
    // Send the identity frame
    dealer.send(zmq::message_t(std::string("Client1")), zmq::send_flags::sndmore);

    // Send the message frame
    dealer.send(zmq::message_t(std::string("qwe")), zmq::send_flags::none);

    // Receive the reply from the server
    zmq::message_t replyIdentity;
    zmq::message_t replyMessage;

    // Receive identity frame
    dealer.recv(&replyIdentity);

    // Receive message frame
    dealer.recv(&replyMessage);
    std::string replyMsg(static_cast<char*>(replyMessage.data()), replyMessage.size());

    std::cout << "Received reply from server: " << replyMsg << std::endl;
  }

  return 0;
}


