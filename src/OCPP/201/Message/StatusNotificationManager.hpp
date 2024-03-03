#ifndef ECHOOCPP_STATUSNOTIFICATION_HPP
#define ECHOOCPP_STATUSNOTIFICATION_HPP
#include "../DataType/Datatypes.hpp"
#include "Devices/Connector.hpp"
#include <functional>

namespace OCPP201 {
class StatusNotificationManager {
public:

  void setSendHandler(std::function<void()> tHandler) {
    this->mSendHandler = tHandler;
  }

  InternalRouterMessage getRequestMessage(const Connector &tConnector, int tevseId) {
    InternalRouterMessage routerProtobufMessage;
    this->mRequest.connectorId = tConnector.mConnectorId;
    this->mRequest.evseId = tevseId;
    this->mRequest.connectorStatus = tConnector.mConnectorStatus;
    this->mRequest.timestamp.setDateTime(std::chrono::system_clock::now());
    routerProtobufMessage.mutable_ocpp_data()->set_data(this->mRequest.toString());
    routerProtobufMessage.mutable_ocpp_data()->set_ocpp_type(this->mRequest.getAction());
    routerProtobufMessage.set_uuid(this->mRequest.getMessageId());
    routerProtobufMessage.set_source(ZMQIdentify::ocpp);
    routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
    routerProtobufMessage.set_message_type(MessageType::REQUEST);
    routerProtobufMessage.set_dest(ZMQIdentify::websocket);
    return routerProtobufMessage;
  }

private:
  StatusNotificationRequest mRequest;
  std::function<void()> mSendHandler{};

};
}
#endif