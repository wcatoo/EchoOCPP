#ifndef ECHOOCPP_BOOTNOTIFICATIONMANAGER_HPP
#define ECHOOCPP_BOOTNOTIFICATIONMANAGER_HPP
#include "../../DataType/Datatypes.hpp"


namespace OCPP201 {
class BootNotificationManager {
public:
  BootNotificationRequest networkOnline(BootReasonEnumType tReason, const ChargingStationType & tChargingStationType) {
    BootNotificationRequest bootNotificationRequest(tReason, tChargingStationType);
    return bootNotificationRequest;
  }
private:
  bool isBoot{false};
};

}
#endif // ECHOOCPP_BOOTNOTIFICATIONMANAGER_HPP
