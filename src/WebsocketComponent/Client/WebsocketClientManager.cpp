#include "WebsocketClientManager.hpp"

namespace Components {
    WebsocketClientManager::WebsocketClientManager(zmq::context_t *tContext, 
                                                    const std::string &tZMQAddress, const std::string &tZMQID)
    {
        this->mMQRouterPtr = std::make_unique<MQDealer>(tContext, tZMQAddress, tZMQID);
    }

}


