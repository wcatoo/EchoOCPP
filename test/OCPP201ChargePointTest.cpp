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

 std::cout << "uuid: " <<  generateMessageId().substr(0,9) << std::endl;
//  ThreadPool  threadPool(10);
//
//  for (int i = 0; i < 20; i++) {
//    threadPool.enqueue([](int answer) {
//      return answer;
//    }, i);
//  }
//








}

}