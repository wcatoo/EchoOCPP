#ifndef ECHOOCPP_CONFIGUREKEYGENERAL_HPP
#define ECHOOCPP_CONFIGUREKEYGENERAL_HPP
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../DataType/PrimitiveDatatypes.hpp"


namespace OCPP201 {

class VariableValue {
public:
  VariableValue() = default;
  std::string attributeValue;
  AttributeEnumType type;
  friend void to_json(nlohmann::json &j, const VariableValue &config){
    j = nlohmann::json {
      {"type", magic_enum::enum_name(config.type)},
      {"attributeValue", config.attributeValue}
    };
  }
  friend void from_json(const nlohmann::json &j, VariableValue &config){
    config.attributeValue = j.at("attributeValue").get<std::string>();
    try {
      config.type = magic_enum::enum_cast<AttributeEnumType>(j.at("type")).value();
    } catch (std::exception &e) {
      config.type = AttributeEnumType::Actual;
    }
  }


};

class Variable {
public:
  Variable() = default;
  std::optional<std::string> variableInstance;
  std::vector<VariableValue> value;
  friend void to_json(nlohmann::json &j, const Variable &config){
    j = nlohmann::json {
      {"value", config.value}
    };
    if (config.variableInstance.has_value()) {
      j.emplace("variableInstance", config.variableInstance.value());
    }
  }
  friend void from_json(const nlohmann::json &j, Variable &config){
    j.at("value").get_to(config.value);
    if (j.contains("variableInstance")) {
      config.variableInstance = std::optional<std::string>(j.at("variableInstance"));
    }
  }
};

class ComponentInstance {
public:
  ComponentInstance() = default;
  std::string variableName;
  std::optional<std::string> componentInstance;
  std::optional<EVSEType> evse;
  std::vector<Variable> variable;
  friend void to_json(nlohmann::json &j, const ComponentInstance &config){
    j = nlohmann::json {
        {"variableName", config.variableName},
      {"variable", config.variable}
    };
    if (config.componentInstance.has_value()) {
      j.emplace("componentInstance", config.componentInstance.value());
    }
    if (config.evse.has_value()) {
      j.emplace("evse", config.evse.value());
    }
    j.emplace("variable", config.variable);
  }
  friend void from_json(const nlohmann::json &j, ComponentInstance &config){
    j.at("variableName").get_to(config.variableName);
    if (j.contains("componentInstance") && !j.at("componentInstance").is_null()) {
      config.componentInstance = std::optional<std::string>(j.at("componentInstance"));
    }
    if (j.contains("evse")) {
      config.evse = std::optional<EVSEType>(j.at("evse"));
    }
    j.at("variable").get_to(config.variable);
  }
};


class Component {
public:
  Component() = default;
  std::string componentName;
  std::vector<ComponentInstance> component;
  friend void to_json(nlohmann::json &j, const Component &config){
    j = nlohmann::json {
      {"componentName", config.componentName},
      {"component", config.component}
    };
  }
  friend void from_json(const nlohmann::json &j, Component &config){
    j.at("componentName").get_to(config.componentName);
    j.at("component").get_to(config.component);
  }
};


class ComponentManager {
public:
  ComponentManager() = default;
  std::vector<Component> components;
  friend void to_json(nlohmann::json &j, const ComponentManager &config){
    j = nlohmann::json {
        {"Components", config.components}
    };
  }
  friend void from_json(const nlohmann::json &j, ComponentManager &config){
    try {
      j.at("components").get_to(config.components);
    }catch (std::exception &e) {
      std::cout << "component manager from json " << e.what() << std::endl;
      config.components = std::vector<Component>{};
    }
  }

};


}


