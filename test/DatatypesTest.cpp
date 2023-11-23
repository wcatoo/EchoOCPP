//
// Created by 杨帆 on 2023/11/20.
//


#include "OCPP201/Datatypes.hpp"


#include <gtest/gtest.h>
#include <memory>

class DatatypesTest : public ::testing::Test {
protected:
  void SetUp() override{
  }
};


TEST_F(DatatypesTest, auto) {
  ACChargingParametersType acParams;

//  acParams.to_json(tjson, acParams);

  nlohmann::json tJson = nlohmann::json::parse(R"({"energyAmount":1000,"evMaxCurrent":50,"evMaxVoltage":240})");
  acParams = tJson;
  std::cout << tJson << std::endl;

  APNType apnType;
  apnType.apnAuthentication = APNAuthenticationEnumType::AUTO;

  apnType.apn = "a";

  nlohmann::json tjson = apnType;

  APNType tt = tjson;

  std::cout << tjson << std::endl;



}
