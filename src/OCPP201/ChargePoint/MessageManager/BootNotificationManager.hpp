#ifndef ECHOOCPP_BOOTNOTIFICATIONMANAGER_HPP
#define ECHOOCPP_BOOTNOTIFICATIONMANAGER_HPP
#include "../../DataType/Datatypes.hpp"
#include <atomic>


namespace OCPP201 {
class BootNotificationManager {
public:
  BootNotificationManager() = default;
  BootNotificationManager(const std::string &tModel, const std::string &tVendorName){
    this->mBootNotificationRequest = BootNotificationRequest(BootReasonEnumType::PowerUp, ChargingStationType(tModel, tVendorName));
  }
  inline void setSerialNumber(const std::string &tValue) {
    this->mBootNotificationRequest.chargingStation.setSerialNumber(tValue.empty()?std::nullopt:std::optional<std::string>(tValue));
  }
  inline void setFirmwareVersion(const std::string &tValue) {
    this->mBootNotificationRequest.chargingStation.setFirmwareVersion(tValue.empty()?std::nullopt:std::optional<std::string>(tValue));
  }

  inline void setModel(const std::string &tValue) {
    this->mBootNotificationRequest.chargingStation.setModel(tValue);
  }
  inline void setVendorName(const std::string &tValue) {
    this->mBootNotificationRequest.chargingStation.setVendorName(tValue);
  }

  inline void setBootReason(BootReasonEnumType tReason) {
    this->mBootNotificationRequest.reason = tReason;
  }

  inline void setModem(const std::string &tIccid, const std::string &tImsi) {
    if (tIccid.empty() && tImsi.empty()) {
      this->mBootNotificationRequest.chargingStation.setModem(std::nullopt);
    } else {
      this->mBootNotificationRequest.chargingStation.setModem(std::optional<ModemType>(ModemType((IdentifierString(tIccid)), IdentifierString(tImsi))));
    }
  }

  RouterProtobufMessage getRequestMessage(const std::string &tDest) {
    RouterProtobufMessage routerProtobufMessage;
    routerProtobufMessage.set_data(this->mBootNotificationRequest.serializeMessage());
    routerProtobufMessage.set_uuid(this->mBootNotificationRequest.getMessageId());
    routerProtobufMessage.set_source("OCPP201");
    routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
    routerProtobufMessage.set_message_type(MessageType::REQUEST);
    routerProtobufMessage.set_dest(tDest);
    return routerProtobufMessage;
  }



  inline void setBootInterval(int tValue) {
    this->mBootInterval = tValue;
  }

  int getBootInterval() {
    return this->mBootInterval;
  }


  // boot is happening
  std::atomic_bool isBooting = false;
  // boot is finish, ocpp can receive message from CMCS
  // is boot status is pending, the charger station should receive GetVariablesReq and setVariableReq
  bool bootFinish = false;
private:
  BootNotificationRequest mBootNotificationRequest;
  int mBootInterval = 3;

};

}
#endif // ECHOOCPP_BOOTNOTIFICATIONMANAGER_HPP
