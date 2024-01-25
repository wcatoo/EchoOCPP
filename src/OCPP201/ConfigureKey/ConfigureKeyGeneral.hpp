//
// Created by 杨帆 on 2024/1/13.
//

#ifndef ECHOOCPP_CONFIGUREKEYGENERAL_HPP
#define ECHOOCPP_CONFIGUREKEYGENERAL_HPP
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../DataType/PrimitiveDatatypes.hpp"


class ConfigureKeyGeneral {
private:
public:
  int ActiveNetworkProfile{};
  bool AllowNewSessionsPendingFirmwareUpdate{};
  int DefaultMessageTimeout{};
  std::string FileTransferProtocols;
  int HeartbeatInterval{};
  std::string NetworkConfigurationPriority;
  int NetworkProfileConnectionAttempts{};
  int OfflineThreshold{};
  bool QueueAllMessages{};
  int MessageAttemptsTransactionEvent{};
  int MessageAttemptIntervalTransactionEvent{};
  bool UnlockOnEVSideDisconnect{};
  int WebSocketPingInterval{};
  int ResetRetries{};
  int MessageFieldLength{};
  int ItemsPerMessageGetReport{};
  int ItemsPerMessageGetVariables{};
  int BytesPerMessageGetReport{};
  int BytesPerMessageGetVariables{};
  int ConfigurationValueSize{};
  int ReportingValueSize{};
  int ItemsPerMessageSetVariables{};
  int BytesPerMessageSetVariables{};
  RFC3339DateTime DateTime;
  std::string NtpSource;
  std::string NtpServerUri;
  std::string TimeOffset;
  std::string NextTimeOffsetTransitionDateTime;
  std::string TimeOffsetNextTransition;
  std::string TimeSource;
  std::string TimeZone;
  int TimeAdjustmentReportingThreshold{};
  bool CustomImplementationEnabled{};

