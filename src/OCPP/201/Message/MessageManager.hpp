#ifndef ECHOOCPP_MESSAGEMANAGER_HPP
#define ECHOOCPP_MESSAGEMANAGER_HPP

#include "BootNotificationManager.hpp"
#include "HeartBeatManager.hpp"
#include "StatusNotificationManager.hpp"
#include "ComponentVariableManager.hpp"
#include "Utilies/ThreadPool.hpp"
#include "../Devices/Configure/OCPP201ConfigureManager.hpp"
#include "201/Devices/EVSE.hpp"



namespace OCPP201 {
class MessageManager {
private:
  std::function<void(const RouterProtobufMessage&, std::function<void(const std::string &)>)> send;
  std::shared_ptr<ThreadPool> mThreadPool;
  OCPP201ConfigureManager mConfigureManager;
  std::vector<OCPP201::EVSE> mEVSEs;
  std::function<void (MessageErrorResponse &errorResponse, const std::string &tSource)> sendOCPPErrorMessage;
  BootNotificationManager mBootNotificationManager;
  HeartBeatManager mHeartbeatManager;
  StatusNotificationManager mStatusNotificationManager;
public:
  MessageManager() = default;
  void init() {
    this->mConfigureManager.init();
  }
  void setSendMessage(std::function<void(const RouterProtobufMessage&, std::function<void(const std::string &)>)> callback) {
    this->send = callback;
  }
  void setSendOCPPError(std::function<void(MessageErrorResponse &, const std::string &)> tCallback) {
    this->sendOCPPErrorMessage = tCallback;

  }
  void setThreadPoolRef(std::shared_ptr<ThreadPool> threadPool) {
    this->mThreadPool = threadPool;
  }

  void bootHandler(const RouterProtobufMessage &tMessage);

  void getBaseReportHandler(const std::string &tUUID, const std::string &tSource, const std::string  &tMessage);
  void getVariableHandler(const std::string &tUUID, const std::string &tSource, const std::string &tMessage);
  void setVariableHandler(const std::string &tUUID, const std::string &tSource, const std::string &tMessage);


};




}
#endif //ECHOOCPP_MESSAGEMANAGER_HPP
