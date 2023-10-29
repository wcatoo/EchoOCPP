//
// Created by 杨帆 on 2023/10/29.
//

#ifndef ECHOOCPP_IWEBSOCKETSERVER_HPP
#define ECHOOCPP_IWEBSOCKETSERVER_HPP

#include <string_view>
#include <thread>

#include "LogComponent/ILogComponent.hpp"

namespace Components {
    /**
     * @brief Websocket server interface
     */
    class IWebsocketServer {
    public:
    private:
        // Log component interface ptr
        // You can use your customize log class tu inherit this interface
        std::unique_ptr<ILogComponent> mLogComponent;

    };
}

#endif//ECHOOCPP_IWEBSOCKETSERVER_HPP
