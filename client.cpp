#include "app/EndPointer/ChargePoint.hpp"

//void printtt(const std::string &t) {
//  std::cout << t << std::endl;
//}
//
//
//void ttt(std::string_view tmp) {
//  printtt(tmp);
//}

int main(int argc, char **argv) {
  ChargePoint chargepoint;
  chargepoint.init();

  while (true) {
    std::cout << "11" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }


//
//  RouterProtobufMessage routerProtobufMessage;
//  routerProtobufMessage.set_uuid("sdad");
//  auto ocpp_data = routerProtobufMessage.mutable_ocpp_data();
//  ocpp_data->set_data("sadd");
//
//
//  std::cout << routerProtobufMessage.SerializeAsString().size() << std::endl;
//



  return 0;
}




