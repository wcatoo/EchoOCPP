//
// Created by 杨帆 on 2023/10/29.
//

#ifndef ECHOOCPP_IWEBSOCKETSERVER_HPP
#define ECHOOCPP_IWEBSOCKETSERVER_HPP

#include "WebsocketDefines.hpp"
#include <functional>
#include <string_view>
#include <thread>

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
      virtual bool setOnMessage(std::function<void(const WebsocketOnMessageInfo&)>&& tOnMessage) = 0;
      virtual bool setOnOpen(std::function<void()>&& tOnOpen) = 0;
      virtual bool setOnClose(std::function<void()>&& tOnClose) = 0;
      virtual bool setOnFail(std::function<void(const std::string&)>&& tOnFail) = 0;
    protected:
      WebsocketStatus mStatus{WebsocketStatus::CLOSE};
      std::function<void(const WebsocketOnMessageInfo&)> mOnMessage{};
      std::function<void(const std::string&)> mOnFail{};
      std::function<void()> mOnOpen{};
      std::function<void()> mOnClose{};

    };
}

#endif//ECHOOCPP_IWEBSOCKETSERVER_HPP
