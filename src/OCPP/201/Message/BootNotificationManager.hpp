#ifndef ECHOOCPP_BOOTNOTIFICATIONMANAGER_HPP
#define ECHOOCPP_BOOTNOTIFICATIONMANAGER_HPP
#include "201/DataType/Datatypes.hpp"
#include "../../../MessageQueue/protobufMessage.pb.h"
#include "201/Message/MessageRequest.hpp"
#include "../Devices/Configure/BaseInfo.hpp"
#include <atomic>


namespace OCPP201 {
class BootNotificationManager {
public:
  BootNotificationManager() = default;
  BootNotificationManager(const std::string &tModel, const std::string &tVendorName){
    this->mRequest = BootNotificationRequest(BootReasonEnumType::PowerUp, ChargingStationType(tModel, tVendorName));
  }
  inline void setSerialNumber(const std::string &tValue) {
    this->mRequest.chargingStation.setSerialNumber(tValue.empty() ? std::nullopt : std::optional<std::string>(tValue));
  }
  inline void setFirmwareVersion(const std::string &tValue) {
    this->mRequest.chargingStation.setFirmwareVersion(tValue.empty() ? std::nullopt : std::optional<std::string>(tValue));
  }

  inline void setModel(const std::string &tValue) {
    this->mRequest.chargingStation.setModel(tValue);
  }
  inline void setVendorName(const std::string &tValue) {
    this->mRequest.chargingStation.setVendorName(tValue);
  }

  inline void setBootReason(BootReasonEnumType tReason) {
    this->mRequest.reason = tReason;
  }

  inline void setModem(const std::string &tIccid, const std::string &tImsi) {
    if (tIccid.empty() && tImsi.empty()) {
      this->mRequest.chargingStation.setModem(std::nullopt);
    } else {
      this->mRequest.chargingStation.setModem(std::optional<ModemType>(ModemType((IdentifierString(tIccid)), IdentifierString(tImsi))));
    }
  }

  void setConfigure(const BaseInfo &tBaseInfo) {
      this->mRequest.chargingStation.setModel(tBaseInfo.model);
      this->mRequest.chargingStation.setVendorName(tBaseInfo.vendorName);
      this->mRequest.chargingStation.setSerialNumber(std::equal(tBaseInfo.serialNumber.begin(), tBaseInfo.serialNumber.end(),"")?std::nullopt:std::optional<std::string>(tBaseInfo.serialNumber));
      this->mRequest.chargingStation.setFirmwareVersion(std::equal(tBaseInfo.firmwareVersion.begin(), tBaseInfo.firmwareVersion.end(),"")?std::nullopt:std::optional<std::string>(tBaseInfo.firmwareVersion));
      this->setModem(tBaseInfo.iccid, tBaseInfo.imsi);
  }



  RouterProtobufMessage getRequestMessage(const std::string &tDest) {
    RouterProtobufMessage routerProtobufMessage;
    this->mRequest.build();
    routerProtobufMessage.set_data(this->mRequest.serializeMessage());
    routerProtobufMessage.set_uuid(this->mRequest.getMessageId());
    routerProtobufMessage.set_source("OCPP201");
    routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
    routerProtobufMessage.set_message_type(MessageType::REQUEST);
    routerProtobufMessage.set_dest(tDest);
    routerProtobufMessage.set_ocpp_type(this->mRequest.getAction());
    return routerProtobufMessage;
  }

  inline void setBootInterval(int tValue) {
    this->mBootInterval = tValue;
  }

  int getBootInterval() {
    return this->mBootInterval;
  }

  void release() {
    this->mBootInterval = 3;
    this->isBooting = false;
    this->bootFinish = false;
  }


  // boot is happening
  std::atomic_bool isBooting = false;
  // boot is finish, ocpp can receive message from CMCS
  // is boot status is pending, the charger station should receive GetVariablesReq and setVariableReq
  bool bootFinish = false;
private:
  BootNotificationRequest mRequest;
  int mBootInterval = 3;


};

}
#endif // ECHOOCPP_BOOTNOTIFICATIONMANAGER_HPP
