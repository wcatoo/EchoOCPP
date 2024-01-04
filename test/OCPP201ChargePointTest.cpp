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
  Helper helper{};
  std::string test1{R"([2,"866ee0a4-d990-40de-8256-3798cf977609","StatusNotification",{"connectorId":1,"errorCode":"NoError","status":"Available","timestamp":"2023-12-19T08:28:29Z","vendorErrorCode":"0,0,0,0"}])"};
  if (std::optional<MessageCall> messageCall = helper.checkMessageCallValid(test1); messageCall  != std::nullopt) {
    std::cout << "message id: " << messageCall.value().getMessageId() << std::endl;
    std::cout << "Action: " << messageCall.value().getAction() << std::endl;
  } else {
    MessageErrorResponse messageErrorResponse;
    messageErrorResponse.setErrorCode(ProtocolError::FormatViolation);
    messageErrorResponse.setErrorDescription("");
    nlohmann::json j = nlohmann::json::object();
    messageErrorResponse.setErrorDetails(j);
    std::cout << messageErrorResponse.serializeMessage() << std::endl;
  }

//  EXPECT_TRUE(helper.checkOCPPMessageFormat(test1));
//  std::string test2{R"( [2,"866ee0a4-d990-40de-8256-3798cf977609","StatusNotification",{"connectorId":1,"errorCode":"NoError","status":"Available","timestamp":"2023-12-19T08:28:29Z","vendorErrorCode":"0,0,0,0"}])"};
//  EXPECT_FALSE(helper.checkOCPPMessageFormat(test2));
//  std::string test3{};
//  EXPECT_FALSE(helper.checkOCPPMessageFormat(test3));

}

}