  ConfigureKeyGeneral() = default;
//  int getActiveNetworkProfile() const { return ActiveNetworkProfile; }
//  bool getAllowNewSessionsPendingFirmwareUpdate() const { return AllowNewSessionsPendingFirmwareUpdate; }
//  int getDefaultMessageTimeout() const { return DefaultMessageTimeout; }
//  std::string getFileTransferProtocols() const { return FileTransferProtocols; }
//  int getHeartbeatInterval() const { return HeartbeatInterval; }
//  std::string getNetworkConfigurationPriority() const { return NetworkConfigurationPriority; }
//  int getNetworkProfileConnectionAttempts() const { return NetworkProfileConnectionAttempts; }
//  int getOfflineThreshold() const { return OfflineThreshold; }
//  bool getQueueAllMessages() const { return QueueAllMessages; }
//  int getMessageAttemptsTransactionEvent() const { return MessageAttemptsTransactionEvent; }
//  int getMessageAttemptIntervalTransactionEvent() const { return MessageAttemptIntervalTransactionEvent; }
//  bool getUnlockOnEVSideDisconnect() const { return UnlockOnEVSideDisconnect; }
//  int getWebSocketPingInterval() const { return WebSocketPingInterval; }
//  int getResetRetries() const { return ResetRetries; }
//  int getMessageFieldLength() const { return MessageFieldLength; }
//  int getItemsPerMessageGetReport() const { return ItemsPerMessageGetReport; }
//  int getItemsPerMessageGetVariables() const { return ItemsPerMessageGetVariables; }
//  int getBytesPerMessageGetReport() const { return BytesPerMessageGetReport; }
//  int getBytesPerMessageGetVariables() const { return BytesPerMessageGetVariables; }
//  int getConfigurationValueSize() const { return ConfigurationValueSize; }
//  int getReportingValueSize() const { return ReportingValueSize; }
//  int getItemsPerMessageSetVariables() const { return ItemsPerMessageSetVariables; }
//  int getBytesPerMessageSetVariables() const { return BytesPerMessageSetVariables; }
//  RFC3339DateTime getDateTime() const { return DateTime; }
//  std::string getNtpSource() const { return NtpSource; }
//  std::string getNtpServerUri() const { return NtpServerUri; }
//  std::string getTimeOffset() const { return TimeOffset; }
//  std::string getNextTimeOffsetTransitionDateTime() const { return NextTimeOffsetTransitionDateTime; }
//  std::string getTimeOffsetNextTransition() const { return TimeOffsetNextTransition; }
//  std::string getTimeSource() const { return TimeSource; }
//  std::string getTimeZone() const { return TimeZone; }
//  int getTimeAdjustmentReportingThreshold() const { return TimeAdjustmentReportingThreshold; }
//  bool getCustomImplementationEnabled() const { return CustomImplementationEnabled; }
//
//  void setActiveNetworkProfile(int value) { ActiveNetworkProfile = value; }
//  void setAllowNewSessionsPendingFirmwareUpdate(bool value) { AllowNewSessionsPendingFirmwareUpdate = value; }
//  void setDefaultMessageTimeout(int value) { DefaultMessageTimeout = value; }
//  void setFileTransferProtocols(const std::string& value) { FileTransferProtocols = value; }
//  void setHeartbeatInterval(int value) { HeartbeatInterval = value; }
//  void setNetworkConfigurationPriority(const std::string& value) { NetworkConfigurationPriority = value; }
//  void setNetworkProfileConnectionAttempts(int value) { NetworkProfileConnectionAttempts = value; }
//  void setOfflineThreshold(int value) { OfflineThreshold = value; }
//  void setQueueAllMessages(bool value) { QueueAllMessages = value; }
//  void setMessageAttemptsTransactionEvent(int value) { MessageAttemptsTransactionEvent = value; }
//  void setMessageAttemptIntervalTransactionEvent(int value) { MessageAttemptIntervalTransactionEvent = value; }
//  void setUnlockOnEVSideDisconnect(bool value) { UnlockOnEVSideDisconnect = value; }
//  void setWebSocketPingInterval(int value) { WebSocketPingInterval = value; }
//  void setResetRetries(int value) { ResetRetries = value; }
//  void setMessageFieldLength(int value) { MessageFieldLength = value; }
//  void setItemsPerMessageGetReport(int value) { ItemsPerMessageGetReport = value; }
//  void setItemsPerMessageGetVariables(int value) { ItemsPerMessageGetVariables = value; }
//  void setBytesPerMessageGetReport(int value) { BytesPerMessageGetReport = value; }
//  void setBytesPerMessageGetVariables(int value) { BytesPerMessageGetVariables = value; }
//  void setConfigurationValueSize(int value) { ConfigurationValueSize = value; }
//  void setReportingValueSize(int value) { ReportingValueSize = value; }
//  void setItemsPerMessageSetVariables(int value) { ItemsPerMessageSetVariables = value; }
//  void setBytesPerMessageSetVariables(int value) { BytesPerMessageSetVariables = value; }
//  void setDateTime(const RFC3339DateTime& value) { DateTime = value; }
//  void setNtpSource(const std::string& value) { NtpSource = value; }
//  void setNtpServerUri(const std::string& value) { NtpServerUri = value; }
//  void setTimeOffset(const std::string& value) { TimeOffset = value; }
//  void setNextTimeOffsetTransitionDateTime(const std::string& value) { NextTimeOffsetTransitionDateTime = value; }
//  void setTimeOffsetNextTransition(const std::string& value) { TimeOffsetNextTransition = value; }
//  void setTimeSource(const std::string& value) { TimeSource = value; }
//  void setTimeZone(const std::string& value) { TimeZone = value; }
//  void setTimeAdjustmentReportingThreshold(int value) { TimeAdjustmentReportingThreshold = value; }
//  void setCustomImplementationEnabled(bool value) { CustomImplementationEnabled = value; }
  friend void to_json(nlohmann::json &json, const ConfigureKeyGeneral &configure) {
    json = nlohmann::json{
        {"ActiveNetworkProfile", configure.ActiveNetworkProfile},
        {"AllowNewSessionsPendingFirmwareUpdate", configure.AllowNewSessionsPendingFirmwareUpdate},
        {"DefaultMessageTimeout", configure.DefaultMessageTimeout},
        {"FileTransferProtocols", configure.FileTransferProtocols},
        {"HeartbeatInterval", configure.HeartbeatInterval},
        {"NetworkConfigurationPriority", configure.NetworkConfigurationPriority},
        {"NetworkProfileConnectionAttempts", configure.NetworkProfileConnectionAttempts},
        {"OfflineThreshold", configure.OfflineThreshold},
        {"QueueAllMessages", configure.QueueAllMessages},
        {"MessageAttemptsTransactionEvent", configure.MessageAttemptsTransactionEvent},
        {"MessageAttemptIntervalTransactionEvent", configure.MessageAttemptIntervalTransactionEvent},
        {"UnlockOnEVSideDisconnect", configure.UnlockOnEVSideDisconnect},
        {"WebSocketPingInterval", configure.WebSocketPingInterval},
        {"ResetRetries", configure.ResetRetries},
        {"MessageFieldLength", configure.MessageFieldLength},
        {"ItemsPerMessageGetReport", configure.ItemsPerMessageGetReport},
        {"ItemsPerMessageGetVariables", configure.ItemsPerMessageGetVariables},
        {"BytesPerMessageGetReport", configure.BytesPerMessageGetReport},
        {"BytesPerMessageGetVariables", configure.BytesPerMessageGetVariables},
        {"ConfigurationValueSize", configure.ConfigurationValueSize},
        {"ReportingValueSize", configure.ReportingValueSize},
        {"ItemsPerMessageSetVariables", configure.ItemsPerMessageSetVariables},
        {"BytesPerMessageSetVariables", configure.BytesPerMessageSetVariables},
        {"DateTime", configure.DateTime},
        {"NtpSource", configure.NtpSource},
        {"NtpServerUri", configure.NtpServerUri},
        {"TimeOffset", configure.TimeOffset},
        {"NextTimeOffsetTransitionDateTime", configure.NextTimeOffsetTransitionDateTime},
        {"TimeOffsetNextTransition", configure.TimeOffsetNextTransition},
        {"TimeSource", configure.TimeSource},
        {"TimeZone", configure.TimeZone},
        {"TimeAdjustmentReportingThreshold", configure.TimeAdjustmentReportingThreshold},
        {"CustomImplementationEnabled", configure.CustomImplementationEnabled}
    };
  }

