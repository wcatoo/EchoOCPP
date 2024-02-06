
#ifndef ECHOOCPP_WEBSOCKETCLIENT_CPP
#define ECHOOCPP_WEBSOCKETCLIENT_CPP
#include "WebsocketClient.hpp"

#include <utility>
namespace Components {

bool WebsocketClient::setOnFail(const std::function<void(const std::string &)> &&tOnFail){
  if (mStatus == WebsocketStatus::OPEN) {
    return false;
  }
  this->mOnFail = tOnFail;
  return true;
}

bool WebsocketClient::setOnMessage(const std::function<void(const WebsocketOnMessageInfo&)>&& tOnMessage) {
  if (mStatus == WebsocketStatus::OPEN) {
    return false;
  }
  this->mOnMessage = tOnMessage;
  return true;
}

bool WebsocketClient::setOnOpen(const std::function<void()>&& tOnOpen) {
  if (mStatus == WebsocketStatus::OPEN) {
    return false;
  }

  this->mOnOpen = tOnOpen;
  return true;

}
bool WebsocketClient::setOnClose(const std::function<void()>&& tOnClose) {
  if (mStatus == WebsocketStatus::OPEN) {
    return false;
  }

  this->mOnClose = tOnClose;
  return true;
}


//bool Components::WebsocketClient::
void WebsocketClient::connect(const std::string &tURL) {
  this->mUrl = tURL;
  websocketpp::lib::error_code errorCode;
  this->mHandler = this->mWSEndpoint.get_connection(tURL, errorCode);
  if (errorCode) {
    std::cout << "> Connect initialization error: " << errorCode.message() << std::endl;
    return;
  }
  this->mWSEndpoint.connect(this->mHandler);
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

void WebsocketClient::onMessage(websocketpp::connection_hdl tHandler,websocketpp::client<websocketpp::config::asio_client>::message_ptr tMessagePtr) {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  WebsocketOnMessageInfo messageInfo;
  messageInfo.setMessage(tMessagePtr->get_payload());
  messageInfo.setResource(this->mWSEndpoint.get_con_from_hdl(tHandler)->get_resource());
  if (this->mOnMessage) {
    this->mOnMessage(messageInfo);
  }

}

void WebsocketClient::onOpen(websocketpp::connection_hdl tHandler) {
  this->mStatus = WebsocketStatus::OPEN;
  std::cout << "onopen" << std::endl;
  if (this->mOnOpen) {
    this->mOnOpen();
    std::cout << "onopen callback " << std::endl;
  } else {
    std::cout << "onopen callback null" << std::endl;

  }
}

void WebsocketClient::onClose(websocketpp::connection_hdl tHandler){
//  this->mWSEndpoint.stop();
//  if (this->mWSEndpoint.stopped()) {
    this->mStatus = WebsocketStatus::CLOSE;
    if (this->mOnClose) {
      this->mOnClose();
    }
//  }
  std::this_thread::sleep_for(std::chrono::seconds(1));
}
void WebsocketClient::sendPayload(const std::string & tPayload, const std::string & tResource) {
  if (this->mStatus == WebsocketStatus::OPEN) {
    std::error_code errorCode = this->mHandler->send(tPayload, websocketpp::frame::opcode::text);
    if (errorCode) {
      std::cout << errorCode.message() << std::endl;
    }
  }
}

void WebsocketClient::sendPayload(const std::string & tPayload) {
  this->sendPayload(tPayload, "");
}

void WebsocketClient::onFail(websocketpp::connection_hdl tHandler) {
  std::cout << "websocket fail " << std::endl;
  auto tmp =  this->mWSEndpoint.get_con_from_hdl(tHandler);
  std::cout << tmp->get_ec().message() << std::endl;
  this->reconnect();
}

void WebsocketClient::reconnect() {
  this->connect(this->mUrl);
}


void WebsocketClient::run() {
  this->connect(this->mUrl);
  this->mWSEndpoint.run();
}

void WebsocketClient::stop() {
  this->mWSEndpoint.stop();
}
WebsocketClient::~WebsocketClient() {
  this->mWSEndpoint.stop();
}
void WebsocketClient::init() {
  this->mUrl = "ws://127.0.0.1:8888";
  this->mWSEndpoint.init_asio();
  this->mWSEndpoint.start_perpetual();
  this->mWSEndpoint.set_access_channels(websocketpp::log::alevel::all);
  this->mWSEndpoint.set_error_channels(websocketpp::log::elevel::all);
  this->mWSEndpoint.set_open_handler([this](auto && PH1) { onOpen(std::forward<decltype(PH1)>(PH1)); });
  this->mWSEndpoint.set_close_handler([this](auto && PH1) {onClose(std::forward<decltype(PH1)>(PH1));});
  this->mWSEndpoint.set_message_handler([this](auto && PH1, auto && PH2) { onMessage(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2)); });
  this->mWSEndpoint.set_fail_handler([this](auto && PH1) { onFail(std::forward<decltype(PH1)>(PH1)); });
  this->mWSEndpoint.set_reuse_addr(true);
}

}
#endif