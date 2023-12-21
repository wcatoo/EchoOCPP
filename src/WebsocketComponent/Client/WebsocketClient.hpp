#ifndef ECHOOCPP_WEBSOCKETCLIENT_HPP
#define ECHOOCPP_WEBSOCKETCLIENT_HPP
#include "IWebsocketClient.hpp"
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include "../WebsocketStatus.hpp"

namespace Components {
class WebsocketClient : public IWebsocketClient{
public:
  void init(const std::string &tAddress) override;
  void connect(const std::string &tURL);
  bool setOnMessage(const std::function<void(const std::string&)>&& tOnMessage);
  void onMessage(websocketpp::connection_hdl,websocketpp::client<websocketpp::config::asio_client>::message_ptr);

  std::shared_ptr<websocketpp::connection<websocketpp::config::asio_client>::type> mHandler;
  websocketpp::client<websocketpp::config::asio_client> mWSEndpoint{};
private:
  std::function<void(const std::string&)> mOnMessage{};
  WebsocketStatus mStatus{WebsocketStatus::CLOSE};
};



}
#endif // ECHOOCPP_WEBSOCKETCLIENT_HPP
