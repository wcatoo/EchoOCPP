//
// Created by 杨帆 on 2024/1/2.
//

#ifndef ECHOOCPP_OCPPMANAGER_HPP
#define ECHOOCPP_OCPPMANAGER_HPP


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


private:
  std::unique_ptr<MQDealer> mWebsocketDealerPtr;

  Helper mHelper{};



};
}
#endif // ECHOOCPP_OCPPMANAGER_HPP
