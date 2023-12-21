
#ifndef ECHOOCPP_WEBSOCKETCLIENT_CPP
#define ECHOOCPP_WEBSOCKETCLIENT_CPP
#include "WebsocketClient.hpp"

#include <utility>

void Components::WebsocketClient::init(const std::string &tAddress) {
  this->mWSEndpoint.init_asio();
  this->mWSEndpoint.start_perpetual();

//  this->mWSEndpoint.connect()

}
bool Components::WebsocketClient::setOnMessage(const std::function<void(const std::string&)>&& tOnMessage) {
  if (mStatus == WebsocketStatus::OPEN) {
    return false;
  }

  this->mOnMessage = std::move(tOnMessage);
  return true;
}
void Components::WebsocketClient::connect(const std::string &tURL) {
  websocketpp::lib::error_code errorCode;
  this->mWSEndpoint.set_message_handler(std::bind(&WebsocketClient::onMessage, this, std::placeholders::_1, std::placeholders::_2));
  this->mHandler = this->mWSEndpoint.get_connection(tURL, errorCode);
  if (errorCode) {
    std::cout << "> Connect initialization error: " << errorCode.message() << std::endl;
    return;
  }
  this->mWSEndpoint.connect(this->mHandler);
//  this->mWSEndpoint.set_message_handler([this](auto && PH1, auto && PH2) { onMessage(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2)); });
  std::thread th1([this]() {
    this->mWSEndpoint.run();
  });

  th1.detach();
  std::this_thread::sleep_for(std::chrono::seconds(1));

}

void Components::WebsocketClient::onMessage(websocketpp::connection_hdl tHandler,websocketpp::client<websocketpp::config::asio_client>::message_ptr tMessagePtr) {
  std::cout << "Received Message: " << tMessagePtr->get_payload() << std::endl;

  this->mWSEndpoint.send(tHandler, "client send  message",  tMessagePtr->get_opcode());
  std::this_thread::sleep_for(std::chrono::seconds(1));
  if (this->mOnMessage) {
    this->mOnMessage(tMessagePtr->get_payload());
  }

}

#endif