//
// Created by 杨帆 on 2023/10/29.
//

#ifndef ECHOOCPP_IWEBSOCKETSERVER_HPP
#define ECHOOCPP_IWEBSOCKETSERVER_HPP

#include "WebsocketStatus.hpp"
#include <string_view>
#include <thread>
#include <functional>

namespace Components {
    /**
     * @brief Websocket server interface
     */
    class IWebsocketBase {
    public:
      virtual void init() = 0;
      virtual void run() = 0;
      virtual void stop() = 0;
      virtual void sendPayload(const std::string &, const std::string &) = 0;
      virtual bool setOnMessage(const std::function<void(const std::string&)>&& tOnMessage) = 0;
      virtual bool setOnOpen(const std::function<void()>&& tOnOpen) = 0;
      virtual bool setOnClose(const std::function<void()>&& tOnClose) = 0;
      virtual bool setOnFail(const std::function<void(const std::string&)>&& tOnFail) = 0;
    protected:
      WebsocketStatus mStatus{WebsocketStatus::CLOSE};
      std::function<void(const std::string&)> mOnMessage{};
      std::function<void(const std::string&)> mOnFail{};
      std::function<void()> mOnOpen{};
      std::function<void()> mOnClose{};

    };
}

#endif//ECHOOCPP_IWEBSOCKETSERVER_HPP
