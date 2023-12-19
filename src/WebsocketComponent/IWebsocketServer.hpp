//
// Created by 杨帆 on 2023/10/29.
//

#ifndef ECHOOCPP_IWEBSOCKETSERVER_HPP
#define ECHOOCPP_IWEBSOCKETSERVER_HPP

#include <string_view>
#include <thread>


namespace Components {
    /**
     * @brief Websocket server interface
     */
    class IWebsocketServer {
    public:
      virtual void init(int tPort) = 0;
//      virtual void logInfo(std::string_view tMessage) = 0;
//      virtual void logError(std::string_view tMessage) = 0;
    private:
        // Log component interface ptr
        // You can use your customize log class tu inherit this interface
//        std::unique_ptr<ILogComponent> mLogComponent;

    };
}

#endif//ECHOOCPP_IWEBSOCKETSERVER_HPP
