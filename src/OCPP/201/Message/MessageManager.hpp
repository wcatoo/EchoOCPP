#ifndef ECHOOCPP_MESSAGEMANAGER_HPP
#define ECHOOCPP_MESSAGEMANAGER_HPP

#include "./BootNotificationManager.hpp"
#include "./HeartBeatManager.hpp"
#include "./StatusNotificationManager.hpp"


namespace OCPP201 {
    class MessageManager {
    public:
        MessageManager() = default;
        void init() {
        }
        BootNotificationManager mBootNotificationManager;
        HeartBeatManager mHeartBeatManager;
        StatusNotificationManager mStatusNotificationManager;
    };
}


#endif //ECHOOCPP_MESSAGEMANAGER_HPP
