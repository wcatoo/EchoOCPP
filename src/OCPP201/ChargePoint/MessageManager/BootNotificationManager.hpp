#ifndef ECHOOCPP_BOOTNOTIFICATIONMANAGER_HPP
#define ECHOOCPP_BOOTNOTIFICATIONMANAGER_HPP
#include "../../DataType/Datatypes.hpp"


namespace OCPP201 {
class BootNotificationManager {
public:
  BootNotificationManager(const std::string &tModel, const std::string &tVendorName){
    this->mBootNotificationRequest = BootNotificationRequest(BootReasonEnumType::PowerUp, ChargingStationType(tModel, tVendorName));
  }
  void setSerialNumber(const std::string &tSerialNum) {
    this->mBootNotificationRequest.chargingStation.setSerialNumber(tSerialNum);
  }
  void setFirmwareVersion(const std::string &tVersion) {
    this->mBootNotificationRequest.chargingStation.setFirmwareVersion(tVersion);
  }


  RouterProtobufMessage& getRequest() {
  }

private:
  bool isBoot{false};
  BootNotificationRequest mBootNotificationRequest;
};

}
#endif // ECHOOCPP_BOOTNOTIFICATIONMANAGER_HPP
