//
// Created by 杨帆 on 2024/1/2.
//

#ifndef ECHOOCPP_OCPPMANAGER_HPP
#define ECHOOCPP_OCPPMANAGER_HPP

#include <unordered_map>
#include <mutex>

#include "../../Devices/Connector.hpp"
#include "../../MessageQueue/MQDealer.hpp"
#include "../../MessageQueue/MQRouter.hpp"
#include "../Message/MessageRequest.hpp"
#include "../Message/MessageRespone.hpp"
#include "../Utilies/Helper.hpp"
#include "ThreadPool.hpp"
#include "../../Devices/Connector.hpp"
namespace OCPP201 {
class OCPPManager {
public:
  void init();
  void start();
  void stop();
  OCPPManager() = default;
  OCPPManager(zmq::context_t *tContext, const std::string &tAddress);

  void OCPP201MessageHandler(const RouterProtobufMessage & tMessage);
  void receiveMessageHandler(const RouterProtobufMessage & tMessage);
//  bool send(OCPP201Type tType, MessageCall *tCall, std::function<void()> tCallback = nullptr);
  bool send(const RouterProtobufMessage &tMessage, std::function<void(const RouterProtobufMessage &&)> tCallback = nullptr, bool isResponse = false);
  bool sendOCPPError(const std::string & tResource, ProtocolError tError, const std::string &tDetail, std::function<void()> tCallback = nullptr);


private:
  std::unique_ptr<MQDealer> mMQRouterPtr;
  // UUID | OCPPType | callback function
  std::unordered_map<std::string, std::pair<OCPP201Type, std::function<void()>>> mMessagesTrace;
  // if message timeout, it should be removed from trace
  std::map<std::chrono::time_point<std::chrono::system_clock>, std::string> mMessageTimeoutTrace;
  std::mutex mMessageTimeoutTraceMutex;

  Helper mHelper{};
  std::unique_ptr<ThreadPool> mThreadPoll;
  std::unordered_map<std::string, std::function<void(const RouterProtobufMessage &&)>> mMessageCallback;
  std::unordered_map<std::string, OCPP201Type> mOCPPMessageType;
  std::vector<Connector> mConnectors;

};




}
#endif // ECHOOCPP_OCPPMANAGER_HPP
