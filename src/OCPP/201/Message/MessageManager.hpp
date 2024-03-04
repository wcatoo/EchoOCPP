#ifndef ECHOOCPP_MESSAGEMANAGER_HPP
#define ECHOOCPP_MESSAGEMANAGER_HPP

#include "../Devices/Configure/OCPP201ConfigureManager.hpp"
#include "BootNotificationManager.hpp"
#include "ComponentVariableManager.hpp"
#include "Devices/EVSE.hpp"
#include "HeartBeatManager.hpp"
#include "StatusNotificationManager.hpp"
#include "Utilies/ThreadPool.hpp"
#include "../Devices/RealTimeData.hpp"
#include "../MessageQueue/MQStatus.hpp"
#include "../DataInterface/InterfaceType.hpp"
namespace OCPP201 {
class ResetScheduleEvent {
public:
  bool resetChargingStation{false};
  int evseId{false};
};
class MessageManager {
private:
  std::vector<ResetScheduleEvent> mResetScheduleEvents;
  std::function<bool(const std::string &)> isUUIDExist;
  std::function<void(RouterPackage &&)> send;
  std::shared_ptr<ThreadPool> mThreadPool;
  OCPP201ConfigureManager mConfigureManager;
  std::vector<EVSE> mEVSEs;
  RealTimeDataManager mRealTimeDataManager;
  std::function<void (MessageErrorResponse &errorResponse, const ZMQIdentify &tDest)> sendOCPPErrorMessage;
  BootNotificationManager mBootNotificationManager;
  HeartBeatManager mHeartbeatManager;
  StatusNotificationManager mStatusNotificationManager;
public:
  MessageManager() = default;
  void init() {
    this->mConfigureManager.init();
  }
  void setIsUUIDExist(std::function<bool(const std::string&)> tCallback) {
    this->isUUIDExist = tCallback;
  }
  void setSendMessage(std::function<void(RouterPackage &&)> callback) {
    this->send = callback;
  }

  void sendOCPPMessage(const std::string &tUUID, ZMQIdentify tDest, std::string_view tMessage,
                       MessageType messageType, OCPP201Type ocpp201Type,
                       std::function<void(const std::string&)> tSuccessCallback = nullptr,
                       std::function<void()> tFailedCallback = nullptr
                       );
  void setSendOCPPError(std::function<void(MessageErrorResponse &, const ZMQIdentify)> tCallback) {
    this->sendOCPPErrorMessage = tCallback;

  }
  void setThreadPoolRef(std::shared_ptr<ThreadPool> threadPool) {
    this->mThreadPool = threadPool;
  }

  void bootHandler(const InternalRouterMessage &tMessage);

  void getBaseReportHandler(std::string_view tUUID, const ZMQIdentify tSource,
                            std::string_view tMessage);
  void getVariableHandler(std::string_view tUUID, const ZMQIdentify tSource,
                          std::string_view tMessage);
  void setVariableHandler(std::string_view tUUID, const ZMQIdentify tSource,
                          std::string_view tMessage);

  void setNetworkProfileReqHandler(std::string_view tUUID, const ZMQIdentify tDest,
                                   std::string_view tMessage);

  void resetReqHandler(std::string_view tUUID, const ZMQIdentify tDest,
                       std::string_view tMessage);


};




}
#endif //ECHOOCPP_MESSAGEMANAGER_HPP
