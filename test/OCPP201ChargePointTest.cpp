//
// Created by 杨帆 on 2023/11/20.
//

#include "../src/OCPP201/ChargePoint/OCPPManager.hpp"
#include "../src/OCPP201/Utilies/Helper.hpp"
#include <gtest/gtest.h>
#include <string>
namespace OCPP201 {

class OCPP201ChargePoint : public ::testing::Test {
protected:
  void SetUp() override {}
  std::unique_ptr<OCPP201::OCPPManager> ocppManager;
};

TEST_F(OCPP201ChargePoint, GetVariableRequest) {
    std::vector<GetVariableDataType> data;
    for (int i =0; i< 10; i++) {
        data.emplace_back();
    }
    GetVariablesRequest getVariablesRequest(data);
//    GetVariablesRequest tmp = nlohmann::json::parse(tt);
//    EXPECT_EQ(getVariablesRequest.getPayload(), tmp.getPayload());
}


}