#ifndef ECHOOCPP_HEARTBEAT_HPP
#define ECHOOCPP_HEARTBEAT_HPP
#include "../DataType/Datatypes.hpp"
#include <thread>
#include <memory>
#include <atomic>
#include <functional>

namespace OCPP201
{
    class HeartBeatManager
    {
    public:
        HeartBeatManager() = default;
        HeartBeatManager(int tInterval)
        {
            this->mInterval = tInterval;
        }

        void start()
        {
            if (this->isRunning) {
                return;
            }
            this->mTimer = std::make_unique<std::thread>([this]()
                                                         {
                this->isRunning = true;
                std::this_thread::sleep_for(std::chrono::seconds(this->mInterval));
                while (this->isRunning && this->mHeartbeatHandler) {
                    this->mHeartbeatHandler();
                    std::this_thread::sleep_for(std::chrono::seconds(this->mInterval));
                } });
                this->mTimer->detach();
        }
        void stop() {
            this->isRunning = false;
        }
        void setHeartbeatHandler(std::function<void()> tHandler) {
            this->mHeartbeatHandler = tHandler;
        }
        RouterProtobufMessage getRequestMessage() {
            RouterProtobufMessage routerProtobufMessage;
            routerProtobufMessage.set_data(this->mHeartbeatRequest.serializeMessage());
            routerProtobufMessage.set_uuid(this->mHeartbeatRequest.getMessageId());
            routerProtobufMessage.set_source("OCPP201");
            routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
            routerProtobufMessage.set_message_type(MessageType::REQUEST);
            routerProtobufMessage.set_dest(this->mDest);
            return routerProtobufMessage;
        }
        std::string mDest;
        std::atomic_int mInterval{10};
    private:
        std::unique_ptr<std::thread> mTimer{nullptr};
        bool isRunning{false};
        // std::function<bool(const RouterProtobufMessage &tMessage,
        //                    std::function<void(const std::string &)> tCallback,
        //                    bool isResponse)>
        std::function<void()> mHeartbeatHandler{};

        HeartbeatRequest mHeartbeatRequest;



    };

}
#endif