#pragma once
#include "201/DataType/Datatypes.hpp"
#include "../../../MessageQueue/protobufMessage.pb.h"
#include "201/Message/MessageRequest.hpp"
#include "../Devices/Configure/OCPP201ConfigureManager.hpp"
namespace OCPP201 {
class ComponentVariableConfigureManager {
public:
  OCPP201ConfigureManager mConfigureManager;

};
}