#ifndef ECHOOCPP_DEVICEDATAINTERFACE_HPP
#define ECHOOCPP_DEVICEDATAINTERFACE_HPP
#include <optional>
#include <string>
#include <ranges>
#include "InterfaceType.hpp"
#include "../MessageQueue/protobufMessage.pb.h"
#include "../MessageQueue/MQDealer.hpp"
#include "../Devices/EVSE.hpp"


class DeviceDataInterface {
private:
  std::unique_ptr<MQDealer> mMQRouterPtr;
  std::vector<EVSE> mEVSE;
public:
  DeviceDataInterface(zmq::context_t *tContext, const std::string &tAddress);
  void init();
  void start();
  void updateEVSE(const EVSE &tevse);
  void sendConnectorData(const ZMQIdentify tDest, int tevseId);
//  void setConnectorData(RouterProtobufConnectorData &tData);
//  void setConnectorStatusNotification(RouterProtobufConnectorData &tData);


};

#endif // ECHOOCPP_DEVICEDATAINTERFACE_HPP
