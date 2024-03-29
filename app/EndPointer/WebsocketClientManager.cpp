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
        this->mMQRouterPtr->setReceiveCallBack([this](const InternalRouterMessage& tMessage){
            this->mWebsocketClient.sendPayload(tMessage.ocpp_data().data());
        }) ;
        this->mWebsocketClient.setOnOpen([this](){
            InternalRouterMessage routerProtobufMessage;
            routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_NETWORK_ONLINE);
            routerProtobufMessage.set_dest(ZMQIdentify::ocpp);
            routerProtobufMessage.set_source(ZMQIdentify::websocket);
            routerProtobufMessage.set_message_type(MessageType::NETWORK_ONLINE);
            if (this->mMQRouterPtr != nullptr) {
                this->mMQRouterPtr->send(routerProtobufMessage);
            } else {
                //TODO MQ router nullptr error
            }
        });
        this->mWebsocketClient.setOnClose([this](){
            InternalRouterMessage routerProtobufMessage;
            routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_NETWORK_OFFLINE);
            routerProtobufMessage.set_dest(ZMQIdentify::ocpp);
            routerProtobufMessage.set_source(ZMQIdentify::websocket);
            routerProtobufMessage.set_message_type(MessageType::NETWORK_OFFLINE);
            if (this->mMQRouterPtr != nullptr) {
                this->mMQRouterPtr->send(routerProtobufMessage);
            } else {
//                //TODO MQ router nullptr error
            }
        });
        this->mWebsocketClient.setOnFail([](const std::string &t){
            // TODO websocket connect fail handler
            std::cout << "websocket connect failed -> "  << t<< std::endl;
        });
         this->mWebsocketClient.setOnMessage([](WebsocketOnMessageInfo t){
             std::cout << "message: " << t.getPayload() << std::endl;
             InternalRouterMessage routerProtobufMessage;
             routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
             routerProtobufMessage.set_dest(ZMQIdentify::ocpp);
             routerProtobufMessage.set_source(ZMQIdentify::websocket);
             if (t.getPayload().size() > 2) {
                 switch (t.getPayload().at(1)) {
                     case '2':
                         routerProtobufMessage.set_message_type(MessageType::REQUEST);
                         break;
                     case '3':
                         routerProtobufMessage.set_message_type(MessageType::RESPONSE);
                         break;
                     case '4':
                         break;
                     default:
                         std::cout << t.getPayload() << " -> no OCPP message" << std::endl;
                         break;
                 }
                 routerProtobufMessage.mutable_ocpp_data()->set_data(t.getPayload());
             } else {
                 return ;
             }
         });
        this->mWebsocketClient.init();
        this->mWebsocketClient.connect("ws://124.222.224.186:8800");
//        this->mWebsocketClient.connect("ws://127.0.0.1:8080");
    }

    void WebsocketClientManager::start() {
        std::thread th([this](){
            this->mWebsocketClient.mWSEndpoint.run();
        });
        th.detach();
        this->mMQRouterPtr->start();

    }

}


