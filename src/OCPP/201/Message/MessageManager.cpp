#include "MessageManager.hpp"
namespace OCPP201 {

void MessageManager::bootHandler(const RouterProtobufMessage &tMessage) {
  OCPP201::ComponentType componentType("OCPPCommCtrlr");
  OCPP201::VariableType variableType("HeartbeatInterval");
  try {
    this->mHeartbeatManager.mInterval = std::stoi(
        this->mConfigureManager.getVariableManager().getVariableAttributeValue(componentType, variableType,
                                                                               OCPP201::AttributeEnumType::Actual));
  } catch (std::exception &e) {
    // min heartbeat interval == 1
    this->mHeartbeatManager.mInterval = 1;
  }
  if (!this->mBootNotificationManager.isBooting) {
    this->mBootNotificationManager.setConfigure(this->mConfigureManager.getBaseInfo());
    this->mThreadPool->enqueue([this, tMessage]() {
      this->mBootNotificationManager.isBooting = true;
      this->mBootNotificationManager.bootFinish =
          true;
      // set dest
      this->mStatusNotificationManager.mDest =
          tMessage.source();
      this->mHeartbeatManager.mDest =
          tMessage.source();
      while (
          this->mBootNotificationManager
              .getBootInterval() &&
          this->mBootNotificationManager.isBooting) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        this->send(this->mBootNotificationManager.getRequestMessage(tMessage.source()),
                   [this](const std::string &tMessageConf) {
                     OCPP201::BootNotificationResponse bootNotificationResponse =
                         nlohmann::json::parse(tMessageConf);
                     this->mBootNotificationManager
                         .setBootInterval(bootNotificationResponse.getInterval());
                     switch (bootNotificationResponse.getStatus()) {
                     case OCPP201::RegistrationStatusEnumType::Accepted:
                       this->mBootNotificationManager.isBooting = false;
                       this->mBootNotificationManager.bootFinish = true;
                       // init heartbeat Timer
                       this->mHeartbeatManager.mInterval = bootNotificationResponse.getInterval();
                       this->mThreadPool->enqueue([this]() {
                         this->mHeartbeatManager.setHeartbeatHandler([&]() {
                           this->send(this->mHeartbeatManager.getRequestMessage(),
                                      [this](const std::string &tMessageConf) {
                                        // TODO heartbeat response
                                      });
                         });
                         // start heartbeat timer
                         this->mHeartbeatManager.start();
                         // send statusnotification for each connector
                         std::for_each(
                             this->mEVSEs.begin(), this->mEVSEs.end(),
                             [this](const OCPP201::EVSE &tEVSE) {
                               if (tEVSE.id!=0) {
                                 std::for_each(tEVSE.mConnectors.begin(), tEVSE.mConnectors.end(), [this](const OCPP201::Connector &tConnector){
                                   this->send(this->mStatusNotificationManager.getRequestMessage(tConnector), [](const std::string &tMessageConf){});
                                 });
                               }
                             });

                         // TODO offline meesage
                       });
                       break;
                       // 1. To inform the Charging Station that it is not yet accepted by the CSMS: Pending status.
                       // 2. To give the CSMS a way to retrieve or set certain configuration information.
                       // 3. To give the CSMS a way of limiting the load on the CSMS after e.g. a reboot of the CSMS.
                     case OCPP201::RegistrationStatusEnumType::Pending:
                       this->mBootNotificationManager
                           .isBooting = true;
                       this->mBootNotificationManager
                           .bootFinish = false;
                       break;
                     case OCPP201::RegistrationStatusEnumType::Rejected:
                       this->mBootNotificationManager
                           .isBooting = false;
                       this->mBootNotificationManager
                           .bootFinish = false;
                       break;
                     }
                   });
      }
    });
  }
}
void MessageManager::getBaseReportHandler(const std::string &tUUID,
                                          const std::string &tSource,
                                          const std::string &tMessage) {
      try {
        OCPP201::GetBaseReportRequest getBaseReportRequest = nlohmann::json::parse(tMessage);
        OCPP201::GetBaseReportResponse response;
        if (getBaseReportRequest.getReportBase() == OCPP201::ReportBaseEnumType::SummaryInventory) {
          //TODO summary reject
          response.status = OCPP201::GenericDeviceModelStatusEnumType::Rejected;
        } else {
          this->mThreadPool->enqueue([this,tSource,&getBaseReportRequest]() {
            auto configNum = this->mConfigureManager.getVariableManager().mComponentManager.componentVariable.size();
            int seqBegin = 0;
            RouterProtobufMessage routerProtobufMessage;
            routerProtobufMessage.set_source("OCPP201");
            routerProtobufMessage.set_dest(tSource);
            routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
            routerProtobufMessage.set_message_type(MessageType::REQUEST);
            routerProtobufMessage.set_ocpp_type("NotifyReport");
            while (seqBegin < configNum) {
              auto result = this->mConfigureManager.getVariableManager().getNotifyRequestInventory(getBaseReportRequest.getRequestId(), seqBegin,
                                                                                                   seqBegin + 4 >= configNum, getBaseReportRequest.getReportBase());
              routerProtobufMessage.set_data(result.serializeMessage());
              routerProtobufMessage.set_uuid(result.getMessageId());
              // ignore response
              this->send(routerProtobufMessage, [](const std::string &t){});
              seqBegin += 4;
            }
          });
          response.status = OCPP201::GenericDeviceModelStatusEnumType::Accepted;
        }
        response.setMessageId(tUUID);
        response.setPayload(Utility::toJsonString<OCPP201::GetBaseReportResponse>(response));
        RouterProtobufMessage routerProtobufMessage;
        routerProtobufMessage.set_uuid(tUUID);
        routerProtobufMessage.set_source("OCPP201");
        routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
        routerProtobufMessage.set_ocpp_type("GetBaseReport");
        routerProtobufMessage.set_dest(tSource);
        routerProtobufMessage.set_data(response.serializeMessage());
        this->send(routerProtobufMessage, [](const std::string &t){});
      } catch (std::exception &e) {
        this->sendOCPPError(tUUID, tSource, ProtocolError::InternalError,"GetBaseReportRequest parse failed");
      }

}
}
