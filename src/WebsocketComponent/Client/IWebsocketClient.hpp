//
// Created by 杨帆 on 2023/12/19.
//

#ifndef ECHOOCPP_IWEBSOCKETCLIENT_HPP
#define ECHOOCPP_IWEBSOCKETCLIENT_HPP
#include <string>

namespace Components {
/**
     * @brief Websocket client interface
 */
class IWebsocketClient {
public:
  virtual void init(const std::string &tAddress) = 0;
  //      virtual void logInfo(std::string_view tMessage) = 0;
  //      virtual void logError(std::string_view tMessage) = 0;
private:
  // Log component interface ptr
  // You can use your customize log class tu inherit this interface
  //        std::unique_ptr<ILogComponent> mLogComponent;

};
}
#endif // ECHOOCPP_IWEBSOCKETCLIENT_HPP
