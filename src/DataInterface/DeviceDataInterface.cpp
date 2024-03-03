#include "DeviceDataInterface.hpp"
DeviceDataInterface::DeviceDataInterface(zmq::context_t *tContext,
                                         const std::string &tAddress) {
  this->mMQRouterPtr = std::make_unique<MQDealer>(tContext, tAddress, "OCPP201");
}

void DeviceDataInterface::init() {
  this->mMQRouterPtr->init();

}
void DeviceDataInterface::start() {
  this->mMQRouterPtr->start();
}


void DeviceDataInterface::updateEVSE(const EVSE &tevse) {
  if (tevse.id <= this->mEVSE.size()) {
    this->mEVSE.emplace(this->mEVSE.begin(), tevse);
  }
}
void DeviceDataInterface::sendConnectorData(const ZMQIdentify tDest, int tevseId) {
  InternalRouterMessage routerProtobufMessage;
  routerProtobufMessage.set_source(ZMQIdentify::interface);
  routerProtobufMessage.set_dest(tDest);
  std::for_each(this->mEVSE.begin()+1, this->mEVSE.end(), [this,&routerProtobufMessage,tevseId](const EVSE &tevse){
        std::for_each(tevse.mConnectors.begin()+1, tevse.mConnectors.end(), [this,&routerProtobufMessage, tevseId](const Connector &tConnector){
            auto data = routerProtobufMessage.mutable_connector_data();
            data->set_evse_id(tevseId);
            data->set_connector_id(tConnector.mConnectorId);
            if (tConnector.mMeter.energy_Wh.has_value()) {
              data->set_energy(tConnector.mMeter.energy_Wh.value());
            }

            if (tConnector.mMeter.l1_watt_W.has_value()) {
              data->set_l1_watt_w(tConnector.mMeter.l1_watt_W.value());
            }

            if (tConnector.mMeter.l2_watt_W.has_value()) {
              data->set_l2_watt_w(tConnector.mMeter.l2_watt_W.value());
            }

            if (tConnector.mMeter.l3_watt_W.has_value()) {
              data->set_l3_watt_w(tConnector.mMeter.l3_watt_W.value());
            }

            if (tConnector.mMeter.l1_l2_watt_W.has_value()) {
              data->set_l1_l2_watt_w(tConnector.mMeter.l1_l2_watt_W.value());
            }

            if (tConnector.mMeter.l2_l3_watt_W.has_value()) {
              data->set_l2_l3_watt_w(tConnector.mMeter.l2_l3_watt_W.value());
            }

            if (tConnector.mMeter.l3_l1_watt_W.has_value()) {
              data->set_l3_l1_watt_w(tConnector.mMeter.l3_l1_watt_W.value());
            }

            if (tConnector.mMeter.l1_n_watt_W.has_value()) {
              data->set_l1_n_watt_w(tConnector.mMeter.l1_n_watt_W.value());
            }

            if (tConnector.mMeter.l2_n_watt_W.has_value()) {
              data->set_l2_n_watt_w(tConnector.mMeter.l2_n_watt_W.value());
            }

            if (tConnector.mMeter.l3_n_watt_W.has_value()) {
              data->set_l3_n_watt_w(tConnector.mMeter.l3_n_watt_W.value());
            }

            if (tConnector.mMeter.neutral_watt_W.has_value()) {
              data->set_neutral_watt_w(tConnector.mMeter.neutral_watt_W.value());
            }

            if (tConnector.mMeter.l1_ampere_A.has_value()) {
              data->set_l1_ampere_a(tConnector.mMeter.l1_ampere_A.value());
            }

            if (tConnector.mMeter.l2_ampere_A.has_value()) {
              data->set_l2_ampere_a(tConnector.mMeter.l2_ampere_A.value());
            }

            if (tConnector.mMeter.l3_ampere_A.has_value()) {
              data->set_l3_ampere_a(tConnector.mMeter.l3_ampere_A.value());
            }

            if (tConnector.mMeter.l1_l2_ampere_A.has_value()) {
              data->set_l1_l2_ampere_a(tConnector.mMeter.l1_l2_ampere_A.value());
            }

            if (tConnector.mMeter.l2_l3_ampere_A.has_value()) {
              data->set_l2_l3_ampere_a(tConnector.mMeter.l2_l3_ampere_A.value());
            }

            if (tConnector.mMeter.l3_l1_ampere_A.has_value()) {
              data->set_l3_l1_ampere_a(tConnector.mMeter.l3_l1_ampere_A.value());
            }

            if (tConnector.mMeter.l1_n_ampere_A.has_value()) {
              data->set_l1_n_ampere_a(tConnector.mMeter.l1_n_ampere_A.value());
            }

            if (tConnector.mMeter.l2_n_ampere_A.has_value()) {
              data->set_l2_n_ampere_a(tConnector.mMeter.l2_n_ampere_A.value());
            }

            if (tConnector.mMeter.l3_n_ampere_A.has_value()) {
              data->set_l3_n_ampere_a(tConnector.mMeter.l3_n_ampere_A.value());
            }

            if (tConnector.mMeter.neutral_ampere_A.has_value()) {
              data->set_neutral_ampere_a(tConnector.mMeter.neutral_ampere_A.value());
            }
            this->mMQRouterPtr->send(routerProtobufMessage);
        });


  });

}
