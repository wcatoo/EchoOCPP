#ifndef ECHOOCPP_WEBSOCKETCLIENTMANAGER_HPP
#define ECHOOCPP_WEBSOCKETCLIENTMANAGER_HPP
#include "WebsocketClient.hpp"
#include "../../MessageQueue/MQDealer.hpp"
#include "../../MessageQueue/protobufMessage.pb.h"


namespace Components {
class WebsocketClientManager
{
private:
public:
    WebsocketClientManager() = default;
    WebsocketClientManager(zmq::context_t *tContext, const std::string &tZMQAddress, const std::string &tZMQID);
    void init();
    
    std::unique_ptr<MQDealer> mMQRouterPtr;
    WebsocketClient mWebsocketClient;
};


}


#endif