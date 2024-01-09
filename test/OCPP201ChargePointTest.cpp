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



  ChargingStationType chargingStationType;
  //
  BootNotificationRequest bootNotificationRequest(BootReasonEnumType::ApplicationReset,
                                                  chargingStationType);

  std::cout << bootNotificationRequest.getPayload() << std::endl;
  Helper helper;

  std::string tt{R"({"chargingStation":{"model":"","vendorName":""},"reason":"ApplicationReset","a":false})"};
  auto t = helper.checkOCPPJsonSchema(OCPP201Type::BootNotification, tt, MessageMethod::Request);
  if (t.has_value()) {
    std::cout << t.value() << std::endl;
  }
//  std::string tmp{R"({
//"$schema": "http://json-schema.org/draft-06/schema#",
//"$id": "urn:OCPP:Cp:2:2020:3:BootNotificationRequest",
//"comment": "OCPP 2.0.1 FINAL",
//"definitions": {
//  "CustomDataType": {
//    "description": "This class does not get 'AdditionalProperties = false' in the schema generation, so it can be extended with arbitrary JSON properties to allow adding custom data.",
//    "javaType": "CustomData",
//    "type": "object",
//    "properties": {
//      "vendorId": {
//        "type": "string",
//        "maxLength": 255
//      }
//    },
//    "required": [
//      "vendorId"
//    ]
//  },
//  "BootReasonEnumType": {
//    "description": "This contains the reason for sending this message to the CSMS.\r\n",
//    "javaType": "BootReasonEnum",
//    "type": "string",
//    "additionalProperties": false,
//    "enum": [
//      "ApplicationReset",
//      "FirmwareUpdate",
//      "LocalReset",
//      "PowerUp",
//      "RemoteReset",
//      "ScheduledReset",
//      "Triggered",
//      "Unknown",
//      "Watchdog"
//    ]
//  },
//  "ChargingStationType": {
//    "description": "Charge_ Point\r\nurn:x-oca:ocpp:uid:2:233122\r\nThe physical system where an Electrical Vehicle (EV) can be charged.\r\n",
//    "javaType": "ChargingStation",
//    "type": "object",
//    "additionalProperties": false,
//    "properties": {
//      "customData": {
//        "$ref": "#/definitions/CustomDataType"
//      },
//      "serialNumber": {
//        "description": "Device. Serial_ Number. Serial_ Number\r\nurn:x-oca:ocpp:uid:1:569324\r\nVendor-specific device identifier.\r\n",
//        "type": "string",
//        "maxLength": 25
//      },
//      "model": {
//        "description": "Device. Model. CI20_ Text\r\nurn:x-oca:ocpp:uid:1:569325\r\nDefines the model of the device.\r\n",
//        "type": "string",
//        "maxLength": 20
//      },
//      "modem": {
//        "$ref": "#/definitions/ModemType"
//      },
//      "vendorName": {
//        "description": "Identifies the vendor (not necessarily in a unique manner).\r\n",
//        "type": "string",
//        "maxLength": 50
//      },
//      "firmwareVersion": {
//        "description": "This contains the firmware version of the Charging Station.\r\n\r\n",
//        "type": "string",
//        "maxLength": 50
//      }
//    },
//    "required": [
//      "model",
//      "vendorName"
//    ]
//  },
//  "ModemType": {
//    "description": "Wireless_ Communication_ Module\r\nurn:x-oca:ocpp:uid:2:233306\r\nDefines parameters required for initiating and maintaining wireless communication with other devices.\r\n",
//    "javaType": "Modem",
//    "type": "object",
//    "additionalProperties": false,
//    "properties": {
//      "customData": {
//        "$ref": "#/definitions/CustomDataType"
//      },
//      "iccid": {
//        "description": "Wireless_ Communication_ Module. ICCID. CI20_ Text\r\nurn:x-oca:ocpp:uid:1:569327\r\nThis contains the ICCID of the modem’s SIM card.\r\n",
//        "type": "string",
//        "maxLength": 20
//      },
//      "imsi": {
//        "description": "Wireless_ Communication_ Module. IMSI. CI20_ Text\r\nurn:x-oca:ocpp:uid:1:569328\r\nThis contains the IMSI of the modem’s SIM card.\r\n",
//        "type": "string",
//        "maxLength": 20
//      }
//    }
//  }
//},
//"type": "object",
//"additionalProperties": false,
//"properties": {
//  "customData": {
//    "$ref": "#/definitions/CustomDataType"
//  },
//  "chargingStation": {
//    "$ref": "#/definitions/ChargingStationType"
//  },
//  "reason": {
//    "$ref": "#/definitions/BootReasonEnumType"
//  }
//},
//"required": [
//  "reason",
//  "chargingStation"
//]
//})"};
//  nlohmann::json_schema::json_validator  jsonValidator;
//  jsonValidator.set_root_schema(nlohmann::json::parse(tmp));
//  try {
//    std::string tt{R"({"chargingStation":{"model":"","vendorName":""},"reason":"ApplicationReset"})"};
//    jsonValidator.validate(nlohmann::json::parse(tt));
//    std::cout << "Validation succeeded\n";
//  } catch (const std::exception &e) {
//    std::cerr << "Validation failed, here is why: " << e.what() << "\n";
//  }
//



}

}