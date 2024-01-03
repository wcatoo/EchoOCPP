

#include "OCPPRouter.hpp"
OCPP201::OCPPRouter::OCPPRouter(const std::string &tAddress,
                       const std::string &tIdentity) {

  this->mContext = zmq::context_t(1);
  this->mClientSocket = std::make_unique<zmq::socket_t>(this->mContext, zmq::socket_type::router);
  this->mClientSocket->set(zmq::sockopt::routing_id, tIdentity);
  this->mClientSocket->bind(tAddress);
}
void OCPP201::OCPPRouter::start() {

}
