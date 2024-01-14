//
// Created by 杨帆 on 2024/1/13.
//

#ifndef ECHOOCPP_CONFIGUREKEYGENERAL_HPP
#define ECHOOCPP_CONFIGUREKEYGENERAL_HPP
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../DataType/PrimitiveDatatypes.hpp"

using json = nlohmann::json;

class ConfigureKeyGeneral {
public:
  int ActiveNetworkProfile;
  bool AllowNewSessionsPendingFirmwareUpdate;
  int DefaultMessageTimeout;
  std::string FileTransferProtocols;
  int HeartbeatInterval;
  std::string NetworkConfigurationPriority;
  int NetworkProfileConnectionAttempts;
  int OfflineThreshold;
  bool QueueAllMessages;
  int MessageAttemptsTransactionEvent;
  int MessageAttemptIntervalTransactionEvent;
  bool UnlockOnEVSideDisconnect;
  int WebSocketPingInterval;
  int ResetRetries;
  int MessageFieldLength;
  int ItemsPerMessageGetReport;
  int ItemsPerMessageGetVariables;
  int BytesPerMessageGetReport;
  int BytesPerMessageGetVariables;
  int ConfigurationValueSize;
  int ReportingValueSize;
  int ItemsPerMessageSetVariables;
  int BytesPerMessageSetVariables;
  RFC3339DateTime DateTime;
  std::string NtpSource;
  std::string NtpServerUri;
  std::string TimeOffset;
  std::string NextTimeOffsetTransitionDateTime;
  std::string TimeOffsetNextTransition;
  std::string TimeSource;
  std::string TimeZone;
  int TimeAdjustmentReportingThreshold;
  bool CustomImplementationEnabled;

  ConfigureKeyGeneral() : ActiveNetworkProfile(0), AllowNewSessionsPendingFirmwareUpdate(false),
                          DefaultMessageTimeout(0), HeartbeatInterval(0), NetworkProfileConnectionAttempts(0),
                          OfflineThreshold(0), QueueAllMessages(false), MessageAttemptsTransactionEvent(0),
                          MessageAttemptIntervalTransactionEvent(0), UnlockOnEVSideDisconnect(false),
                          WebSocketPingInterval(0), ResetRetries(0), MessageFieldLength(0),
                          ItemsPerMessageGetReport(0), ItemsPerMessageGetVariables(0),
                          BytesPerMessageGetReport(0), BytesPerMessageGetVariables(0),
                          ConfigurationValueSize(0), ReportingValueSize(0), ItemsPerMessageSetVariables(0),
                          BytesPerMessageSetVariables(0), TimeAdjustmentReportingThreshold(0),
                          CustomImplementationEnabled(false) {
  }
  void to_json(nlohmann::json &json, const ConfigureKeyGeneral &configure) {
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

  friend void from_Json(const json& j, ConfigureKeyGeneral &config) {
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
    config.DateTime = j.value("DateTime", "");
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
