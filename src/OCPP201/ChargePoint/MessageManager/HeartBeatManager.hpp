#ifndef ECHOOCPP_HEARTBEAT_HPP
#define ECHOOCPP_HEARTBEAT_HPP
#include "../../DataType/Datatypes.hpp"
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

        void init()
        {
            this->mTimer = std::make_unique<std::thread>([this]()
                                                         {
                this->isRunning = true;
                std::this_thread::sleep_for(std::chrono::seconds(this->mInterval));
                while (this->isRunning && this->mHeartbeatHandler) {
                    this->mHeartbeatHandler();
                    std::this_thread::sleep_for(std::chrono::seconds(this->mInterval));
                } });
        }
    private:

        std::unique_ptr<std::thread> mTimer{nullptr};
        std::atomic_int mInterval{10};
        bool isRunning{false};
        // std::function<bool(const RouterProtobufMessage &tMessage,
        //                    std::function<void(const std::string &)> tCallback,
        //                    bool isResponse)>
        std::function<void()> mHeartbeatHandler{};
    };
}
#endif