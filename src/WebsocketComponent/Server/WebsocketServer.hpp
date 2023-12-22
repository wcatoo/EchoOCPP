
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

            auto client_id = con->get_handle();

            std::cout << "Received message from client " << str.get()->get_resource() << ": " << msg->get_payload() << std::endl;

            // Print the received message
            std::cout << "Received message: " << msg->get_payload() << std::endl;

            // Send a response back to the client
            this->mWSEndpoint.send(hdl, "Server received your message", websocketpp::frame::opcode::text);
//            this->sendPayload(msg->get_payload());
            if (this->mOnMessage) {
              this->mOnMessage(msg->get_payload());
            }
          } catch (const std::exception& e) {
            std::cerr << "Error processing message: " << e.what() << std::endl;
          }
        }

        void sendPayload(const std::string &tPayload);
        void onOpen(websocketpp::connection_hdl);
        void onClose(websocketpp::connection_hdl);
      private:
        websocketpp::server<websocketpp::config::asio> mWSEndpoint;
        std::function<void(const std::string &)> mOnMessage;
    };

}

#endif

