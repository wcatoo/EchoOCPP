#include "WebsocketClientManager.hpp"

namespace Components {
    WebsocketClientManager::WebsocketClientManager(zmq::context_t *tContext, 
                                                    const std::string &tZMQAddress, const std::string &tZMQID)
    {
        this->mMQRouterPtr = std::make_unique<MQDealer>(tContext, tZMQAddress, tZMQID);

    }

    void WebsocketClientManager::init() {
        if (this->mWebsocketClient.setOnOpen([](){
            std::cout << "open" << std::endl;
        })) {
            std::cout << "set open succ" << std::endl;
        } else {

            std::cout << "set open failed" << std::endl;
        }
        this->mWebsocketClient.setOnClose([](){
            std::cout << "close" << std::endl;
        });
        this->mWebsocketClient.setOnFail([](const std::string &t){
            std::cout << "fail" << std::endl;
        });
        // this->mWebsocketClient.setOnMessage([](const WebsocketOnMessageInfo &t){
        //     std::cout << "message: " << t.getPayload() << std::endl;
        // });
        this->mWebsocketClient.init();
        this->mWebsocketClient.connect("ws://124.222.224.186:8800");
        std::thread th([this](){
            this->mWebsocketClient.mWSEndpoint.run();
        });
        th.detach();
    }

}


