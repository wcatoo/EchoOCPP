
#ifndef ECHOOCPP_IWEBSOCKETSERVER_CPP
#define ECHOOCPP_IWEBSOCKETSERVER_CPP
#include "WebsocketServer.hpp"
#include <algorithm>
#include <iostream>

namespace Components {

void WebsocketServer::sendPayload(const std::string & tPayload, const std::string & tResource = "") {
      this->mWSEndpoint.send(this->mConnectionHandlers[tResource], tPayload, websocketpp::frame::opcode::text);
}
void WebsocketServer::onOpen(websocketpp::connection_hdl tHandler) {
  auto tmp = this->mWSEndpoint.get_con_from_hdl(tHandler);
  this->mConnectionHandlers[tmp->get_resource()] = tHandler;
  std::for_each(this->mConnectionHandlers.begin(), this->mConnectionHandlers.end(), [](auto& keyValue){
    std::cout << keyValue.first << std::endl;
  });
  if (this->mOnOpen) {
    this->mOnOpen();
  }

}

auto WebsocketServer::onClose(websocketpp::connection_hdl tHandler) -> void {
  auto tmp = this->mWSEndpoint.get_con_from_hdl(tHandler);
  this->mConnectionHandlers.erase(tmp->get_resource());
  for (auto i : this->mConnectionHandlers) {
    std::cout << "remove: " << i.first << std::endl;
  }
}
void WebsocketServer::onFail(websocketpp::connection_hdl tHandler) {
  std::cout << "websocket fail " << std::endl;
  auto tmp =  this->mWSEndpoint.get_con_from_hdl(tHandler);
  std::cout << tmp->get_ec().message() << std::endl;
}

bool WebsocketServer::setOnFail(const std::function<void(const std::string &)> &&tOnFail){
  if (this->mStatus == WebsocketStatus::OPEN) {
    return false;
  }
  this->mOnFail = tOnFail;
  return true;
}

bool WebsocketServer::setOnMessage(const std::function<void(const WebsocketOnMessageInfo&)>&& tOnMessage) {
  if (mStatus == WebsocketStatus::OPEN) {
    return false;
  }
  this->mOnMessage = tOnMessage;
  return true;
}

bool WebsocketServer::setOnOpen(const std::function<void()>&& tOnOpen) {
  if (mStatus == WebsocketStatus::OPEN) {
    return false;
  }

  this->mOnOpen = tOnOpen;
  return true;

}
bool WebsocketServer::setOnClose(const std::function<void()>&& tOnClose) {
  if (mStatus == WebsocketStatus::OPEN) {
    return false;
  }

  this->mOnClose = tOnClose;
  return true;
}

void WebsocketServer::onMessage(websocketpp::connection_hdl hdl, server_t::message_ptr msg) {
  try {
    server_t::connection_ptr con = this->mWSEndpoint.get_con_from_hdl(hdl);
    auto str = con->get_uri();

    auto client_id = con->get_handle();


    std::cout << "origin: " << con->get_origin() << std::endl;
    std::cout << "Received message from client " << str.get()->get_resource() << ": " << msg->get_payload() << std::endl;

    // Print the received message
    std::cout << "Received message: " << msg->get_payload() << std::endl;
    WebsocketOnMessageInfo websocketOnMessageInfo;
    websocketOnMessageInfo.setMessage(msg->get_payload());
    websocketOnMessageInfo.setResource(con->get_uri()->get_resource());

    if (this->mOnMessage) {
      this->mOnMessage(websocketOnMessageInfo);
    }
  } catch (const std::exception& e) {
    std::cerr << "Error processing message: " << e.what() << std::endl;
  }
}
void WebsocketServer::run() {
  std::cout << "server run: port -> " << this->mPort << std::endl;
  this->mWSEndpoint.run();
}
void WebsocketServer::stop() {
  this->mWSEndpoint.stop();
}

WebsocketServer::WebsocketServer(int tPort) {
  this->mWSEndpoint.init_asio();
  this->mWSEndpoint.listen(tPort);
  this->mWSEndpoint.set_message_handler([this](auto && PH1, auto && PH2) { onMessage(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2)); });
  this->mWSEndpoint.set_open_handler([this](auto && PH1) { onOpen(std::forward<decltype(PH1)>(PH1)); });
  this->mWSEndpoint.set_close_handler([this](auto && PH1) {onClose(std::forward<decltype(PH1)>(PH1));});
  this->mWSEndpoint.set_reuse_addr(true);
  this->mWSEndpoint.set_fail_handler([this](auto && PH1) { onFail(std::forward<decltype(PH1)>(PH1)); });
  this->mWSEndpoint.start_accept();
}

WebsocketServer::~WebsocketServer() {
  this->mWSEndpoint.stop();
}
void WebsocketServer::init() {
  this->mWSEndpoint.init_asio();
  this->mWSEndpoint.listen(this->mPort);
  std::cout << "port: " << this->mPort << std::endl;
  this->mWSEndpoint.set_message_handler([this](auto && PH1, auto && PH2) { onMessage(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2)); });
  this->mWSEndpoint.set_open_handler([this](auto && PH1) { onOpen(std::forward<decltype(PH1)>(PH1)); });
  this->mWSEndpoint.set_close_handler([this](auto && PH1) {onClose(std::forward<decltype(PH1)>(PH1));});
  this->mWSEndpoint.set_reuse_addr(true);
  this->mWSEndpoint.set_fail_handler([this](auto && PH1) { onFail(std::forward<decltype(PH1)>(PH1)); });
  this->mWSEndpoint.start_accept();

}

}
#endif

