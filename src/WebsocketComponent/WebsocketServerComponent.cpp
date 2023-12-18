
#ifndef ECHOOCPP_IWEBSOCKETSERVER_CPP
#define ECHOOCPP_IWEBSOCKETSERVER_CPP
#include "WebsocketServerComponent.hpp"
#include <functional>

namespace Components {

    void WebsocketServer::init(int tPort) {
      mWSEndpoint.init_asio();
      mWSEndpoint.listen(tPort);
      mWSEndpoint.set_message_handler(std::bind(&WebsocketServer::on_message, this, std::placeholders::_1, std::placeholders::_2));
      mWSEndpoint.start_accept();
      mWSEndpoint.run();
    }
//    void WebsocketServer::logInfo(std::string_view tMessage) {
//    }
//    void WebsocketServer::logError(std::string_view tMessage) {
//    }
}

#endif

