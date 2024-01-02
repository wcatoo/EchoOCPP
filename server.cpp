//#include "src/MessageQueue/MQRouter.hpp"
#include "app/CenterSystem/CoreSystem.hpp"
#include <string_view>
#include <algorithm>


int main(void) {

  CenterSystem::CoreSystem coreSystem;
  coreSystem.init();
  coreSystem.run();
  while (true);
}








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
