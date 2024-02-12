#ifndef ECHOOCPP_STATUSNOTIFICATION_HPP
#define ECHOOCPP_STATUSNOTIFICATION_HPP
#include "../../DataType/Datatypes.hpp"
#include <functional>

namespace OCPP201 {
class StatusNotificationManager {
    public:

    void setSendHandler(std::function<void()> tHandler) {
        this->mSendHandler = tHandler;
    }


    RouterProtobufMessage getRequestMessage(const Connector &tConnector) {
        RouterProtobufMessage routerProtobufMessage;
        this->mRequest.connectorId = tConnector.mConnectorId;
        this->mRequest.evseId = tConnector.mEVSEId;
        this->mRequest.connectorStatus = tConnector.mConnectorStatus;
        this->mRequest.timestamp.setDateTime(std::chrono::system_clock::now());
        routerProtobufMessage.set_data(this->mRequest.serializeMessage());
        routerProtobufMessage.set_uuid(this->mRequest.getMessageId());
        routerProtobufMessage.set_source("OCPP201");
        routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
        routerProtobufMessage.set_message_type(MessageType::REQUEST);
        routerProtobufMessage.set_dest(this->mDest);
        routerProtobufMessage.set_ocpp_type(this->mRequest.getAction());
        std::cout << "serial message: " << routerProtobufMessage.SerializeAsString() <<std::endl;
        return routerProtobufMessage;
    }

    std::string mDest{};
    private:
    StatusNotificationRequest mRequest;
    std::function<void()> mSendHandler{};

};
}
#endif