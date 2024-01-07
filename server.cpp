//#include "src/MessageQueue/MQRouter.hpp"
#include "app/CenterSystem/CoreSystem.hpp"

int main(void) {

//  CenterSystem::CoreSystem coreSystem;
//  coreSystem.init();
//  coreSystem.run();
//  while (true);

  std::chrono::time_point<std::chrono::system_clock> tmp = std::chrono::system_clock::now();

  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::chrono::time_point<std::chrono::system_clock> tmp2 = std::chrono::system_clock::now();

  if (tmp2 > tmp) {
    std::cout << "ok" << std::endl;
  } else {
    std::cout << "no" << std::endl;

  }



}
