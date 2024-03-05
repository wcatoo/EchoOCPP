
#include "../src/OCPP/201/DataType/Datatypes.hpp"

#include <gtest/gtest.h>
#include <memory>
#include "openssl/sha.h"


namespace OCPP201 {

class OCPP201DatatypesTest : public ::testing::Test {
protected:
  void SetUp() override{
  }
};
TEST_F(OCPP201DatatypesTest, ACChargingParametersType) {
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

TEST_F(OCPP201DatatypesTest, AdditionalInfoType) {
  AdditionalInfoType additionalInfoType1;
  nlohmann::json json1 = additionalInfoType1;
  EXPECT_EQ(json1.dump(), R"({"additionalIdToken":"","type":""})");
  AdditionalInfoType additionalInfoType2 = json1;
  EXPECT_EQ(additionalInfoType1, additionalInfoType2);
  std::string meg{R"({"additionalIdToken":"","type":""})"};
  EXPECT_NO_THROW(additionalInfoType1 = nlohmann::json::parse(meg));
  meg = R"({"additionalIdToken":""})";
  additionalInfoType1 = nlohmann::json::parse(meg);
  EXPECT_EQ(additionalInfoType1, additionalInfoType2);
}
std::string sha256(const std::string& input) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, input.c_str(), input.length());
  SHA256_Final(hash, &sha256);

  std::stringstream ss;
  for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
  }
  return ss.str();
}
TEST_F(OCPP201DatatypesTest, ModemType) {
  ModemType modemType(std::optional<IdentifierString>("a"),std::optional<IdentifierString>("b") );
  nlohmann::json j = modemType;
  modemType = nlohmann::json::parse(j.dump());
  if (j.contains("imsi")) {
    j.erase("imsi");
  }

  std::cout << sha256("123abcdef") << std::endl;




}




}
