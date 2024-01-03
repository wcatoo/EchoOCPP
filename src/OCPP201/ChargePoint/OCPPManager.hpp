//
// Created by 杨帆 on 2024/1/2.
//

#ifndef ECHOOCPP_OCPPMANAGER_HPP
#define ECHOOCPP_OCPPMANAGER_HPP


#include "../../MessageQueue/MQDealer.hpp"
#include "../../MessageQueue/MQRouter.hpp"
namespace OCPP201 {
class OCPPManager {
public:
  void init();
  void start();
  void stop();


  void receiveMessageHandler(const std::string&);


private:
  std::unique_ptr<MQDealer> mWebsocketDealerPtr;


};
}
#endif // ECHOOCPP_OCPPMANAGER_HPP
