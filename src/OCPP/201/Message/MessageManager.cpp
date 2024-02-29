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
          routerProtobufMessage.set_data(result.toString());
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
    routerProtobufMessage.set_data(response.toString());
    this->send(routerProtobufMessage, [](const std::string &t){});
  } catch (std::exception &e) {
    MessageErrorResponse errorResponse;
    errorResponse.setErrorCode(ProtocolError::InternalError);
    errorResponse.setMessageId(tUUID);
    errorResponse.setErrorDescription("GetBaseReportRequest parse failed");
    errorResponse.setErrorDetails(nlohmann::json::object());
    this->sendOCPPErrorMessage(errorResponse, tSource);
  }

}
void MessageManager::getVariableHandler(const std::string &tUUID,
                                        const std::string &tSource,
                                        const std::string &tMessage) {
      try {
        OCPP201::GetVariablesRequest getVariablesRequest = nlohmann::json::parse(tMessage);
        OCPP201::ComponentType componentType("DeviceDataCtrlr");
        OCPP201::VariableType variableType("ItemsPerMessage", "GetVariables");
        int numMessageGetVariable;
        std::string numMessageGetVariableStr;
        try {
          numMessageGetVariableStr = this->mConfigureManager.getVariableManager().getVariableAttributeValue(componentType, variableType, OCPP201::AttributeEnumType::Actual);
          numMessageGetVariable = std::stoi(numMessageGetVariableStr);
        } catch (std::exception &e) {
          numMessageGetVariable = 0;
        }
        if (getVariablesRequest.getVariableData.size() > numMessageGetVariable) {
          MessageErrorResponse errorResponse;
          errorResponse.setMessageId(tUUID);
          errorResponse.setErrorCode(ProtocolError::OccurrenceConstraintViolation);
          errorResponse.setErrorDetails(nlohmann::json::object());
          errorResponse.setErrorDescription("The number should be less than " + numMessageGetVariableStr + "; The number of requesting is " + std::to_string(getVariablesRequest.getVariableData.size()));
          this->sendOCPPErrorMessage(errorResponse, tSource);
          return;
        } else if (numMessageGetVariable == 0) {
          MessageErrorResponse errorResponse;
          errorResponse.setMessageId(tUUID);
          errorResponse.setErrorCode(ProtocolError::InternalError);
          errorResponse.setErrorDetails(nlohmann::json::object());
          errorResponse.setErrorDescription("ItemsPerMessageNumber should not equal to 0");
          this->sendOCPPErrorMessage(errorResponse, tSource);
          return;
        }
        auto result = this->mConfigureManager.getVariableManager().getVariableRequestHandler(getVariablesRequest);
        result.setMessageId(tUUID);
        result.setPayload(Utility::toJsonString<OCPP201::GetVariablesResponse>(result));
        RouterProtobufMessage routerProtobufMessage;
        routerProtobufMessage.set_uuid(tUUID) ;
        routerProtobufMessage.set_dest(tSource);
        routerProtobufMessage.set_message_type(MessageType::RESPONSE);
        routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
        routerProtobufMessage.set_data(result.toString());
        routerProtobufMessage.set_ocpp_type("GetVariable");
        this->send(routerProtobufMessage,[](const std::string &t){});
      } catch (std::exception &e) {
        MessageErrorResponse errorResponse;
        errorResponse.setMessageId(tUUID);
        errorResponse.setErrorCode(ProtocolError::InternalError);
        errorResponse.setErrorDetails(nlohmann::json::object());
        errorResponse.setErrorDescription("ItemsPerMessageNumber is loss or parse failed");
        this->sendOCPPErrorMessage(errorResponse, tSource);
      }
}
void MessageManager::setVariableHandler(const std::string &tUUID,
                                        const std::string &tSource,
                                        const std::string &tMessage) {
  OCPP201::SetVariablesResponse response;
  try {
    OCPP201::SetVariablesRequest request = nlohmann::json::parse(tMessage);
    for (const auto &dataReq : request.setVariableData) {
      SetVariableResultType result;
      result.setComponent(dataReq.component);
      result.setVariable(dataReq.variable);
      result.setAttributeType(dataReq.attributeType);
      auto componentConfigure = this->mConfigureManager.getVariableManager().mComponentManager;
      auto hasComponentVariable = std::find_if(componentConfigure.componentVariable.begin(), componentConfigure.componentVariable.end(),
                                               [&](ComponentVariableConfigure &config){
                                                 if (dataReq.component == config.component) {
                                                   if (dataReq.variable == config.variable) {
                                                     return true;
                                                   }else {
                                                     result.setAttributeStatus(SetVariableStatusEnumType::UnknownVariable);
                                                   }
                                                 } else {
                                                   result.setAttributeStatus(SetVariableStatusEnumType::UnknownComponent);
                                                 }
                                                 return false;
                                               });
      if (hasComponentVariable != componentConfigure.componentVariable.end()) {
        auto hasAttribute = std::find_if(hasComponentVariable->variableAttribute.begin(), hasComponentVariable->variableAttribute.end(),
                                         [&dataReq, &result] (VariableAttributeType &instance) {
                                           return dataReq.attributeType == instance.getType();
                                         });
        if (hasAttribute != hasComponentVariable->variableAttribute.end()) {
          switch (hasComponentVariable->variableCharacteristics.getDataType()) {
          case DataEnumType::StringType:
            hasAttribute->setValue(dataReq.attributeValue);
            result.setAttributeStatus(SetVariableStatusEnumType::Accepted);
            break;
          case DataEnumType::DateTimeType:
            if (RFC3339DateTime::fromString(dataReq.attributeValue) == std::nullopt) {
              result.setAttributeStatus(SetVariableStatusEnumType::Rejected);
              StatusInfoType statusInfoType;
              statusInfoType.reasonCode = "String format to RFC3339 time failed";
              result.setAttributeStatusInfo(statusInfoType);
            } else {
              hasAttribute->setValue(dataReq.attributeValue);
              result.setAttributeStatus(SetVariableStatusEnumType::Accepted);
            }
          case DataEnumType::BooleanType:
            if (std::tolower(dataReq.attributeValue == "true") || std::tolower(dataReq.attributeValue == "false"))
            {
              hasAttribute->setValue(dataReq.attributeValue);
              result.setAttributeStatus(SetVariableStatusEnumType::Accepted);
            } else {
              StatusInfoType statusInfoType;
              statusInfoType.reasonCode = "String format to boolean failed";
              result.setAttributeStatusInfo(statusInfoType);
              result.setAttributeStatus(SetVariableStatusEnumType::Rejected);
            }
            break;
          case DataEnumType::IntegerType:
            try {
              auto tmp = std::stoi(dataReq.attributeValue);
              hasAttribute->setValue(dataReq.attributeValue);

              if ((hasComponentVariable->variableCharacteristics.getMaxLimit().has_value() &&  tmp > hasComponentVariable->variableCharacteristics.getMaxLimit())
                  || (hasComponentVariable->variableCharacteristics.getMinLimit().has_value() && tmp < hasComponentVariable->variableCharacteristics.getMinLimit())) {
                StatusInfoType statusInfoType;
                statusInfoType.reasonCode = "The value " + dataReq.attributeValue + " out of bounds";
                result.setAttributeStatusInfo(statusInfoType);
                result.setAttributeStatus(SetVariableStatusEnumType::Rejected);
              } else {
                result.setAttributeStatus(SetVariableStatusEnumType::Accepted);
              }
            }catch (std::exception &e) {
              StatusInfoType statusInfoType;
              statusInfoType.reasonCode = "String format to integer failed";
              result.setAttributeStatusInfo(statusInfoType);
              result.setAttributeStatus(SetVariableStatusEnumType::Rejected);
            }
            break;
          case DataEnumType::DecimalType:
            try {
              auto tmp = std::stof(dataReq.attributeValue);
              hasAttribute->setValue(dataReq.attributeValue);
              if ((hasComponentVariable->variableCharacteristics.getMaxLimit().has_value() &&  tmp > hasComponentVariable->variableCharacteristics.getMaxLimit())
                  || (hasComponentVariable->variableCharacteristics.getMinLimit().has_value() && tmp < hasComponentVariable->variableCharacteristics.getMinLimit())) {
                StatusInfoType statusInfoType;
                statusInfoType.reasonCode = "The value " + dataReq.attributeValue + " out of bounds";
                result.setAttributeStatusInfo(statusInfoType);
                result.setAttributeStatus(SetVariableStatusEnumType::Rejected);
              } else {
                result.setAttributeStatus(SetVariableStatusEnumType::Accepted);
              }
            } catch (std::exception &e) {
              StatusInfoType statusInfoType;
              statusInfoType.reasonCode = "String format to decimal failed";
              result.setAttributeStatusInfo(statusInfoType);
              result.setAttributeStatus(SetVariableStatusEnumType::Rejected);
            }
            break;
          case DataEnumType::MemberListType:
          case DataEnumType::OptionListType:
          case DataEnumType::SequenceListType:
            hasComponentVariable->variableCharacteristics.setValuesList(dataReq.attributeValue);
            result.setAttributeStatus(SetVariableStatusEnumType::Accepted);
            break;
          default:
            StatusInfoType statusInfoType;
            statusInfoType.reasonCode = "Internal error";
            result.setAttributeStatusInfo(statusInfoType);
            result.setAttributeStatus(SetVariableStatusEnumType::Rejected);
            break;
          }
        } else {
          result.setAttributeStatus(SetVariableStatusEnumType::NotSupportedAttributeType);
        }
      }
      response.setVariableResult.emplace_back(result);
    }
  } catch (std::exception &e) {
    MessageErrorResponse errorResponse;
    errorResponse.setMessageId(tUUID);
    errorResponse.setErrorCode(ProtocolError::InternalError);
    errorResponse.setErrorDetails(nlohmann::json::object());
    errorResponse.setErrorDescription(std::string("Internal error ").append(e.what()));
    this->sendOCPPErrorMessage(errorResponse, tSource);
  }
  RouterProtobufMessage routerProtobufMessage;
  routerProtobufMessage.set_uuid(tUUID);
  routerProtobufMessage.set_source("OCPP");
  routerProtobufMessage.set_data(response.toString());
  routerProtobufMessage.set_method(::RouterMethods::ROUTER_METHODS_OCPP201);
  routerProtobufMessage.set_dest("websocket");
  this->send(routerProtobufMessage, [](const std::string &t){});
}

}
