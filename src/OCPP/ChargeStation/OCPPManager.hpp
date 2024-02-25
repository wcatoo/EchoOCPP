//#ifndef ECHOOCPP_OCPPMANAGER_HPP
//#define ECHOOCPP_OCPPMANAGER_HPP
#pragma once
#include <unordered_map>
#include <mutex>

#include "../MessageQueue/MQDealer.hpp"
#include "201/Devices/EVSE.hpp"
#include "ThreadPool.hpp"
#include "Utilies/Utilies.hpp"
#include "Utilies/Helper.hpp"

#include "../Devices/Configure/OCPP201ConfigureManager.hpp"
// message manager
#include "201/Message/BootNotificationManager.hpp"
#include "201/Message/HeartBeatManager.hpp"
#include "201/Message/MessageManager.hpp"
#include "201/Message/StatusNotificationManager.hpp"

namespace OCPP {
// OCPP manager should be initial before websocket
class OCPPManager {
public:
  bool init();
  void start();
  void stop();
  OCPPManager() = delete;
  OCPPManager(zmq::context_t *tContext, const std::string &tAddress);
private:
  void setBaseInfo(BaseInfoType tType, const std::string &tValue);
  bool send(const RouterProtobufMessage &tMessage, std::function<void(const std::string &)> tCallback = nullptr, bool isResponse = false);
  bool sendOCPPError(const std::string &UUID, const std::string & tResource, ProtocolError tError, const std::string &tDetail, std::function<void()> tCallback = nullptr);
  void receiveMessageHandler(const RouterProtobufMessage & tMessage);
  void OCPP201MessageHandler(const RouterProtobufMessage & tMessage);
  void OCPP201RequestHandler(const std::string &tUUID, const std::string &tSource, OCPP201::OCPP201Type tType, const std::string &tMessage);
  std::unique_ptr<MQDealer> mMQRouterPtr;
  // if message timeout, it should be removed from trace
  std::map<std::chrono::time_point<std::chrono::system_clock>, std::string> mMessageTimeoutTrace;
  std::mutex mMessageTimeoutTraceMutex;


  Helper mHelper{};
  std::unique_ptr<ThreadPool> mThreadPoll;
  std::unordered_map<std::string, std::function<void(const std::string &)>> mMessageCallback;
  // UUID | OCPPType | callback function
  std::unordered_map<std::string, OCPP201::OCPP201Type> mOCPPMessageType;
  std::vector<OCPP201::EVSE> mEVSEs;

  // custome configure
  OCPP201ConfigureManager mConfigureManager;

  //Message Manager
  std::unique_ptr<OCPP201::MessageManager> mOCPP201MessageManager;




};




}
//#endif // ECHOOCPP_OCPPMANAGER_HPP
