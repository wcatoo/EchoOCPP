#ifndef ECHOOCPP_CORESYSTEM_HPP
#define ECHOOCPP_CORESYSTEM_HPP

#include "../../WebsocketComponent/Server/WebsocketServer.hpp"

namespace App
{
    class CoreSystem
    {
    private:
    Components::WebsocketServer mWebsocketServer;
    public:
        CoreSystem(/* args */);
        ~CoreSystem();
    };



    CoreSystem::~CoreSystem()
    {
    }

} // namespace App

#endif
