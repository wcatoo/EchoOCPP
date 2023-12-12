//
// Created by 杨帆 on 2023/12/10.
//

#include "MQRouter.hpp"
MQRouter::MQRouter(int tContext, const std::string &tAddress) {
  this->mContext = zmq::context_t(tContext);
  this->mClientSocket = zmq::socket_t(this->mContext, zmq::socket_type::router);
  this->mClientSocket.bind(tAddress);
}