  friend void from_json(const nlohmann::json& j, ConfigureKeyGeneral &config) {
    config.ActiveNetworkProfile = j.value("ActiveNetworkProfile", 0);
    config.AllowNewSessionsPendingFirmwareUpdate = j.value("AllowNewSessionsPendingFirmwareUpdate", false);
    config.DefaultMessageTimeout = j.value("DefaultMessageTimeout", 0);
    config.FileTransferProtocols = j.value("FileTransferProtocols", "");
    config.HeartbeatInterval = j.value("HeartbeatInterval", 0);
    config.NetworkConfigurationPriority = j.value("NetworkConfigurationPriority", "");
    config.NetworkProfileConnectionAttempts = j.value("NetworkProfileConnectionAttempts", 0);
    config.OfflineThreshold = j.value("OfflineThreshold", 0);
    config.QueueAllMessages = j.value("QueueAllMessages", false);
    config.MessageAttemptsTransactionEvent = j.value("MessageAttemptsTransactionEvent", 0);
    config.MessageAttemptIntervalTransactionEvent = j.value("MessageAttemptIntervalTransactionEvent", 0);
    config.UnlockOnEVSideDisconnect = j.value("UnlockOnEVSideDisconnect", false);
    config.WebSocketPingInterval = j.value("WebSocketPingInterval", 0);
    config.ResetRetries = j.value("ResetRetries", 0);
    config.MessageFieldLength = j.value("MessageFieldLength", 0);
    config.ItemsPerMessageGetReport = j.value("ItemsPerMessageGetReport", 0);
    config.ItemsPerMessageGetVariables = j.value("ItemsPerMessageGetVariables", 0);
    config.BytesPerMessageGetReport = j.value("BytesPerMessageGetReport", 0);
    config.BytesPerMessageGetVariables = j.value("BytesPerMessageGetVariables", 0);
    config.ConfigurationValueSize = j.value("ConfigurationValueSize", 0);
    config.ReportingValueSize = j.value("ReportingValueSize", 0);
    config.ItemsPerMessageSetVariables = j.value("ItemsPerMessageSetVariables", 0);
    config.BytesPerMessageSetVariables = j.value("BytesPerMessageSetVariables", 0);
    config.DateTime = j.value("DateTime", RFC3339DateTime());
    config.NtpSource = j.value("NtpSource", "");
    config.NtpServerUri = j.value("NtpServerUri", "");
    config.TimeOffset = j.value("TimeOffset", "");
    config.NextTimeOffsetTransitionDateTime = j.value("NextTimeOffsetTransitionDateTime", "");
    config.TimeOffsetNextTransition = j.value("TimeOffsetNextTransition", "");
    config.TimeSource = j.value("TimeSource", "");
    config.TimeZone = j.value("TimeZone", "");
    config.TimeAdjustmentReportingThreshold = j.value("TimeAdjustmentReportingThreshold", 0);
    config.CustomImplementationEnabled = j.value("CustomImplementationEnabled", false);
  }


};

#endif // ECHOOCPP_CONFIGUREKEYGENERAL_HPP