//
//
//class ConfigureVariables {
//private:
//public:
//  // General
//  int ActiveNetworkProfile{0};
//  bool AllowNewSessionsPendingFirmwareUpdate{};
//  int DefaultMessageTimeout{};
//  std::string FileTransferProtocols;
//  int HeartbeatInterval{};
//  std::string NetworkConfigurationPriority;
//  int NetworkProfileConnectionAttempts{};
//  int OfflineThreshold{};
//  bool QueueAllMessages{};
//  int MessageAttemptsTransactionEvent{};
//  int MessageAttemptIntervalTransactionEvent{};
//  bool UnlockOnEVSideDisconnect{};
//  int WebSocketPingInterval{};
//  int ResetRetries{};
//  int MessageFieldLength{};
//  int ItemsPerMessageGetReport{};
//  int ItemsPerMessageGetVariables{};
//  int BytesPerMessageGetReport{};
//  int BytesPerMessageGetVariables{};
//  int ConfigurationValueSize{};
//  int ReportingValueSize{};
//  int ItemsPerMessageSetVariables{};
//  int BytesPerMessageSetVariables{};
//  RFC3339DateTime DateTime;
//  std::string NtpSource;
//  std::string NtpServerUri;
//  std::string TimeOffset;
//  std::string NextTimeOffsetTransitionDateTime;
//  std::string TimeOffsetNextTransition;
//  std::string TimeSource;
//  std::string TimeZone;
//  int TimeAdjustmentReportingThreshold{};
//  bool CustomImplementationEnabled{};
//  // Authorization
//  bool AuthEnabled{false};
//  int AdditionalInfoItemsPerMessage{0};
//  bool OfflineTxForUnknownIdEnabled{false};
//  bool AuthorizeRemoteStart{false};
//  bool LocalAuthorizeOffline{false};
//  bool LocalPreAuthorize{false};
//  std::string MasterPassGroupId;
//  bool DisableRemoteAuthorization{false};
//  // AuthorizationCache
//  bool AuthCacheEnabled{false};
//  bool AuthCacheAvailable{false};
//  int AuthCacheLifeTime{0};
//  int AuthCacheStorage{0};
//  std::string AuthCachePolicy;
//  bool AuthCacheDisablePostAuthorize{false};
//  // Local Authorization
//  bool LocalAuthListEnabled{false};
//  int LocalAuthListEntries{0};
//  bool LocalAuthListAvailable{false};
//  int ItemsPerMessageSendLocalList{0};
//  int BytesPerMessageSendLocalList{0};
//  int LocalAuthListStorage{0};
//  bool LocalAuthListDisablePostAuthorize{false};
////Security
//  std::string BasicAuthPassword;
//  std::string Identity;
//  std::string OrganizationName;
//  std::string CertificateEntries;
//  std::string SecurityProfile;
//  std::string AdditionalRootCertificateCheck;
//  int MaxCertificateChainSize{0};
//  int CertSigningWaitMinimum{0};
//  int CertSigningRepeatTimes{0};
//  // Transaction
//  std::string EVConnectionTimeOut;
//  bool StopTxOnEVSideDisconnect{false};
//  bool TxBeforeAcceptedEnabled{false};
//  std::string TxStartPoint;
//  std::string TxStopPoint;
//
//
//
//
//
//
//
//
//
//  ConfigureVariables() = default;
//
//
//
//  friend void to_json(nlohmann::json &j, const ConfigureVariables &config){
//    j = nlohmann::json{
//        {"ActiveNetworkProfile", config.ActiveNetworkProfile},
//        {"AllowNewSessionsPendingFirmwareUpdate", config.AllowNewSessionsPendingFirmwareUpdate},
//        {"DefaultMessageTimeout", config.DefaultMessageTimeout},
//        {"FileTransferProtocols", config.FileTransferProtocols},
//        {"HeartbeatInterval", config.HeartbeatInterval},
//        {"NetworkConfigurationPriority", config.NetworkConfigurationPriority},
//        {"NetworkProfileConnectionAttempts", config.NetworkProfileConnectionAttempts},
//        {"OfflineThreshold", config.OfflineThreshold},
//        {"QueueAllMessages", config.QueueAllMessages},
//        {"MessageAttemptsTransactionEvent", config.MessageAttemptsTransactionEvent},
//        {"MessageAttemptIntervalTransactionEvent", config.MessageAttemptIntervalTransactionEvent},
//        {"UnlockOnEVSideDisconnect", config.UnlockOnEVSideDisconnect},
//        {"WebSocketPingInterval", config.WebSocketPingInterval},
//        {"ResetRetries", config.ResetRetries},
//        {"MessageFieldLength", config.MessageFieldLength},
//        {"ItemsPerMessageGetReport", config.ItemsPerMessageGetReport},
//        {"ItemsPerMessageGetVariables", config.ItemsPerMessageGetVariables},
//        {"BytesPerMessageGetReport", config.BytesPerMessageGetReport},
//        {"BytesPerMessageGetVariables", config.BytesPerMessageGetVariables},
//        {"ConfigurationValueSize", config.ConfigurationValueSize},
//        {"ReportingValueSize", config.ReportingValueSize},
//        {"ItemsPerMessageSetVariables", config.ItemsPerMessageSetVariables},
//        {"BytesPerMessageSetVariables", config.BytesPerMessageSetVariables},
//        {"DateTime", config.DateTime},
//        {"NtpSource", config.NtpSource},
//        {"NtpServerUri", config.NtpServerUri},
//        {"TimeOffset", config.TimeOffset},
//        {"NextTimeOffsetTransitionDateTime", config.NextTimeOffsetTransitionDateTime},
//        {"TimeOffsetNextTransition", config.TimeOffsetNextTransition},
//        {"TimeSource", config.TimeSource},
//        {"TimeZone", config.TimeZone},
//        {"TimeAdjustmentReportingThreshold", config.TimeAdjustmentReportingThreshold},
//        {"CustomImplementationEnabled", config.CustomImplementationEnabled},
//        {"AuthEnabled", config.AuthEnabled},
//        {"AdditionalInfoItemsPerMessage", config.AdditionalInfoItemsPerMessage},
//        {"OfflineTxForUnknownIdEnabled", config.OfflineTxForUnknownIdEnabled},
//        {"AuthorizeRemoteStart", config.AuthorizeRemoteStart},
//        {"LocalAuthorizeOffline", config.LocalAuthorizeOffline},
//        {"LocalPreAuthorize", config.LocalPreAuthorize},
//        {"MasterPassGroupId", config.MasterPassGroupId},
//        {"DisableRemoteAuthorization", config.DisableRemoteAuthorization},
//        {"AuthCacheEnabled", config.AuthCacheEnabled},
//        {"AuthCacheAvailable", config.AuthCacheAvailable},
//        {"AuthCacheLifeTime", config.AuthCacheLifeTime},
//        {"AuthCacheStorage", config.AuthCacheStorage},
//        {"AuthCachePolicy", config.AuthCachePolicy},
//        {"AuthCacheDisablePostAuthorize", config.AuthCacheDisablePostAuthorize},
//        {"LocalAuthListEnabled", config.LocalAuthListEnabled},
//        {"LocalAuthListEntries", config.LocalAuthListEntries},
//        {"LocalAuthListAvailable", config.LocalAuthListAvailable},
//        {"ItemsPerMessageSendLocalList", config.ItemsPerMessageSendLocalList},
//        {"BytesPerMessageSendLocalList", config.BytesPerMessageSendLocalList},
//        {"LocalAuthListStorage", config.LocalAuthListStorage},
//        {"LocalAuthListDisablePostAuthorize", config.LocalAuthListDisablePostAuthorize},
//        {"BasicAuthPassword", config.BasicAuthPassword},
//        {"Identity", config.Identity},
//        {"OrganizationName", config.OrganizationName},
//        {"CertificateEntries", config.CertificateEntries},
//        {"SecurityProfile", config.SecurityProfile},
//        {"AdditionalRootCertificateCheck", config.AdditionalRootCertificateCheck},
//        {"MaxCertificateChainSize", config.MaxCertificateChainSize},
//        {"CertSigningWaitMinimum", config.CertSigningWaitMinimum},
//        {"CertSigningRepeatTimes", config.CertSigningRepeatTimes},
//        {"EVConnectionTimeOut", config.EVConnectionTimeOut},
//        {"StopTxOnEVSideDisconnect", config.StopTxOnEVSideDisconnect},
//        {"TxBeforeAcceptedEnabled", config.TxBeforeAcceptedEnabled},
//        {"TxStartPoint", config.TxStartPoint},
//        {"TxStopPoint", config.TxStopPoint}
//    };
//  }
//  friend void from_json(const nlohmann::json &j, ConfigureVariables &config) {
//    config.ActiveNetworkProfile = j.value("ActiveNetworkProfile", 0);
//    config.AllowNewSessionsPendingFirmwareUpdate = j.value("AllowNewSessionsPendingFirmwareUpdate", false);
//    config.DefaultMessageTimeout = j.value("DefaultMessageTimeout", 0);
//    config.FileTransferProtocols = j.value("FileTransferProtocols", "");
//    config.HeartbeatInterval = j.value("HeartbeatInterval", 0);
//    config.NetworkConfigurationPriority = j.value("NetworkConfigurationPriority", "");
//    config.NetworkProfileConnectionAttempts = j.value("NetworkProfileConnectionAttempts", 0);
//    config.OfflineThreshold = j.value("OfflineThreshold", 0);
//    config.QueueAllMessages = j.value("QueueAllMessages", false);
//    config.MessageAttemptsTransactionEvent = j.value("MessageAttemptsTransactionEvent", 0);
//    config.MessageAttemptIntervalTransactionEvent = j.value("MessageAttemptIntervalTransactionEvent", 0);
//    config.UnlockOnEVSideDisconnect = j.value("UnlockOnEVSideDisconnect", false);
//    config.WebSocketPingInterval = j.value("WebSocketPingInterval", 0);
//    config.ResetRetries = j.value("ResetRetries", 0);
//    config.MessageFieldLength = j.value("MessageFieldLength", 0);
//    config.ItemsPerMessageGetReport = j.value("ItemsPerMessageGetReport", 0);
//    config.ItemsPerMessageGetVariables = j.value("ItemsPerMessageGetVariables", 0);
//    config.BytesPerMessageGetReport = j.value("BytesPerMessageGetReport", 0);
//    config.BytesPerMessageGetVariables = j.value("BytesPerMessageGetVariables", 0);
//    config.ConfigurationValueSize = j.value("ConfigurationValueSize", 0);
//    config.ReportingValueSize = j.value("ReportingValueSize", 0);
//    config.ItemsPerMessageSetVariables = j.value("ItemsPerMessageSetVariables", 0);
//    config.BytesPerMessageSetVariables = j.value("BytesPerMessageSetVariables", 0);
//    config.DateTime = j.value("DateTime", RFC3339DateTime());
//    config.NtpSource = j.value("NtpSource", "");
//    config.NtpServerUri = j.value("NtpServerUri", "");
//    config.TimeOffset = j.value("TimeOffset", "");
//    config.NextTimeOffsetTransitionDateTime = j.value("NextTimeOffsetTransitionDateTime", "");
//    config.TimeOffsetNextTransition = j.value("TimeOffsetNextTransition", "");
//    config.TimeSource = j.value("TimeSource", "");
//    config.TimeZone = j.value("TimeZone", "");
//    config.TimeAdjustmentReportingThreshold = j.value("TimeAdjustmentReportingThreshold", 0);
//    config.CustomImplementationEnabled = j.value("CustomImplementationEnabled", false);
//    config.AuthEnabled = j.value("AuthEnabled", false);
//    config.AdditionalInfoItemsPerMessage = j.value("AdditionalInfoItemsPerMessage", 0);
//    config.OfflineTxForUnknownIdEnabled = j.value("OfflineTxForUnknownIdEnabled", false);
//    config.AuthorizeRemoteStart = j.value("AuthorizeRemoteStart", false);
//    config.LocalAuthorizeOffline = j.value("LocalAuthorizeOffline", false);
//    config.LocalPreAuthorize = j.value("LocalPreAuthorize", false);
//    config.MasterPassGroupId = j.value("MasterPassGroupId", "");
//    config.DisableRemoteAuthorization = j.value("DisableRemoteAuthorization", false);
//    config.AuthCacheEnabled = j.value("AuthCacheEnabled", false);
//    config.AuthCacheAvailable = j.value("AuthCacheAvailable", false);
//    config.AuthCacheLifeTime = j.value("AuthCacheLifeTime", 0);
//    config.AuthCacheStorage = j.value("AuthCacheStorage", 0);
//    config.AuthCachePolicy = j.value("AuthCachePolicy", "");
//    config.AuthCacheDisablePostAuthorize = j.value("AuthCacheDisablePostAuthorize", false);
//    config.LocalAuthListEnabled = j.value("LocalAuthListEnabled", false);
//    config.LocalAuthListEntries = j.value("LocalAuthListEntries", 0);
//    config.LocalAuthListAvailable = j.value("LocalAuthListAvailable", false);
//    config.ItemsPerMessageSendLocalList = j.value("ItemsPerMessageSendLocalList", 0);
//    config.BytesPerMessageSendLocalList = j.value("BytesPerMessageSendLocalList", 0);
//    config.LocalAuthListStorage = j.value("LocalAuthListStorage", 0);
//    config.LocalAuthListDisablePostAuthorize = j.value("LocalAuthListDisablePostAuthorize", false);
//    config.BasicAuthPassword = j.value("BasicAuthPassword", "");
//    config.Identity = j.value("Identity", "");
//    config.OrganizationName = j.value("OrganizationName", "");
//    config.CertificateEntries = j.value("CertificateEntries", "");
//    config.SecurityProfile = j.value("SecurityProfile", "");
//    config.AdditionalRootCertificateCheck = j.value("AdditionalRootCertificateCheck", "");
//    config.MaxCertificateChainSize = j.value("MaxCertificateChainSize", 0);
//    config.CertSigningWaitMinimum = j.value("CertSigningWaitMinimum", 0);
//    config.CertSigningRepeatTimes = j.value("CertSigningRepeatTimes", 0);
//    config.EVConnectionTimeOut = j.value("EVConnectionTimeOut", "");
//    config.StopTxOnEVSideDisconnect = j.value("StopTxOnEVSideDisconnect", false);
//    config.TxBeforeAcceptedEnabled = j.value("TxBeforeAcceptedEnabled", false);
//    config.TxStartPoint = j.value("TxStartPoint", "");
//    config.TxStopPoint = j.value("TxStopPoint", "");
//  }
//};



#endif // ECHOOCPP_CONFIGUREKEYGENERAL_HPP
