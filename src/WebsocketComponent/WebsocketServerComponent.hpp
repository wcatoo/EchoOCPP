
#ifndef ECHOOCPP_WEBSOCKETSERVER_HPP
#define ECHOOCPP_WEBSOCKETSERVER_HPP
#include "IWebsocketServer.hpp"

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

namespace Components {

typedef websocketpp::server<websocketpp::config::asio> server_t;

    class WebsocketServer : public IWebsocketServer{
    public:
        void init(int tPort) override;
//        void logInfo(std::string_view tMessage) override;
//        void logError(std::string_view tMessage) override;
        void on_message(websocketpp::connection_hdl hdl, server_t::message_ptr msg) {
          try {
            server_t::connection_ptr con = this->mWSEndpoint.get_con_from_hdl(hdl);
            auto str = con->get_uri();

            // 获取连接的唯一标识符
            auto client_id = con->get_handle();

            std::cout << "Received message from client " << str.get()->get_resource() << ": " << msg->get_payload() << std::endl;

            // Print the received message
            std::cout << "Received message: " << msg->get_payload() << std::endl;

            // Send a response back to the client
            this->mWSEndpoint.send(hdl, "Server received your message", websocketpp::frame::opcode::text);
          } catch (const std::exception& e) {
            std::cerr << "Error processing message: " << e.what() << std::endl;
          }
        }
      private:
        websocketpp::server<websocketpp::config::asio> mWSEndpoint;
//        std::unique_ptr<MQRouter> mMQRouter;
    };

}

#endif

