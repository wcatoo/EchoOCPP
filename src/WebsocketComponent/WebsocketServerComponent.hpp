//
// Created by 杨帆 on 2023/10/29.
//

#ifndef ECHOOCPP_WEBSOCKETSERVER_HPP
#define ECHOOCPP_WEBSOCKETSERVER_HPP
#include "IWebsocketServer.hpp"


namespace Components {

    class WebsocketServer : public IWebsocketServer{
        void init() override;
        void info(std::string_view tMessage) override;
        void error(std::string_view tMessage) override;
    };

}

#endif//ECHOOCPP_IWEBSOCKETSERVER_HPP

