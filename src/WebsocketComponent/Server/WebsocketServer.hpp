
#ifndef ECHOOCPP_WEBSOCKETSERVER_HPP
#define ECHOOCPP_WEBSOCKETSERVER_HPP
#include "../IWebsocketBase.hpp"

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

namespace Components {

typedef websocketpp::server<websocketpp::config::asio> server_t;

class WebsocketServer : public IWebsocketBase{
public:
  WebsocketServer() = delete;
  WebsocketServer(int tPort);
  ~WebsocketServer();

  void run() override;


  void sendPayload(const std::string &, const std::string &) override;
  bool setOnMessage(const std::function<void(const std::string&)>&& tOnMessage) override;
  bool setOnOpen(const std::function<void()>&& tOnOpen) override;
  bool setOnClose(const std::function<void()>&& tOnClose) override;
  bool setOnFail(const std::function<void(const std::string&)>&& tOnFail) override;
private:
  void onOpen(websocketpp::connection_hdl);
  void onClose(websocketpp::connection_hdl);
  void onFail(websocketpp::connection_hdl);
  void onMessage(websocketpp::connection_hdl hdl, server_t::message_ptr msg);

  websocketpp::server<websocketpp::config::asio> mWSEndpoint{};
  std::unordered_map<std::string, websocketpp::connection_hdl> mConnectionHandlers;
};

}

#endif

