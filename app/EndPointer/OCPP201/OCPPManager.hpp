//
// Created by 杨帆 on 2024/1/2.
//

#ifndef ECHOOCPP_OCPPMANAGER_HPP
#define ECHOOCPP_OCPPMANAGER_HPP


//#include "../../../src/MessageQueue/MQDealer.hpp"
//#include "../../../src/MessageQueue/MQRouter.hpp"
#include "MQDealer.hpp"
#include "MQRouter.hpp"
namespace OCPP201 {
class OCPPManager {
public:


private:
  std::unique_ptr<MQRouter> mCoreRouterPtr;
  std::unique_ptr<MQDealer> mWebsocketDealerPtr;

};
}
#endif // ECHOOCPP_OCPPMANAGER_HPP
