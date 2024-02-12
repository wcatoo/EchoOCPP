//
// Created by 杨帆 on 2024/1/2.
//

#ifndef ECHOOCPP_OCPPMANAGER_HPP
#define ECHOOCPP_OCPPMANAGER_HPP

#include <unordered_map>
#include <mutex>

#include "../../Devices/Connector.hpp"
#include "../../MessageQueue/MQDealer.hpp"
#include "../Message/MessageRequest.hpp"
#include "../Message/MessageRespone.hpp"
#include "../Utilies/Helper.hpp"
#include "../Utilies/Utilies.hpp"
#include "ThreadPool.hpp"

#include "../ConfigureKey/ConfigureKeyGeneral.hpp"

// message manager
#include "./MessageManager/BootNotificationManager.hpp"
#include "../../Devices/Configure/ConfigureManager.hpp"
#include "./MessageManager/HeartBeatManager.hpp"
#include "./MessageManager/StatusNotificationManager.hpp"


namespace OCPP201 {
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
  bool sendOCPPError(const std::string & tResource, ProtocolError tError, const std::string &tDetail, std::function<void()> tCallback = nullptr);
  void receiveMessageHandler(const RouterProtobufMessage & tMessage);
  void OCPP201MessageHandler(const RouterProtobufMessage & tMessage);
void OCPP201RequestHandler(const std::string &tUUID, OCPP201Type tType, const std::string &tMessage);
        std::unique_ptr<MQDealer> mMQRouterPtr;
  // UUID | OCPPType | callback function
  std::unordered_map<std::string, std::pair<OCPP201Type, std::function<void()>>> mMessagesTrace;
  // if message timeout, it should be removed from trace
  std::map<std::chrono::time_point<std::chrono::system_clock>, std::string> mMessageTimeoutTrace;
  std::mutex mMessageTimeoutTraceMutex;

  Helper mHelper{};
  std::unique_ptr<ThreadPool> mThreadPoll;
  std::unordered_map<std::string, std::function<void(const std::string &)>> mMessageCallback;
  std::unordered_map<std::string, OCPP201Type> mOCPPMessageType;
  std::vector<Connector> mConnectors;

  // custome configure
  ConfigureManager mConfigureManager;

  // configure key
  ConfigureKeyGeneral mConfigureKeyGeneral{};

  //Message Manager
  std::unique_ptr<BootNotificationManager> mBootNotificationManager;
  HeartBeatManager mHeartbeatManager;
  StatusNotificationManager mStatusNotificationManager;


};




}
#endif // ECHOOCPP_OCPPMANAGER_HPP
