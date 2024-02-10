#include "WebsocketClientManager.hpp"
#include "MessageQueue/protobufMessage.pb.h"

namespace Components {
    WebsocketClientManager::WebsocketClientManager(zmq::context_t *tContext, 
                                                    const std::string &tZMQAddress, const std::string &tZMQID)
    {
        this->mMQRouterPtr = std::make_unique<MQDealer>(tContext, tZMQAddress, tZMQID);
        this->mMQRouterPtr->init();
    }

    void WebsocketClientManager::init() {
        this->mMQRouterPtr->setReceiveCallBack([this](const RouterProtobufMessage& tMessage){
            this->mWebsocketClient.sendPayload(tMessage.data());
        }) ;
        this->mWebsocketClient.setOnOpen([this](){
            RouterProtobufMessage routerProtobufMessage;
            routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_NETWORK_ONLINE);
            routerProtobufMessage.set_dest("OCPP201");
            routerProtobufMessage.set_source(this->mZMQIdentity);
            routerProtobufMessage.set_message_type(MessageType::NETWORK_ONLINE);
            routerProtobufMessage.set_data("websocket open");
            if (this->mMQRouterPtr != nullptr) {
                this->mMQRouterPtr->send(routerProtobufMessage);
            } else {
                //TODO MQ router nullptr error
            }
        });
        this->mWebsocketClient.setOnClose([this](){
            RouterProtobufMessage routerProtobufMessage;
            routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_NETWORK_OFFLINE);
            routerProtobufMessage.set_dest("OCPP201");
            routerProtobufMessage.set_source(this->mZMQIdentity);
            routerProtobufMessage.set_message_type(MessageType::NETWORK_OFFLINE);
            routerProtobufMessage.set_data("websocket close");
            if (this->mMQRouterPtr != nullptr) {
                this->mMQRouterPtr->send(routerProtobufMessage);
            } else {
//                //TODO MQ router nullptr error
            }
        });
        this->mWebsocketClient.setOnFail([](const std::string &t){
            std::cout << "fail" << std::endl;
        });
         this->mWebsocketClient.setOnMessage([](WebsocketOnMessageInfo t){
             std::cout << "message: " << t.getPayload() << std::endl;
         });
        this->mWebsocketClient.init();
        this->mWebsocketClient.connect("ws://124.222.224.186:8800");
    }

    void WebsocketClientManager::start() {
        std::thread th([this](){
            this->mWebsocketClient.mWSEndpoint.run();
        });
        th.detach();
        this->mMQRouterPtr->start();

    }

}


