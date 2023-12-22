
#ifndef ECHOOCPP_IWEBSOCKETSERVER_CPP
#define ECHOOCPP_IWEBSOCKETSERVER_CPP
#include "WebsocketServer.hpp"
#include <functional>

namespace Components {

void WebsocketServer::init(int tPort) {
  this->mWSEndpoint.init_asio();
  this->mWSEndpoint.listen(tPort);
  this->mWSEndpoint.set_message_handler([this](auto && PH1, auto && PH2) { on_message(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2)); });
  this->mWSEndpoint.set_open_handler([this](auto && PH1) { onOpen(std::forward<decltype(PH1)>(PH1)); });
  this->mWSEndpoint.set_close_handler([this](auto && PH1) {onClose(std::forward<decltype(PH1)>(PH1));});
  this->mWSEndpoint.set_reuse_addr(true);
//  this->mWSEndpoint.set_fail_handler()
  this->mWSEndpoint.start_accept();
  this->mWSEndpoint.run();
}
void WebsocketServer::sendPayload(const std::string &tPayload) {
//      this->mWSEndpoint.send(this->mWSEndpoint.get_connection(), tPayload, websocketpp::frame::opcode::text);
}
void WebsocketServer::onOpen(websocketpp::connection_hdl tHandler) {
  auto tmp = this->mWSEndpoint.get_con_from_hdl(tHandler);
}

void WebsocketServer::onClose(websocketpp::connection_hdl tHandler) {
  auto tmp = this->mWSEndpoint.get_con_from_hdl(tHandler);
}


}

#endif

