#ifndef ECHOOCPP_MESSAGEMANAGER_HPP
#define ECHOOCPP_MESSAGEMANAGER_HPP

#include "./BootNotificationManager.hpp"
#include "./HeartBeatManager.hpp"
#include "./StatusNotificationManager.hpp"


namespace OCPP201 {
class MessageManager {
private:
  std::function<void(const RouterProtobufMessage&, std::function<void(const std::string &)>)> send;
  std::shared_ptr<ThreadPool> mThreadPool;
  OCPP201ConfigureManager mConfigureManager;
  std::vector<OCPP201::EVSE> mEVSEs;
public:
  MessageManager() = default;
  void init() {
    this->mConfigureManager.init();
  }
  void setSendMessage(std::function<void(const RouterProtobufMessage&, std::function<void(const std::string &)>)> callback) {
    this->send = callback;
  }
  void setThreadPoolRef(std::shared_ptr<ThreadPool> threadPool) {
    this->mThreadPool = threadPool;
  }

  void bootHandler(const RouterProtobufMessage &tMessage) {
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
      this->mBootNotificationManager.setConfigure(
          this->mConfigureManager.getBaseInfo());
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






  BootNotificationManager mBootNotificationManager;
  HeartBeatManager mHeartbeatManager;
  StatusNotificationManager mStatusNotificationManager;
};




}
#endif //ECHOOCPP_MESSAGEMANAGER_HPP
