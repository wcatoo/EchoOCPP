#include "app/EndPointer/ChargePoint.hpp"

int main(int argc, char **argv) {
  ChargePoint chargepoint;
  chargepoint.init();

  while (true) {
    std::cout << "11" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  // Components::WebsocketClient wbe;
  // wbe.init();
  // wbe.connect("ws://124.222.224.186:8800");
  // wbe.mWSEndpoint.run();




  return 0;
}




