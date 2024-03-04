#include "MessageManager.hpp"
namespace OCPP201 {

void MessageManager::bootHandler(const InternalRouterMessage &tMessage) {
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
      this->mBootNotificationManager.bootFinish = true;
      // set dest
      while ( this->mBootNotificationManager .getBootInterval()
             && this->mBootNotificationManager.isBooting) {
        RouterPackage bootMessage;
        bootMessage.message = this->mBootNotificationManager.getRequestMessage(tMessage.source());
        bootMessage.tGetReturnSuccessCallback =
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
                    RouterPackage routerPackage;
                    routerPackage.message = std::move(this->mHeartbeatManager.getRequestMessage());
                    routerPackage.tGetReturnSuccessCallback = [](const std::string &tMessageConf) {
                      // TODO heartbeat response
                    };
                    this->send(std::move(routerPackage));
                  });
                  // start heartbeat timer
                  this->mHeartbeatManager.start();
                  // send statusnotification for each connector
                  std::for_each(
                      this->mEVSEs.begin(), this->mEVSEs.end(),
                      [this](const EVSE &tEVSE) {
                        std::for_each(tEVSE.mConnectors.begin(), tEVSE.mConnectors.end(), [this, &tEVSE](const Connector &tConnector){
                          RouterPackage routerPackage;
                          routerPackage.message = this->mStatusNotificationManager.getRequestMessage(tConnector, tEVSE.id);
                          routerPackage.tGetReturnSuccessCallback = [](const std::string &tMessageConf) {
                          };
                          this->send(std::move(routerPackage));
                        });
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
            };
        this->send(std::move(bootMessage));
        std::this_thread::sleep_for(std::chrono::seconds(this->mBootNotificationManager .getBootInterval()));
      }
    });
  }
}
void MessageManager::getBaseReportHandler(std::string_view tUUID,
                                          const ZMQIdentify tSource,
                                          std::string_view tMessage) {
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
        InternalRouterMessage routerProtobufMessage;
        routerProtobufMessage.mutable_ocpp_data()->set_ocpp_type(magic_enum::enum_name(OCPP201Type::NotifyReport).begin());
        routerProtobufMessage.set_source(ZMQIdentify::ocpp);
        routerProtobufMessage.set_dest(tSource);
        routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
        routerProtobufMessage.set_message_type(MessageType::REQUEST);
        while (seqBegin < configNum) {
          auto result = this->mConfigureManager.getVariableManager().getNotifyRequestInventory(getBaseReportRequest.getRequestId(), seqBegin,
                                                                                               seqBegin + 4 >= configNum, getBaseReportRequest.getReportBase());
          routerProtobufMessage.mutable_ocpp_data()->set_data(result.toString());
          routerProtobufMessage.set_uuid(result.getMessageId());
          // ignore response
          RouterPackage routerPackage;
          routerPackage.message = routerProtobufMessage;
          this->send(std::move(routerPackage));
          seqBegin += 4;
        }
      });
      response.status = OCPP201::GenericDeviceModelStatusEnumType::Accepted;
    }
    response.setMessageId(tUUID.begin());
    response.setPayload(Utility::toJsonString<OCPP201::GetBaseReportResponse>(response));
    InternalRouterMessage routerProtobufMessage;
    routerProtobufMessage.set_uuid(tUUID.begin());
    routerProtobufMessage.set_source(ZMQIdentify::ocpp);
    routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
    routerProtobufMessage.set_dest(ZMQIdentify::websocket);
    routerProtobufMessage.mutable_ocpp_data()->set_ocpp_type(magic_enum::enum_name(OCPP201Type::GetBaseReport).begin());
    routerProtobufMessage.mutable_ocpp_data()->set_data(response.toString());
    RouterPackage routerPackage;
    routerPackage.message = std::move(routerProtobufMessage);
    this->send(std::move(routerPackage));
  } catch (std::exception &e) {
    MessageErrorResponse errorResponse;
    errorResponse.setErrorCode(ProtocolError::InternalError);
    errorResponse.setMessageId(tUUID.begin());
    errorResponse.setErrorDescription("GetBaseReportRequest parse failed");
    errorResponse.setErrorDetails(nlohmann::json::object());
    this->sendOCPPErrorMessage(errorResponse, tSource);
  }

}
void MessageManager::getVariableHandler(std::string_view tUUID,
                                        const ZMQIdentify tSource,
                                        std::string_view tMessage) {
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
      errorResponse.setMessageId(tUUID.begin());
      errorResponse.setErrorCode(ProtocolError::OccurrenceConstraintViolation);
      errorResponse.setErrorDetails(nlohmann::json::object());
      errorResponse.setErrorDescription("The number should be less than " + numMessageGetVariableStr + "; The number of requesting is " + std::to_string(getVariablesRequest.getVariableData.size()));
      this->sendOCPPErrorMessage(errorResponse, tSource);
      return;
    } else if (numMessageGetVariable == 0) {
      MessageErrorResponse errorResponse;
      errorResponse.setMessageId(tUUID.begin());
      errorResponse.setErrorCode(ProtocolError::InternalError);
      errorResponse.setErrorDetails(nlohmann::json::object());
      errorResponse.setErrorDescription("ItemsPerMessageNumber should not equal to 0");
      this->sendOCPPErrorMessage(errorResponse, tSource);
      return;
    }
    auto result = this->mConfigureManager.getVariableManager().getVariableRequestHandler(getVariablesRequest);
    result.setMessageId(tUUID.begin());
    result.setPayload(Utility::toJsonString<OCPP201::GetVariablesResponse>(result));
    InternalRouterMessage routerProtobufMessage;
    routerProtobufMessage.set_uuid(tUUID.begin()) ;
    routerProtobufMessage.set_dest(tSource);
    routerProtobufMessage.set_message_type(MessageType::RESPONSE);
    routerProtobufMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
    routerProtobufMessage.mutable_ocpp_data()->set_data(result.toString());
    routerProtobufMessage.mutable_ocpp_data()->set_ocpp_type("GetVariable");
    RouterPackage routerPackage;
    routerPackage.message = std::move(routerProtobufMessage);
    this->send(std::move(routerPackage));
  } catch (std::exception &e) {
    MessageErrorResponse errorResponse;
    errorResponse.setMessageId(tUUID.begin());
    errorResponse.setErrorCode(ProtocolError::InternalError);
    errorResponse.setErrorDetails(nlohmann::json::object());
    errorResponse.setErrorDescription("ItemsPerMessageNumber is loss or parse failed");
    this->sendOCPPErrorMessage(errorResponse, tSource);
  }
}
void MessageManager::setVariableHandler(std::string_view tUUID,
                                        const ZMQIdentify tSource,
                                        std::string_view tMessage) {
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
    errorResponse.setMessageId(tUUID.begin());
    errorResponse.setErrorCode(ProtocolError::InternalError);
    errorResponse.setErrorDetails(nlohmann::json::object());
    errorResponse.setErrorDescription(std::string("Internal error ").append(e.what()));
    this->sendOCPPErrorMessage(errorResponse, tSource);
  }
  InternalRouterMessage routerProtobufMessage;
  routerProtobufMessage.set_uuid(tUUID.begin());
  routerProtobufMessage.set_source(ZMQIdentify::ocpp);
  routerProtobufMessage.mutable_ocpp_data()->set_data(response.toString());
  routerProtobufMessage.set_method(::RouterMethods::ROUTER_METHODS_OCPP201);
  routerProtobufMessage.set_dest(ZMQIdentify::websocket);
  RouterPackage routerPackage;
  routerPackage.message = routerProtobufMessage;
  this->send(std::move(routerPackage));
}
void MessageManager::setNetworkProfileReqHandler(std::string_view tUUID,
                                                 const ZMQIdentify tDest,
                                                 std::string_view tMessage) {
  OCPP201::SetNetworkProfileRequest request = nlohmann::json::parse(tMessage);
  OCPP201::SetNetworkProfileResponse response;


}
void MessageManager::resetReqHandler(std::string_view tUUID,
                                     const ZMQIdentify tDest,
                                     std::string_view tMessage) {
  ResetRequest request = nlohmann::json::parse(tMessage);

  // TODO Firmware updating should be reject
  // TODO AllowReset an EVSE can be reset individually.


  bool isAnyCharging = std::ranges::any_of(mEVSEs, [](const EVSE& evse) {
    return std::ranges::any_of(evse.mConnectors, [](const Connector& connector) {
      return connector.isCharging;
    });
  });

  ResetScheduleEvent resetScheduleEvent;
  if (isAnyCharging) {
    if (request.resetType == ResetEnumType::OnIdle) {
      if (request.evseId.has_value()) {
        resetScheduleEvent.resetChargingStation = true;
        resetScheduleEvent.evseId = request.evseId.value();
      } else {
        resetScheduleEvent.resetChargingStation = false;
      }

    }

  } else {

  }





  if (request.resetType == ResetEnumType::Immediate) {
      InternalRouterMessage resetMessage;
      resetMessage.set_method(RouterMethods::ROUTER_METHODS_NOTIFICATION_OCPP_2_EVSE);
      resetMessage.set_dest(ZMQIdentify::interface);
      auto uuid = Utility::generateMessageId();
      while (this->isUUIDExist(uuid)) {
        uuid = Utility::generateMessageId();
      }
      resetMessage.set_uuid(uuid);
      resetMessage.set_source(ZMQIdentify::ocpp);
      resetMessage.set_message_type(MessageType::REQUEST);
      if (request.evseId.has_value()) {
        resetMessage.mutable_evse_status_notification()->set_notification_method(RouterNotificationMethod::RESET_DEVICE);
        resetMessage.mutable_evse_status_notification()->set_id(request.evseId.value());
      } else {
        resetMessage.mutable_charger_station_notification()->set_notification_method(RouterNotificationMethod::RESET_DEVICE);
      }
      RouterPackage routerPackage;
      routerPackage.message = resetMessage;
      std::string uuidOCPP{tUUID};
      routerPackage.tGetReturnSuccessCallback = [this, uuidOCPP, tDest](const std::string & tMessage) {
        ResetResponse response;
        this->sendOCPPMessage(uuidOCPP,tDest, response.toString(), MessageType::RESPONSE, OCPP201Type::Reset);
      };
      routerPackage.tGetResponseFailedCallback = [this, uuidOCPP, tDest] () {
        ResetResponse response;
        response.status = ResetStatusEnumType::Rejected;
        StatusInfoType statusInfoType;
        statusInfoType.reasonCode = "No response from charge station";
        this->sendOCPPMessage(uuidOCPP, tDest, response.toString(), MessageType::RESPONSE,
                              OCPP201Type::Reset);
      };
  } else if (request.resetType == ResetEnumType::OnIdle) {
    ResetResponse response;
    ResetScheduleEvent resetScheduleEvent;
    if (request.evseId.has_value()) {

    } else {
      //
      resetScheduleEvent.resetChargingStation = true;
      this->mResetScheduleEvents.emplace_back(resetScheduleEvent);
      response.status = ResetStatusEnumType::Scheduled;
    }
//     TODO schedule
//    StatusInfoType statusInfoType;
//    statusInfoType.reasonCode = "No support";
    this->sendOCPPMessage(tUUID.begin(), tDest, response.toString(), MessageType::RESPONSE,
                          OCPP201Type::Reset);
  }
}











void MessageManager::sendOCPPMessage(
    const std::string &tUUID, ZMQIdentify tDest, std::string_view tMessage,
    MessageType messageType, OCPP201Type ocpp201Type,
    std::function<void(const std::string &)> tSuccessCallback,
    std::function<void()> tFailedCallback) {

  InternalRouterMessage responseRouterMessage;
  responseRouterMessage.set_uuid(tUUID);
  responseRouterMessage.set_dest(tDest);
  responseRouterMessage.set_method(RouterMethods::ROUTER_METHODS_OCPP201);
  responseRouterMessage.set_source(ZMQIdentify::ocpp);
  responseRouterMessage.set_message_type(messageType);
  responseRouterMessage.mutable_ocpp_data()->set_data(tMessage.begin());
  responseRouterMessage.mutable_ocpp_data()->set_ocpp_type(magic_enum::enum_name(ocpp201Type).begin());
  RouterPackage package;
  package.message = responseRouterMessage;
  if (tSuccessCallback != nullptr) {
    package.tGetReturnSuccessCallback = tSuccessCallback;
  }
  if (tFailedCallback != nullptr) {
    package.tGetResponseFailedCallback = tFailedCallback;
  }
  this->send(std::move(package));
}

}
