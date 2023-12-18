#include <zmq.hpp>
#include <iostream>
#include <string>
#include "src/MessageQueue/MQRouter.hpp"

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
    RouterProtobufMessage network2RouterMessage;
      network2RouterMessage.set_resource("Client1");
      network2RouterMessage.set_dest("wo");
      network2RouterMessage.set_data("i'm data");
      network2RouterMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP);
      dealer.send(zmq::message_t(identity), zmq::send_flags::sndmore);
//        dealer.send(zmq::message_t("wo%101%" + std::string(R"([2,"04d90767-8292-4be6-8c16-cc69d370635a","Authorize",{"idTag":"6ACA6EDC"}])")), zmq::send_flags::none);
      dealer.send(zmq::message_t(network2RouterMessage.SerializeAsString()), zmq::send_flags::none);
        i++;

        zmq::message_t reply;
        dealer.recv(reply, zmq::recv_flags::none);

    auto currentTimePoint = std::chrono::system_clock::now();

    // 将时间点转换为 time_t 类型
    std::time_t time = std::chrono::system_clock::to_time_t(currentTimePoint);

    // 获取 tm 结构体，用于格式化
    std::tm timeStruct = *std::localtime(&time);

    // 使用 std::put_time 格式化时间
    std::cout << std::put_time(&timeStruct, "%Y-%m-%d %H:%M:%S") << ".";

    // 获取毫秒数
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTimePoint.time_since_epoch()) % 1000;


    std::string reply_str(static_cast<char*>(reply.data()), reply.size());
    std::cout << std::setw(3) << std::setfill('0') << milliseconds.count() << " " <<reply_str <<std::endl;
        zmq_sleep(1);
        std::cout << "client end" << std::endl;
  }

  return 0;
}




