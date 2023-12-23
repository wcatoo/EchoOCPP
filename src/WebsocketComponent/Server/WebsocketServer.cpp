
#ifndef ECHOOCPP_IWEBSOCKETSERVER_CPP
#define ECHOOCPP_IWEBSOCKETSERVER_CPP
#include "WebsocketServer.hpp"
#include <functional>
#include <algorithm>

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
void WebsocketServer::sendPayload(const std::string & tResource, const std::string &tPayload) {
      this->mWSEndpoint.send(this->mConnectionHandlers[tResource], tPayload, websocketpp::frame::opcode::text);
}
void WebsocketServer::onOpen(websocketpp::connection_hdl tHandler) {
  auto tmp = this->mWSEndpoint.get_con_from_hdl(tHandler);
  this->mConnectionHandlers[tmp->get_resource()] = tHandler;
  std::for_each(this->mConnectionHandlers.begin(), this->mConnectionHandlers.end(), [](auto& keyValue){
    std::cout << keyValue.first << std::endl;

  });
//  for (auto i : this->mConnectionHandlers) {
//    std::cout << "add: " <<  i.first << std::endl;
//  }
}

auto WebsocketServer::onClose(websocketpp::connection_hdl tHandler) -> void {
  auto tmp = this->mWSEndpoint.get_con_from_hdl(tHandler);
  this->mConnectionHandlers.erase(tmp->get_resource());
  for (auto i : this->mConnectionHandlers) {
    std::cout << "remove: " << i.first << std::endl;
  }
}



}

#endif

