

#include "ChargePoint.hpp"
void ChargePoint::init() {
    this->mWebsocketManager = std::make_unique<Components::WebsocketClientManager>();
    // this->mWebsocketManager->mWebsocketClient.init();
    // this->mWebsocketManager->mWebsocketClient.connect("ws://124.222.224.186:8800");
    this->mWebsocketManager->init();
    
    // std::this_thread::sleep_for(std::chrono::seconds(3));
    // std::thread th([this]() {
    //     this->mWebsocketManager->mWebsocketClient.mWSEndpoint.run();
    // });

    std::this_thread::sleep_for(std::chrono::seconds(10));

    // std::cout << "here1" << std::endl;
    // this->mWebsocketManager->mWebsocketClient.stop();
    std::cout << "here2" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    this->mWebsocketManager->mWebsocketClient.connect("ws://124.222.224.186:8800");
    while (true) {
        std::cout << "asdsad" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
