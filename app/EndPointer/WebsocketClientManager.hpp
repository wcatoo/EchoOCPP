#ifndef ECHOOCPP_WEBSOCKETCLIENTMANAGER_HPP
#define ECHOOCPP_WEBSOCKETCLIENTMANAGER_HPP
#include "../../src/WebsocketComponent/Client/WebsocketClient.hpp"
#include "../../src/MessageQueue/MQDealer.hpp"
#include "../../src/MessageQueue/protobufMessage.pb.h"


namespace Components {
class WebsocketClientManager
{
private:
public:
    WebsocketClientManager() = default;
    WebsocketClientManager(zmq::context_t *tContext, const std::string &tZMQAddress, const std::string &tZMQID);
    void init();
    void start();
    
    std::unique_ptr<MQDealer> mMQRouterPtr;
    WebsocketClient mWebsocketClient;
    const std::string mZMQIdentity = "websocket";
};


}


#endif