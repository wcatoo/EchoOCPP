//
// Created by 杨帆 on 2024/1/2.
//

#ifndef ECHOOCPP_OCPPMANAGER_HPP
#define ECHOOCPP_OCPPMANAGER_HPP

#include <unordered_map>
#include <mutex>

#include "../../MessageQueue/MQDealer.hpp"
#include "../../MessageQueue/MQRouter.hpp"
#include "../Utilies/Helper.hpp"
#include "../Message/MessageRequest.hpp"
#include "../Message/MessageRespone.hpp"
namespace OCPP201 {
class OCPPManager {
public:
  void init();
  void start();
  void stop();


  void receiveMessageHandler(const std::string& tResource, const std::string & tMessage);
  bool send(OCPP201Type tType, MessageCall *tCall, std::function<void()> tCallback = nullptr);


private:
  std::unique_ptr<MQDealer> mWebsocketDealerPtr;
  // UUID | OCPPType | callback function
  std::unordered_map<std::string, std::pair<OCPP201Type, std::function<void()>>> mMessagesTrace;
  // if message timeout, it should be removed from trace
  std::map<std::chrono::time_point<std::chrono::system_clock>, std::string> mMessageTimeoutTrace;
  std::mutex mMessageTimeoutTraceMutex;

  Helper mHelper{};

};
}
#endif // ECHOOCPP_OCPPMANAGER_HPP
