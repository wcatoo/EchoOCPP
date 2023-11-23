
#ifndef ECHOOCPP_WEBSOCKETSERVER_HPP
#define ECHOOCPP_WEBSOCKETSERVER_HPP
#include "IWebsocketServer.hpp"


namespace Components {

    class WebsocketServer : public IWebsocketServer{
        void init() override;
        void logInfo(std::string_view tMessage) override;
        void logError(std::string_view tMessage) override;
    };

}

#endif

