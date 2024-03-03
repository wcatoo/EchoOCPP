#include "../src/OCPP/ChargeStation/OCPPCore.hpp"
#include "201/Message/MessageRequest.hpp"
#include "../src/Devices/RealTimeData.hpp"
#include <gtest/gtest.h>
#include <string>
namespace OCPP201 {

class OCPP201ChargePoint : public ::testing::Test {
protected:
  void SetUp() override {}
  std::unique_ptr<OCPP201::OCPPCore> ocppManager;
};

TEST_F(OCPP201ChargePoint, GetVariableRequest) {}

TEST_F(OCPP201ChargePoint, SetVariablesRequest) {
}

TEST_F(OCPP201ChargePoint, ACChargingParametersType) {
  ACChargingParametersType acChargingParametersType1;
  nlohmann::json j1 = acChargingParametersType1;
  EXPECT_EQ(j1.dump(), "{\"energyAmount\":0,\"evMaxCurrent\":0,\"evMaxVoltage\":0,\"evMinCurrent\":0}");
  ACChargingParametersType acChargingParametersType2 = nlohmann::json::parse(j1.dump());
  EXPECT_EQ(acChargingParametersType1,acChargingParametersType2);
  acChargingParametersType1.setEvMaxCurrent(1);
  EXPECT_FALSE(acChargingParametersType1 == acChargingParametersType2);
  ACChargingParametersType acChargingParametersType3 = nlohmann::json::parse(R"({"energyAmount":1,"evMaxCurrent":2,"evMaxVoltage":3,"evMinCurrent":4})");
  ACChargingParametersType acChargingParametersType4;
  acChargingParametersType4.setEvMaxCurrent(2);
  acChargingParametersType4.setEnergyAmount(1);
  acChargingParametersType4.setEvMaxVoltage(3);
  acChargingParametersType4.setEvMinCurrent(4);
  EXPECT_EQ(acChargingParametersType3, acChargingParametersType4);
  // parse error
  std::string meg{R"({"energyAmount":"0","evMaxCurrent":{},"evMaxVoltage":0.0,"evMinCurrent":0}
)"};
  EXPECT_NO_THROW(acChargingParametersType1 = nlohmann::json::parse(meg));
}

TEST_F(OCPP201ChargePoint, AdditionalInfoType) {
  AdditionalInfoType additionalInfoType1;
  nlohmann::json json1 = additionalInfoType1;
  EXPECT_EQ(json1.dump(), R"({"additionalIdToken":"","type":""})");
  AdditionalInfoType additionalInfoType2 = json1;
  EXPECT_EQ(additionalInfoType1, additionalInfoType2);


  std::cout << Utility::generateMessageId() << std::endl;

}





}