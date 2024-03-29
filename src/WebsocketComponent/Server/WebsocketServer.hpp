
#ifndef ECHOOCPP_WEBSOCKETSERVER_HPP
#define ECHOOCPP_WEBSOCKETSERVER_HPP
#include "../IWebsocketBase.hpp"

#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

namespace Components {

typedef websocketpp::server<websocketpp::config::asio> server_t;

class WebsocketServer : public IWebsocketBase{
public:
  WebsocketServer() = default;
  WebsocketServer(int tPort);
  ~WebsocketServer();

  void init() override;
  void run() override;
  void stop() override;
  void setPort(std::uint16_t tPort){this->mPort = tPort;}



  void sendPayload(const std::string &, const std::string &) override;
  bool setOnMessage(std::function<void(const WebsocketOnMessageInfo&)>&& tOnMessage) override;
  bool setOnOpen(std::function<void()>&& tOnOpen) override;
  bool setOnClose(std::function<void()>&& tOnClose) override;
  bool setOnFail(std::function<void(const std::string&)>&& tOnFail) override;
private:
  void onOpen(websocketpp::connection_hdl);
  void onClose(websocketpp::connection_hdl);
  void onFail(websocketpp::connection_hdl);
  void onMessage(websocketpp::connection_hdl hdl, server_t::message_ptr msg);

  websocketpp::server<websocketpp::config::asio> mWSEndpoint{};
  std::unordered_map<std::string, websocketpp::connection_hdl> mConnectionHandlers;
  std::uint16_t mPort{8888};
  WebsocketOnMessageInfo mMessageInfo;
};

}

#endif

