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

  std::string jsonString = R"(
{
  "components" : [
    {
      "componentName" : "OCPPCommCtrlr",
      "component" : [
        {
          "componentInstance" : null,
          "evse" : {
            "id" : 1
          },
          "variableName" : "asd",
          "variable" : [
            {
              "variableInstance" : "qwe",
              "value" : [
                {
                  "attributeValue" : "asd123",
                  "type" : "Actual"
                }
              ]
            }
          ]
        }
      ]
    }
  ]
}
)";
  ComponentManager componentManager;
  componentManager = nlohmann::json::parse(jsonString);
  nlohmann::json tmp = componentManager;
  std::cout << tmp.dump() << std::endl;


  EVSEType evseType;

  nlohmann::json json = evseType;
  EVSEType tt = nlohmann::json::parse(json.dump());

}
}