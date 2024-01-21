#include "app/EndPointer/ChargePoint.hpp"
#include "app/EndPointer/CoreSystem.hpp"

int main(int argc, char **argv) {
//  ChargePoint chargePoint;
  EndPointer::CoreSystem coreSystem;

  coreSystem.init();
  coreSystem.run();
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(10));
  }
  return 0;
}




