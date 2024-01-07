//
// Created by 杨帆 on 2023/11/20.
//

#include "../src/OCPP201/ChargePoint/OCPPManager.hpp"
#include "../src/OCPP201/Utilies/Helper.hpp"
#include <gtest/gtest.h>
namespace OCPP201 {

class OCPP201ChargePoint : public ::testing::Test {
protected:
  void SetUp() override {}
  std::unique_ptr<OCPP201::OCPPManager> OCPPManager;
};

TEST_F(OCPP201ChargePoint, auto) {


  std::string test2{R"([3, "19223201", { "currentTime": "2013-02-01T20:53:32.486Z", "interval": 300, "status": "Accepted" } ])"};
  std::smatch matches;
  std::regex mPatternConf{R"lit(\s*\[\s*(\d+)\s*,\s*"([\w-]+)"\s*,\s*(.+)\s*\]\s*)lit"};
  if (std::regex_match(test2, matches, mPatternConf)) {
    std::cout << "Match message" << std::endl;
  } else {
    std::cout << "not match" << std::endl;
  }
  ChargingStationType chargingStationType;

  BootNotificationRequest bootNotificationRequest(BootReasonEnumType::ApplicationReset,
                                                  chargingStationType);
  OCPPManager->send(OCPP201Type::BootNotification, dynamic_cast<MessageCall*>(&bootNotificationRequest));

}

}
