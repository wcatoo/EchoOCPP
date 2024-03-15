//#ifndef ECHOOCPP_OCPPMANAGER_HPP
//#define ECHOOCPP_OCPPMANAGER_HPP
#pragma once
#include <unordered_map>
#include <mutex>

#include "../MessageQueue/MQDealer.hpp"
#include "Devices/EVSE.hpp"
#include "Utilies/Helper.hpp"
#include "Utilies/ThreadPool.hpp"
#include "Utilies/Utilies.hpp"

#include "../Devices/Configure/OCPP201ConfigureManager.hpp"
// message manager
#include "201/Message/BootNotificationManager.hpp"
#include "201/Message/HeartBeatManager.hpp"
#include "201/Message/MessageManager.hpp"
#include "201/Message/StatusNotificationManager.hpp"

namespace OCPP {
// OCPP manager should be initial before websocket

class ConnectorMeasuredValue {
public:


};




class OCPPCore {
public:
  bool init();
  void start();
  void stop();
  OCPPCore() = delete;
  OCPPCore(zmq::context_t *tContext, const std::string &tAddress);

  void startChargingEvent(int tEVSEId, int tConnectorId);

  void stopChargingEvent(int tEVSEId, int tConnectorId);

  void connectorConnectEVEvent(int tEVSEId, int tConnectorId);

  void connectorDisconnectEVEvent(int tEVSEId, int tConnectorId);

  void EVSENotificationEvent(int tEVSEId, int tConnectorId, OCPP201::ReasonEnumType tReason);

  void updateMeterValueEvent(const Meter &tMeter, int tEVSEId, int tConnectorId);

  void updateMeasurandValueEvent(int tEVSEId, int tConnectorId, float tValue, OCPP201::MeasurandEnumType tType);

  void heartbeatEvent();

private:

  std::shared_ptr<RealTimeDataManager> mDeviceMeasurandManager;
  void setBaseInfo(BaseInfoType tType, const std::string &tValue);
//  bool send(const InternalRouterMessage &tMessage, std::function<void(const std::string &)> tCallback = nullptr);
  void send(RouterPackage &tPackage);
  void send(RouterPackage &&tPackage);
//  bool sendOCPPError(const std::string &UUID, const std::string & tResource, ProtocolError tError, const std::string &tDetail, std::function<void()> tCallback = nullptr);
  bool sendOCPPError(MessageErrorResponse &errorResponse, const ZMQIdentify tDest);
  void receiveMessageHandler(const InternalRouterMessage & tMessage);
  void OCPP201MessageHandler(const InternalRouterMessage & tMessage);
  void OCPP201RequestHandler(const std::string &tUUID, const ZMQIdentify tDest, OCPP201::OCPP201Type tType, const std::string &tMessage);
  bool isUUIDExist(const std::string &);
  inline bool isEVSEIdValid(int tEVSEId) {
      return tEVSEId < this->mDeviceMeasurandManager->EVSEs.size();
  }
  inline bool isConnectorIdValid(int tEVSEId, int tConnectorId) {
      return tConnectorId < this->mDeviceMeasurandManager->EVSEs.at(tEVSEId).mConnectors.size();
  }
  inline EVSE* getEVSE(int tEVSEId) {
      return isEVSEIdValid(tEVSEId) ? &(this->mDeviceMeasurandManager->EVSEs.at(tEVSEId)) : nullptr;
  }
  inline Connector* getConnector(int tEVSEId, int tConnectorId) {
      return isConnectorIdValid(tEVSEId, tConnectorId) ? &(this->getEVSE(tEVSEId)->mConnectors.at(tConnectorId)) : nullptr;

  }



  Helper mHelper{};
  std::shared_ptr<ThreadPool> mThreadPoll;
//  // UUID , callback
//  std::unordered_map<std::string, std::function<void(const std::string &)>> mMessageCallback;
  // UUID , Router package
  std::unordered_map<std::string, RouterPackage> mRouterPackagesTrace;
  // if message timeout, it should be removed from trace
  // time , UUID
  std::map<std::chrono::time_point<std::chrono::system_clock>, std::string> mMessageTimeoutTrace;
  // UUID , OCPPType
  std::unordered_map<std::string, OCPP201::OCPP201Type> mOCPPMessageType;

  std::mutex mMessageTimeoutTraceMutex;

  //Message Manager
  std::unique_ptr<OCPP201::MessageManager> mOCPP201MessageManager;
  std::unique_ptr<MQDealer> mMQRouterPtr;

};




}
//#endif // ECHOOCPP_OCPPMANAGER_HPP
