#include "../src/OCPP/ChargeStation/OCPPManager.hpp"
#include "201/Message/MessageRequest.hpp"
#include <gtest/gtest.h>
#include <string>
namespace OCPP201 {

class OCPP201ChargePoint : public ::testing::Test {
protected:
  void SetUp() override {}
  std::unique_ptr<OCPP201::OCPPManager> ocppManager;
};

TEST_F(OCPP201ChargePoint, GetVariableRequest) {}

TEST_F(OCPP201ChargePoint, SetVariablesRequest) {
}
}