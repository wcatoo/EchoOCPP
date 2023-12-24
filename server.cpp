//#include "src/MessageQueue/MQRouter.hpp"
#include "src/WebsocketComponent/Server/WebsocketServer.hpp"

int main(void) {
// std::string tmp = "tcp://*:5556";
// auto contex = std::make_shared<zmq::context_t>(2);
// MQRouter mqRouter(contex, tmp, "router");
//  mqRouter.addWorker("wo");
// mqRouter.init();

  Components::WebsocketServer server(8081);
  server.run();

//std::cout << "hello module" << std::endl;






}


// #include <iostream>
// #include <regex>
// #include <string>

// int main() {
//     std::string jsonString1 = "[2,\"04d90767-8292-4be6-8c16-cc69d370635a\",\"Authorize\",{\"idTag\":\"6ACA6EDC\"}]";
//     std::string jsonString2 = "[2,\"4fbcd1287eeb4fa79588666465dc2cea\",\"GetConfiguration\",{\"key\":[]}]";

//     std::regex pattern("\\[(\\d),\"([\\w-]+)\",\"(.+)\",(.+)\\]");




//     std::smatch match;
//     if (std::regex_match(jsonString1, match, pattern)) {
//         std::cout << "Message Type: " << match[1].str() << std::endl;
//         std::cout << "UUID: " << match[2].str() << std::endl;
//         std::cout << "Command: " << match[3].str() << std::endl;
//         std::cout << "idTag: " << match[4].str() << std::endl;
//     } else {
//         std::cout << "No match found." << std::endl;
//     }

//     return 0;
// }
