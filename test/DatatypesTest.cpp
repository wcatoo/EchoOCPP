//
// Created by 杨帆 on 2023/11/20.
//


#include "OCPP201/Datatypes.hpp"


#include <gtest/gtest.h>
#include <memory>

namespace OCPP201 {

class DatatypesTest : public ::testing::Test {
protected:
  void SetUp() override{
  }

  AuthorizationData authorizationData;
};



TEST_F(DatatypesTest, auto) {


//  CertificateHashDataType certificateHashDataType(HashAlgorithmEnumType::SHA256, "1", "2", "3");
//  CertificateHashDataChainType certificateHashDataChainType(GetCertificateIdUseEnumType::CSMSRootCertificate,
//                                                            certificateHashDataType);
//  nlohmann::json tJson = certificateHashDataChainType;

  nlohmann::json t = {{"certificateHashData", 1}, {"certificateType", "CSMSRootCertificate"}};
  CertificateHashDataChainType tmp = t;
  nlohmann::json tt = tmp;
    std::cout << tt << std::endl;

//  authorizationData.setIdToken(IdTokenType());
//  authorizationData = AuthorizationData(IdTokenType());
//  nlohmann::json authorizationDataJson = authorizationData;
//  std::cout << authorizationDataJson.dump() << std::endl;
  //  OCPP201::ACChargingParametersType acParams;
  //
  ////  acParams.to_json(tjson, acParams);
  //
  //  nlohmann::json tJson = nlohmann::json::parse(R"({"energyAmount":1000,"evMaxCurrent":50,"evMaxVoltage":240})");
  //  acParams = tJson;
  //  std::cout << tJson << std::endl;
  //
  //  OCPP201::APNType apnType;
  //  apnType.apnAuthentication = OCPP201::APNAuthenticationEnumType::AUTO;
  //
  //
  //  nlohmann::json tjson = apnType;
  //
  //  OCPP201::APNType tt = tjson;
  //
  //  std::cout << tjson << std::endl;



}
}
