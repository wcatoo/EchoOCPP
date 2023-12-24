#ifndef ECHOOCPP_WEBSOCKETCLIENT_HPP
#define ECHOOCPP_WEBSOCKETCLIENT_HPP
#include "../IWebsocketBase.hpp"
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include "../WebsocketStatus.hpp"

namespace Components {
class WebsocketClient : public IWebsocketBase{
public:
  WebsocketClient() = delete;
  WebsocketClient(const std::string &tAddress);
  ~WebsocketClient();

  void run() override;
  void connect(const std::string &tURL);
  void sendPayload(const std::string &, const std::string &) override;
  void sendPayload(const std::string &);
  bool setOnMessage(const std::function<void(const std::string&)>&& tOnMessage) override;
  bool setOnOpen(const std::function<void()>&& tOnOpen) override;
  bool setOnClose(const std::function<void()>&& tOnClose) override;
  bool setOnFail(const std::function<void(const std::string&)>&& tOnFail) override;

  std::shared_ptr<websocketpp::connection<websocketpp::config::asio_client>::type> mHandler;
  websocketpp::client<websocketpp::config::asio_client> mWSEndpoint{};
private:
  void onMessage(websocketpp::connection_hdl,websocketpp::client<websocketpp::config::asio_client>::message_ptr);
  void onOpen(websocketpp::connection_hdl);
  void onClose(websocketpp::connection_hdl);
  void onFail(websocketpp::connection_hdl);
  void reconnect();
  std::string mUrl{};
};



}
#endif // ECHOOCPP_WEBSOCKETCLIENT_HPP
