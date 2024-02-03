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

void print(std::function<void(const std::string &)> tmp) {
  tmp("tt");
}

TEST_F(OCPP201ChargePoint, auto) {

 std::cout << "uuid: " <<  Utility::generateMessageId().substr(0,9) << std::endl;

    //  ocppManager = std::make_unique<OCPPManager>();
    //  ocppManager->init();
    //   nlohmann::json json = ocppManager->mConfigureKeyGeneral;

// ocppManager = std::make_unique<OCPPManager>();
// ocppManager->init();
//  nlohmann::json json = ocppManager->mConfigureKeyGeneral;
//
// ConfigureKeyGeneral configureKeyGeneral = nlohmann::json::parse(json.dump());

// nlohmann::json json = ChargingStationType();
//
//std::cout << "json : " << json.dump() << std::endl;
//
//ChargingStationType chargingStationType = nlohmann::json::parse(json.dump());





}

}