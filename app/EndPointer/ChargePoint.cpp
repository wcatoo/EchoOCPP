#include "ChargePoint.hpp"
void ChargePoint::init() {
    this->mZMQContext = zmq::context_t(1);
    this->mCoreRouter = std::make_unique<MQRouter>(&this->mZMQContext, "inproc://core_router", "coreRouter");
    this->mCoreRouter->init();
    this->mCoreRouter->setCoreRouterFunction([this](){
        zmq::pollitem_t  items[] = {
                {this->mCoreRouter->mDealerSocket, 0, ZMQ_POLLIN, 0}
        };
        zmq::message_t id;
        zmq::message_t request;
        while (true) {
            id.rebuild();
            request.rebuild();
            zmq::poll(items, 1, std::chrono::milliseconds(100));
            std::cout << "router loop" << std::endl;
            if (items[0].revents & ZMQ_POLLIN) {
                bool isFrameBroken = false;
                auto idReturn = this->mCoreRouter->mDealerSocket.recv(id, zmq::recv_flags::none);
                std::string idStr(static_cast<char*>(id.data()), id.size());
                if (!idReturn.has_value()) {
                    isFrameBroken = true;
                }
                //       empty frame
                auto emptyFrame = this->mCoreRouter->mDealerSocket.recv(request, zmq::recv_flags::none);
                if (!emptyFrame.has_value()) {
                    isFrameBroken = true;
                }
                auto dataFrame = this->mCoreRouter->mDealerSocket.recv(request, zmq::recv_flags::none);
                if (!dataFrame.has_value()) {
                    isFrameBroken = true;
                }
                InternalRouterMessage routerMessage;
                if (routerMessage.ParseFromArray(request.data(), static_cast<int>(request.size())) && !isFrameBroken) {
                    this->mCoreRouter->mDealerSocket.send(zmq::message_t(routerMessage.dest()), zmq::send_flags::sndmore);
                    this->mCoreRouter->mDealerSocket.send(request, zmq::send_flags::none);
                }
            }
        }
    });
    this->mCoreRouter->run();
    //OCPP201
//    this->mOCPPManager = std::make_unique<OCPP::OCPPCore>(&this->mZMQContext, "inproc://core_router");
//    this->mOCPPManager->init();
//    this->mOCPPManager->start();
    // websocket
    this->mWebsocketManager = std::make_unique<Components::WebsocketClientManager>(&this->mZMQContext, "inproc://core_router","websocket");
    this->mWebsocketManager->init();
    this->mWebsocketManager->start();

    while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
