#ifndef ECHOOCPP_MESSAGEREQUEST_HPP
#define ECHOOCPP_MESSAGEREQUEST_HPP
#include "../DataType/Datatypes.hpp"
#include "../../MessageBase.hpp"

namespace OCPP201 {
    using namespace OCPP;
class AuthorizeRequest : public MessageCallRequest {
private:
  std::string certificate;
  std::string idToken;
  nlohmann::json iso15118CertificateHashData;

public:
  AuthorizeRequest(const std::string &certificate, const std::string &idToken,
                   const nlohmann::json &iso15118CertificateHashData)
      : certificate(certificate), idToken(idToken),
        iso15118CertificateHashData(iso15118CertificateHashData) {
    mAction = "AuthorizeRequest";
    mMessageId = Utility::generateMessageId();
  }

private:
  std::string toString() {
    mPayload["certificate"] = certificate;
    mPayload["idToken"] = idToken;
    mPayload["iso15118CertificateHashData"] = iso15118CertificateHashData;
    return this->build();
  }
};

class BootNotificationRequest : public MessageCallRequest {
public:
  BootReasonEnumType reason;
  ChargingStationType chargingStation;

  BootNotificationRequest() = default;
  BootNotificationRequest(
      const BootReasonEnumType &bootReason,
      const ChargingStationType &chargingStationInfo)
      : reason(bootReason), chargingStation(chargingStationInfo) {
  }

  std::string toString() override{
    mAction = "BootNotificationRequest";
    mPayload["reason"] =
        magic_enum::enum_name(this->reason);
    mPayload["chargingStation"] = chargingStation;
    return this->build();
  }
};

class CancelReservationRequest : public MessageCallRequest {
private:
  int reservationId;

public:
  explicit CancelReservationRequest(int reservationId)
      : reservationId(reservationId) {
    mAction = "CancelReservationRequest";
    mMessageId = Utility::generateMessageId();
  }

  std::string toString() override {
    mPayload["reservationId"] = reservationId;
    return this->build();
  }
private:
};

class CertificateSignedRequest : public MessageCallRequest {
private:
  std::vector<std::string> certificateChain;
  std::optional<CertificateSigningUseEnumType> certificateType;

public:
  explicit CertificateSignedRequest(
      const std::vector<std::string> &certChain,
      std::optional<CertificateSigningUseEnumType> certType = std::nullopt)
      : certificateChain(certChain), certificateType(certType) {
    mAction = "CertificateSignedRequest";
    mMessageId = Utility::generateMessageId();
  }

  std::string toString() {
    mPayload["certificateChain"] = certificateChain;
    if (certificateType.has_value()) {
      mPayload["certificateType"] =
          magic_enum::enum_name(certificateType.value());
    }
    return this->build();
  }
private:
};

class ChangeAvailabilityRequest : public MessageCallRequest {
private:
  OperationalStatusEnumType operationalStatus;
  std::optional<EVSEType> evse;

public:
  explicit ChangeAvailabilityRequest(
      const OperationalStatusEnumType &status,
      const std::optional<EVSEType> &evseInfo = std::nullopt)
      : operationalStatus(status), evse(evseInfo) {
    mAction = "ChangeAvailabilityRequest";
    mMessageId = Utility::generateMessageId();
  }
  std::string toString() override{
    mPayload["operationalStatus"] = magic_enum::enum_name(operationalStatus);

    if (evse.has_value()) {
      mPayload["evse"] = evse.value();
    }
    return this->build();
  }

private:
};

class ClearCacheResponse : public MessageCallRequest {
private:
  ClearCacheStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  explicit ClearCacheResponse(
      const ClearCacheStatusEnumType &clearCacheStatus,
      const std::optional<StatusInfoType> &info = std::nullopt)
      : status(clearCacheStatus), statusInfo(info) {
    mAction = "ClearCacheResponse";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["status"] = magic_enum::enum_name(status);

    if (statusInfo.has_value()) {
      mPayload["statusInfo"] = statusInfo.value();
    }
  }
};

class ClearChargingProfileRequest : public MessageCallRequest {
private:
  std::optional<int> chargingProfileId;
  std::optional<ClearChargingProfileType> chargingProfileCriteria;

public:
  explicit ClearChargingProfileRequest(
      const std::optional<int> &profileId,
      const std::optional<ClearChargingProfileType> &criteria = std::nullopt)
      : chargingProfileId(profileId), chargingProfileCriteria(criteria) {
    mAction = "ClearChargingProfileRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    if (chargingProfileId.has_value()) {
      mPayload["chargingProfileId"] = chargingProfileId.value();
    }

    if (chargingProfileCriteria.has_value()) {
      mPayload["chargingProfileCriteria"] = (chargingProfileCriteria.value());
    }
  }
};

class ClearDisplayMessageRequest : public MessageCallRequest {
private:
  int messageId;

public:
  explicit ClearDisplayMessageRequest(int messageId) : messageId(messageId) {
    mAction = "ClearDisplayMessageRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() { mPayload["id"] = messageId; }
};

class ClearedChargingLimitRequest : public MessageCallRequest {
private:
  ChargingLimitSourceEnumType chargingLimitSource;
  std::optional<int> evseId;

public:
  explicit ClearedChargingLimitRequest(
      const ChargingLimitSourceEnumType &limitSource,
      const std::optional<int> &identifier = std::nullopt)
      : chargingLimitSource(limitSource), evseId(identifier) {
    mAction = "ClearedChargingLimitRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["chargingLimitSource"] =
        magic_enum::enum_name(chargingLimitSource);
    if (evseId.has_value()) {
      mPayload["evseId"] = evseId.value();
    }
  }
};

class ClearVariableMonitoringRequest : public MessageCallRequest {
private:
  std::vector<int> monitorIds;

public:
  explicit ClearVariableMonitoringRequest(const std::vector<int> &monitorIds)
      : monitorIds(monitorIds) {
    mAction = "ClearVariableMonitoringRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() { mPayload["id"] = monitorIds; }
};

class CostUpdatedRequest : public MessageCallRequest {
private:
  double totalCost;
  std::string transactionId;

public:
  CostUpdatedRequest(double cost, const std::string &txnId)
      : totalCost(cost), transactionId(txnId) {
    mAction = "CostUpdatedRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["totalCost"] = totalCost;
    mPayload["transactionId"] = transactionId;
  }
};

class CustomerInformationRequest : public MessageCallRequest {
private:
  int requestId;
  bool report;
  bool clear;
  std::optional<std::string> customerIdentifier;
  std::optional<IdTokenType> idToken;
  std::optional<CertificateHashDataType> customerCertificate;

public:
  explicit CustomerInformationRequest(
      int reqId, bool shouldReport, bool shouldClear,
      const std::optional<std::string> &identifier,
      const std::optional<IdTokenType> &token,
      const std::optional<CertificateHashDataType> &certificate)
      : requestId(reqId), report(shouldReport), clear(shouldClear),
        customerIdentifier(identifier), idToken(token),
        customerCertificate(certificate) {
    mAction = "CustomerInformationRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["requestId"] = requestId;
    mPayload["report"] = report;
    mPayload["clear"] = clear;

    if (customerIdentifier.has_value()) {
      mPayload["customerIdentifier"] = customerIdentifier.value();
    }

    if (idToken.has_value()) {
      mPayload["idToken"] = (idToken.value());
    }

    if (customerCertificate.has_value()) {
      mPayload["customerCertificate"] = (customerCertificate.value());
    }
  }
};

class DataTransferRequest : public MessageCallRequest {
private:
  std::optional<std::string> messageId;
  std::optional<nlohmann::json> data;
  std::string vendorId;

public:
  explicit DataTransferRequest(
      const std::optional<std::string> &msgId,
      const std::optional<nlohmann::json> &transferData,
      const std::string &vendor)
      : messageId(msgId), data(transferData), vendorId(vendor) {
    mAction = "DataTransferRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    if (messageId.has_value()) {
      mPayload["messageId"] = messageId.value();
    }

    if (data.has_value()) {
      mPayload["data"] = data.value();
    }

    mPayload["vendorId"] = vendorId;
  }
};

class DeleteCertificateRequest : public MessageCallRequest {
private:
  CertificateHashDataType certificateHashData;

public:
  explicit DeleteCertificateRequest(const CertificateHashDataType &certHashData)
      : certificateHashData(certHashData) {
    mAction = "DeleteCertificateRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["certificateHashData"] = (certificateHashData);
  }
};

class FirmwareStatusNotificationRequest : public MessageCallRequest {
private:
  FirmwareStatusEnumType status;
  std::optional<int> requestId;

public:
  explicit FirmwareStatusNotificationRequest(
      const FirmwareStatusEnumType &firmwareStatus,
      const std::optional<int> &updateRequestId = std::nullopt)
      : status(firmwareStatus), requestId(updateRequestId) {
    mAction = "FirmwareStatusNotificationRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["status"] = magic_enum::enum_name(status);

    if (requestId.has_value()) {
      mPayload["requestId"] = requestId.value();
    }
  }
};

class Get15118EVCertificateRequest : public MessageCallRequest {
private:
  std::string iso15118SchemaVersion;
  CertificateActionEnumType action;
  std::string exiRequest;

public:
  explicit Get15118EVCertificateRequest(
      const std::string &schemaVersion,
      const CertificateActionEnumType &certificateAction,
      const std::string &base64EncodedRequest)
      : iso15118SchemaVersion(schemaVersion), action(certificateAction),
        exiRequest(base64EncodedRequest) {
    mAction = "Get15118EVCertificateRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["iso15118SchemaVersion"] = iso15118SchemaVersion;
    mPayload["action"] = magic_enum::enum_name(action);
    mPayload["exiRequest"] = exiRequest;
  }
};

class GetBaseReportRequest : public MessageCallRequest {
private:
  int requestId;
  ReportBaseEnumType reportBase;

public:
  [[nodiscard]] inline int getRequestId() {
      return this->requestId;
  }
  [[nodiscard]] inline ReportBaseEnumType getReportBase() {
      return this->reportBase;
  }
  inline void setRequestId(int id) {
    this->requestId = id;
  }
  inline void setReportBase(ReportBaseEnumType tType) {
    this->reportBase = tType;
  }
  GetBaseReportRequest() = default;
  explicit GetBaseReportRequest(int reqId,
                                const ReportBaseEnumType &reportBaseType)
      : requestId(reqId), reportBase(reportBaseType) {
    mAction = "GetBaseReportRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }
  friend void from_json(const nlohmann::json &json, GetBaseReportRequest &data) {
    if (json.contains("requestId") && json.at("requestId").is_number_integer()) {
      json.at("requestId").get_to(data.requestId);
    } else {
      data.requestId = 0;
    }

    if (json.contains("reportBase") && json.at("reportBase").is_string()) {
      auto tmp = magic_enum::enum_cast<ReportBaseEnumType>(json.at("reportBase"));
      if (tmp.has_value()) {
        data.reportBase = tmp.value();
      } else {
        data.reportBase = ReportBaseEnumType::ConfigurationInventory;
      }
    }
  }

private:
  void build() {
    mPayload["requestId"] = requestId;
    mPayload["reportBase"] = magic_enum::enum_name(reportBase);
  }
};

class GetCertificateStatusRequest : public MessageCallRequest {
private:
  OCSPRequestDataType ocspRequestData;

public:
  explicit GetCertificateStatusRequest(const OCSPRequestDataType &requestData)
      : ocspRequestData(requestData) {
    mAction = "GetCertificateStatusRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() { mPayload["ocspRequestData"] = (ocspRequestData); }
};

class GetChargingProfilesRequest : public MessageCallRequest {
private:
  int requestId;
  std::optional<int> evseId;
  ChargingProfileCriterionType chargingProfile;

public:
  explicit GetChargingProfilesRequest(
      int reqId, const std::optional<int> &identifier,
      const ChargingProfileCriterionType &criterion)
      : requestId(reqId), evseId(identifier), chargingProfile(criterion) {
    mAction = "GetChargingProfilesRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["requestId"] = requestId;

    if (evseId.has_value()) {
      mPayload["evseId"] = evseId.value();
    }

    mPayload["chargingProfile"] = (chargingProfile);
  }
};

class GetCompositeScheduleRequest : public MessageCallRequest {
private:
  int duration;
  std::optional<ChargingRateUnitEnumType> chargingRateUnit;
  int evseId;

public:
  GetCompositeScheduleRequest(
      int dur, const std::optional<ChargingRateUnitEnumType> &rateUnit,
      int identifier)
      : duration(dur), chargingRateUnit(rateUnit), evseId(identifier) {
    mAction = "GetCompositeScheduleRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["duration"] = duration;

    if (chargingRateUnit.has_value()) {
      mPayload["chargingRateUnit"] =
          magic_enum::enum_name(chargingRateUnit.value());
    }

    mPayload["evseId"] = evseId;
  }
};

class GetDisplayMessagesRequest : public MessageCallRequest {
private:
  std::vector<int> messageIds;
  int requestId;
  std::optional<MessagePriorityEnumType> priority;
  std::optional<MessageStateEnumType> state;

public:
  explicit GetDisplayMessagesRequest(
      const std::vector<int> &ids, int reqId,
      const std::optional<MessagePriorityEnumType> &msgPriority,
      const std::optional<MessageStateEnumType> &msgState)
      : messageIds(ids), requestId(reqId), priority(msgPriority),
        state(msgState) {
    mAction = "GetDisplayMessagesRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    if (!messageIds.empty()) {
      mPayload["id"] = messageIds;
    }

    mPayload["requestId"] = requestId;

    if (priority.has_value()) {
      mPayload["priority"] = magic_enum::enum_name(priority.value());
    }

    if (state.has_value()) {
      mPayload["state"] = magic_enum::enum_name(state.value());
    }
  }
};

class GetInstalledCertificateIdsRequest : public MessageCallRequest {
private:
  std::vector<GetCertificateIdUseEnumType> certificateTypes;

public:
  explicit GetInstalledCertificateIdsRequest(
      const std::vector<GetCertificateIdUseEnumType> &certTypes)
      : certificateTypes(certTypes) {
    mAction = "GetInstalledCertificateIdsRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    if (!certificateTypes.empty()) {
      std::vector<std::string> certTypeNames;
      for (const auto &certType : certificateTypes) {
        certTypeNames.emplace_back(magic_enum::enum_name(certType));
      }
      mPayload["certificateType"] = certTypeNames;
    }
  }
};

class GetLogRequest : public MessageCallRequest {
private:
  LogEnumType logType;
  int requestId;
  std::optional<int> retries;
  std::optional<int> retryInterval;
  LogParametersType logParameters;

public:
  explicit GetLogRequest(const LogEnumType &log, int reqId,
                         const std::optional<int> &numRetries,
                         const std::optional<int> &retryInt,
                         const LogParametersType &logParams)
      : logType(log), requestId(reqId), retries(numRetries),
        retryInterval(retryInt), logParameters(logParams) {
    mAction = "GetLogRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["logType"] = magic_enum::enum_name(logType);
    mPayload["requestId"] = requestId;

    if (retries.has_value()) {
      mPayload["retries"] = retries.value();
    }

    if (retryInterval.has_value()) {
      mPayload["retryInterval"] = retryInterval.value();
    }

    mPayload["log"] = (logParameters);
  }
};

class GetMonitoringReportRequest : public MessageCallRequest {
private:
  int requestId;
  std::vector<MonitoringCriterionEnumType> monitoringCriteria;
  std::vector<ComponentVariableType> componentVariables;

public:
  GetMonitoringReportRequest(
      int reqId, const std::vector<MonitoringCriterionEnumType> &criteria,
      const std::vector<ComponentVariableType> &componentVars)
      : requestId(reqId), monitoringCriteria(criteria),
        componentVariables(componentVars) {
    mAction = "GetMonitoringReportRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["requestId"] = requestId;

    if (!monitoringCriteria.empty()) {
      std::vector<std::string> criteriaNames;
      for (const auto &criterion : monitoringCriteria) {
        criteriaNames.emplace_back(magic_enum::enum_name(criterion));
      }
      mPayload["monitoringCriteria"] = criteriaNames;
    }

    if (!componentVariables.empty()) {
      mPayload["componentVariable"] = (componentVariables);
    }
  }
};

class GetReportRequest : public MessageCallRequest {
private:
  int requestId;
  std::vector<ComponentCriterionEnumType> componentCriteria;
  std::vector<ComponentVariableType> componentVariables;

public:
  GetReportRequest(int reqId,
                   const std::vector<ComponentCriterionEnumType> &criteria,
                   const std::vector<ComponentVariableType> &componentVars)
      : requestId(reqId), componentCriteria(criteria),
        componentVariables(componentVars) {
    mAction = "GetReportRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["requestId"] = requestId;

    if (!componentCriteria.empty()) {
      std::vector<std::string> criteriaNames;
      for (const auto &criterion : componentCriteria) {
        criteriaNames.emplace_back(magic_enum::enum_name(criterion));
      }
      mPayload["componentCriteria"] = criteriaNames;
    }

    if (!componentVariables.empty()) {
      mPayload["componentVariable"] = (componentVariables);
    }
  }
};

class GetTransactionStatusRequest : public MessageCallRequest {
private:
  std::optional<IdentifierString> transactionId;

public:
  explicit GetTransactionStatusRequest(
      const std::optional<IdentifierString> &transId = std::nullopt)
      : transactionId(transId) {
    mAction = "GetTransactionStatusRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    if (transactionId.has_value()) {
      mPayload["transactionId"] = transactionId.value();
    }
  }
};

class GetVariablesRequest : public MessageCallRequest {
public:
    std::vector<GetVariableDataType> getVariableData;
    GetVariablesRequest() = default;
    explicit GetVariablesRequest(
      const std::vector<GetVariableDataType> &variableData)
      : getVariableData(variableData) {
    mAction = "GetVariablesRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }
    friend void from_json(const nlohmann::json& j, GetVariablesRequest& data) {
        std::cout << j.dump() << std::endl;
        if (j.contains("getVariableData")) {
            data.getVariableData = j.at("getVariableData").get<std::vector<GetVariableDataType>>();
        } else {
            std::cout << "no data" << std::endl;
        }
    }

private:
  void build() { mPayload["getVariableData"] = (getVariableData); }
};

class InstallCertificateRequest : public MessageCallRequest {
private:
  InstallCertificateUseEnumType certificateType;
  std::string certificate;

public:
  explicit InstallCertificateRequest(
      const InstallCertificateUseEnumType &certType, const std::string &cert)
      : certificateType(certType), certificate(cert) {
    mAction = "InstallCertificateRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["certificateType"] = magic_enum::enum_name(certificateType);
    mPayload["certificate"] = certificate;
  }
};

class LogStatusNotificationRequest : public MessageCallRequest {
private:
  UploadLogStatusEnumType status;
  std::optional<int> requestId;

public:
  explicit LogStatusNotificationRequest(
      const UploadLogStatusEnumType &logStatus,
      const std::optional<int> &reqId = std::nullopt)
      : status(logStatus), requestId(reqId) {
    mAction = "LogStatusNotificationRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["status"] = magic_enum::enum_name(status);

    if (requestId.has_value()) {
      mPayload["requestId"] = requestId.value();
    }
  }
};

class MeterValuesRequest : public MessageCallRequest {
private:
  int evseId;
  std::vector<MeterValueType> meterValues;

public:
  MeterValuesRequest(int id, const std::vector<MeterValueType> &values)
      : evseId(id), meterValues(values) {
    mAction = "MeterValuesRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["evseId"] = evseId;
    mPayload["meterValue"] = (meterValues);
  }
};

class NotifyChargingLimitRequest : public MessageCallRequest {
private:
  std::optional<int> evseId;
  ChargingLimitType chargingLimit;
  std::vector<ChargingScheduleType> chargingSchedule;

public:
  NotifyChargingLimitRequest(
      const std::optional<int> &id, const ChargingLimitType &limit,
      const std::vector<ChargingScheduleType> &schedule = {})
      : evseId(id), chargingLimit(limit), chargingSchedule(schedule) {
    mAction = "NotifyChargingLimitRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    if (evseId.has_value()) {
      mPayload["evseId"] = evseId.value();
    }

    mPayload["chargingLimit"] = (chargingLimit);

    if (!chargingSchedule.empty()) {
      mPayload["chargingSchedule"] = (chargingSchedule);
    }
  }
};

class NotifyCustomerInformationRequest : public MessageCallRequest {
private:
  std::string data;
  bool tbc;
  int seqNo;
  std::string generatedAt;
  int requestId;

public:
  explicit NotifyCustomerInformationRequest(const std::string &customerData,
                                            bool toBeContinued,
                                            int sequenceNumber,
                                            const std::string &timestamp,
                                            int reqId)
      : data(customerData), tbc(toBeContinued), seqNo(sequenceNumber),
        generatedAt(timestamp), requestId(reqId) {
    mAction = "NotifyCustomerInformationRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["data"] = data;
    mPayload["tbc"] = tbc;
    mPayload["seqNo"] = seqNo;
    mPayload["generatedAt"] = generatedAt;
    mPayload["requestId"] = requestId;
  }
};

class NotifyDisplayMessagesRequest : public MessageCallRequest {
private:
  int requestId;
  bool tbc;
  std::vector<MessageInfoType> messageInfo;

public:
  NotifyDisplayMessagesRequest(int displayRequestId, bool toBeContinued,
                               const std::vector<MessageInfoType> &info)
      : requestId(displayRequestId), tbc(toBeContinued), messageInfo(info) {
    mAction = "NotifyDisplayMessagesRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["requestId"] = requestId;
    mPayload["tbc"] = tbc;
    mPayload["messageInfo"] = (messageInfo);
  }
};

class NotifyEVChargingNeedsRequest : public MessageCallRequest {
private:
  std::optional<int> maxScheduleTuples;
  int evseId;
  ChargingNeedsType chargingNeeds;

public:
  NotifyEVChargingNeedsRequest(const std::optional<int> &maxTuples,
                               int stationId, const ChargingNeedsType &needs)
      : maxScheduleTuples(maxTuples), evseId(stationId), chargingNeeds(needs) {
    mAction = "NotifyEVChargingNeedsRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    if (maxScheduleTuples.has_value()) {
      mPayload["maxScheduleTuples"] = maxScheduleTuples.value();
    }

    mPayload["evseId"] = evseId;
    mPayload["chargingNeeds"] = (chargingNeeds);
  }
};

class NotifyEVChargingScheduleRequest : public MessageCallRequest {
private:
  std::string timeBase;
  int evseId;
  ChargingScheduleType chargingSchedule;

public:
  NotifyEVChargingScheduleRequest(const std::string &baseTime, int stationId,
                                  const ChargingScheduleType &schedule)
      : timeBase(baseTime), evseId(stationId), chargingSchedule(schedule) {
    mAction = "NotifyEVChargingScheduleRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["timeBase"] = timeBase;
    mPayload["evseId"] = evseId;
    mPayload["chargingSchedule"] = (chargingSchedule);
  }
};

class NotifyEventRequest : public MessageCallRequest {
private:
  std::string generatedAt;
  bool tbc;
  int seqNo;
  std::vector<EventDataType> eventData;

public:
  NotifyEventRequest(const std::string &timestamp, bool toBeContinued,
                     int sequenceNumber, const std::vector<EventDataType> &data)
      : generatedAt(timestamp), tbc(toBeContinued), seqNo(sequenceNumber),
        eventData(data) {
    mAction = "NotifyEventRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["generatedAt"] = generatedAt;
    mPayload["tbc"] = tbc;
    mPayload["seqNo"] = seqNo;
    mPayload["eventData"] = (eventData);
  }
};

class NotifyMonitoringReportRequest : public MessageCallRequest {
private:
  int requestId;
  bool tbc;
  int seqNo;
  std::string generatedAt;
  std::vector<MonitoringDataType> monitorData;

public:
  NotifyMonitoringReportRequest(int monitoringRequestId, bool toBeContinued,
                                int sequenceNumber,
                                const std::string &timestamp,
                                const std::vector<MonitoringDataType> &data)
      : requestId(monitoringRequestId), tbc(toBeContinued),
        seqNo(sequenceNumber), generatedAt(timestamp), monitorData(data) {
    mAction = "NotifyMonitoringReportRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["requestId"] = requestId;
    mPayload["tbc"] = tbc;
    mPayload["seqNo"] = seqNo;
    mPayload["generatedAt"] = generatedAt;
    mPayload["monitor"] = (monitorData);
  }
};

class NotifyReportRequest : public MessageCallRequest {

public:
  NotifyReportRequest() = default;
  NotifyReportRequest(int reportRequestId, const std::string &timestamp,
                      bool toBeContinued, int sequenceNumber,
                      const std::vector<ReportDataType> &data)
      : requestId(reportRequestId), generatedAt(timestamp), tbc(toBeContinued),
        seqNo(sequenceNumber), reportData(data) {
    mAction = "NotifyReportRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }
  int requestId;
  std::string generatedAt;
  bool tbc;
  int seqNo;
  std::vector<ReportDataType> reportData;

private:
  void build() {
    mPayload["requestId"] = requestId;
    mPayload["generatedAt"] = generatedAt;
    mPayload["tbc"] = tbc;
    mPayload["seqNo"] = seqNo;
    mPayload["reportData"] = (reportData);
  }
};

class PublishFirmwareRequest : public MessageCallRequest {
private:
  std::string location;
  int retries;
  std::string checksum;
  int requestId;
  int retryInterval;

public:
  PublishFirmwareRequest(const std::string &firmwareLocation, int numRetries,
                         const std::string &md5Checksum, int publishRequestId,
                         int intervalBetweenRetries = 0)
      : location(firmwareLocation), retries(numRetries), checksum(md5Checksum),
        requestId(publishRequestId), retryInterval(intervalBetweenRetries) {
    mAction = "PublishFirmwareRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["location"] = location;
    mPayload["retries"] = retries;
    mPayload["checksum"] = checksum;
    mPayload["requestId"] = requestId;
    if (retryInterval > 0) {
      mPayload["retryInterval"] = retryInterval;
    }
  }
};

class PublishFirmwareStatusNotificationRequest : public MessageCallRequest {
private:
  PublishFirmwareStatusEnumType status;
  std::vector<std::string> locations;
  std::optional<int> requestId;

public:
  PublishFirmwareStatusNotificationRequest(
      PublishFirmwareStatusEnumType firmwareStatus,
      const std::vector<std::string> &firmwareLocations,
      const std::optional<int> &publishRequestId = std::nullopt)
      : status(firmwareStatus), locations(firmwareLocations),
        requestId(publishRequestId) {
    mAction = "PublishFirmwareStatusNotificationRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["status"] = magic_enum::enum_name(status);

    if (!locations.empty()) {
      mPayload["location"] = locations;
    }

    if (requestId.has_value()) {
      mPayload["requestId"] = requestId.value();
    }
  }
};

class ReportChargingProfilesRequest : public MessageCallRequest {
private:
  int requestId;
  ChargingLimitSourceEnumType chargingLimitSource;
  bool tbc;
  int evseId;
  std::vector<ChargingProfileType> chargingProfiles;

public:
  ReportChargingProfilesRequest(
      int reportRequestId, ChargingLimitSourceEnumType limitSource,
      bool toBeContinued, int evseIdentifier,
      const std::vector<ChargingProfileType> &profiles)
      : requestId(reportRequestId), chargingLimitSource(limitSource),
        tbc(toBeContinued), evseId(evseIdentifier), chargingProfiles(profiles) {
    mAction = "ReportChargingProfilesRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["requestId"] = requestId;
    mPayload["chargingLimitSource"] =
        magic_enum::enum_name(chargingLimitSource);
    mPayload["tbc"] = tbc;
    mPayload["evseId"] = evseId;
    mPayload["chargingProfiles"] = (chargingProfiles);
  }
};

class RequestStartTransactionRequest : public MessageCallRequest {
private:
  std::optional<int> evseId;
  int remoteStartId;
  IdTokenType idToken;
  std::optional<ChargingProfileType> chargingProfile;
  std::optional<IdTokenType> groupIdToken;

public:
  RequestStartTransactionRequest(
      const std::optional<int> &evseIdentifier, int startRequestId,
      const IdTokenType &tokenId,
      const std::optional<ChargingProfileType> &profile,
      const std::optional<IdTokenType> &groupToken = std::nullopt)
      : evseId(evseIdentifier), remoteStartId(startRequestId), idToken(tokenId),
        chargingProfile(profile), groupIdToken(groupToken) {
    mAction = "RequestStartTransactionRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    if (evseId.has_value()) {
      mPayload["evseId"] = evseId.value();
    }

    mPayload["remoteStartId"] = remoteStartId;
    mPayload["idToken"] = idToken;

    if (chargingProfile.has_value()) {
      mPayload["chargingProfile"] = (chargingProfile.value());
    }

    if (groupIdToken.has_value()) {
      mPayload["groupIdToken"] = groupIdToken.value();
    }
  }
};

class RequestStopTransactionRequest : public MessageCallRequest {
private:
  std::string transactionId;

public:
  RequestStopTransactionRequest(const std::string &transactionIdentifier)
      : transactionId(transactionIdentifier) {
    mAction = "RequestStopTransactionRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() { mPayload["transactionId"] = transactionId; }
};

class ReservationStatusUpdateRequest : public MessageCallRequest {
private:
  int reservationId;
  ReservationUpdateStatusEnumType reservationUpdateStatus;

public:
  ReservationStatusUpdateRequest(int reservationIdentifier,
                                 ReservationUpdateStatusEnumType updateStatus)
      : reservationId(reservationIdentifier),
        reservationUpdateStatus(updateStatus) {
    mAction = "ReservationStatusUpdateRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["reservationId"] = reservationId;
    mPayload["reservationUpdateStatus"] =
        magic_enum::enum_name(reservationUpdateStatus);
  }
};

class ReserveNowRequest : public MessageCallRequest {
private:
  int reservationId;
  std::string expiryDateTime;
  std::optional<ConnectorEnumType> connectorType;
  std::optional<int> evseId;
  IdTokenType idToken;
  std::optional<IdTokenType> groupIdToken;

public:
  ReserveNowRequest(
      int reservationIdentifier, const std::string &expiryDate,
      const IdTokenType &token,
      const std::optional<ConnectorEnumType> &connector = std::nullopt,
      const std::optional<int> &evseIdentifier = std::nullopt,
      const std::optional<IdTokenType> &groupToken = std::nullopt)
      : reservationId(reservationIdentifier), expiryDateTime(expiryDate),
        connectorType(connector), evseId(evseIdentifier), idToken(token),
        groupIdToken(groupToken) {
    mAction = "ReserveNowRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["id"] = reservationId;
    mPayload["expiryDateTime"] = expiryDateTime;
    if (connectorType.has_value()) {
      mPayload["connectorType"] = magic_enum::enum_name(connectorType.value());
    }
    if (evseId.has_value()) {
      mPayload["evseId"] = evseId.value();
    }
    mPayload["idToken"] = idToken;
    if (groupIdToken.has_value()) {
      mPayload["groupIdToken"] = groupIdToken.value();
    }
  }
};

class ResetRequest : public MessageCallRequest {
public:
  ResetEnumType resetType;
  std::optional<int> evseId;
  ResetRequest() = default;
  ResetRequest(ResetEnumType type,
               const std::optional<int> &evseIdentifier = std::nullopt)
      : resetType(type), evseId(evseIdentifier) {
    mAction = "ResetRequest";
    mMessageId = Utility::generateMessageId();
  }
  std::string toString() override{
    mPayload = nlohmann::json {
      {"type", magic_enum::enum_name(resetType)},
    };
    if (evseId.has_value()) {
      mPayload["evseId"] = evseId.value();
    }
    return this->build();
  }

  friend void from_json(const nlohmann::json &json, ResetRequest &data) {
    if (json.contains("type") && json.at("type").is_string()) {
      auto tmp = magic_enum::enum_cast<ResetEnumType>(json.at("type"));
      if (tmp.has_value()) {
        data.resetType = tmp.value();
      } else {
        data.resetType = ResetEnumType::OnIdle;
      }
    }
    if (json.contains("evseId") && json.at("evseId").is_number_integer()) {
      data.evseId = std::optional<int>(json.at("evseId"));
    } else {
      data.evseId = std::nullopt;
    }
  }


};

class SecurityEventNotificationRequest : public MessageCallRequest {
private:
  std::string eventType;
  RFC3339DateTime timestamp;
  std::optional<std::string> technicalInfo;

public:
  SecurityEventNotificationRequest(
      const std::string &type, const RFC3339DateTime &eventTimestamp,
      const std::optional<std::string> &techInfo = std::nullopt)
      : eventType(type), timestamp(eventTimestamp), technicalInfo(techInfo) {
    mAction = "SecurityEventNotificationRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["type"] = eventType;
    mPayload["timestamp"] = timestamp;
    if (technicalInfo.has_value()) {
      mPayload["techInfo"] = technicalInfo.value();
    }
  }
};

class SendLocalListRequest : public MessageCallRequest {
private:
  int versionNumber;
  UpdateEnumType updateType;
  std::vector<AuthorizationData> localAuthorizationList;

public:
  SendLocalListRequest(int version, UpdateEnumType type,
                       const std::vector<AuthorizationData> &authList = {})
      : versionNumber(version), updateType(type),
        localAuthorizationList(authList) {
    mAction = "SendLocalListRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["versionNumber"] = versionNumber;
    mPayload["updateType"] = magic_enum::enum_name(updateType);

    if (!localAuthorizationList.empty()) {
      mPayload["localAuthorizationList"] = localAuthorizationList;
    }
  }
};

class SetChargingProfileRequest : public MessageCallRequest {
private:
  int evseId;
  ChargingProfileType chargingProfile;

public:
  SetChargingProfileRequest(int evse, const ChargingProfileType &profile)
      : evseId(evse), chargingProfile(profile) {
    mAction = "SetChargingProfileRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["evseId"] = evseId;
    mPayload["chargingProfile"] = chargingProfile;
  }
};

class SetDisplayMessageRequest : public MessageCallRequest {
private:
  MessageInfoType message;

public:
  SetDisplayMessageRequest(const MessageInfoType &msg) : message(msg) {
    mAction = "SetDisplayMessageRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() { mPayload["message"] = message; }
};

class SetMonitoringBaseRequest : public MessageCallRequest {
private:
  MonitoringBaseEnumType monitoringBase;

public:
  SetMonitoringBaseRequest(const MonitoringBaseEnumType &base)
      : monitoringBase(base) {
    mAction = "SetMonitoringBaseRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["monitoringBase"] = magic_enum::enum_name(monitoringBase);
  }
};

class SetMonitoringLevelRequest : public MessageCallRequest {
private:
  int severity;

public:
  SetMonitoringLevelRequest(int severityLevel) : severity(severityLevel) {
    mAction = "SetMonitoringLevelRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() { mPayload["severity"] = severity; }
};

class SetNetworkProfileRequest : public MessageCallRequest {
public:
    int configurationSlot;
    NetworkConnectionProfileType connectionData;
    SetNetworkProfileRequest() = default;
  SetNetworkProfileRequest(
      int slot, const NetworkConnectionProfileType &connectionProfile)
      : configurationSlot(slot), connectionData(connectionProfile) {
    mAction = "SetNetworkProfileRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }
friend void from_json(const nlohmann::json& j, SetNetworkProfileRequest& data) {
  data.configurationSlot = j.at("configurationSlot").get<int>();
  data.connectionData = j.at("connectionData").get<NetworkConnectionProfileType>();
}

private:
  void build() {
    mPayload["configurationSlot"] = configurationSlot;
    mPayload["connectionData"] = connectionData;
  }
};

class SetVariableMonitoringRequest : public MessageCallRequest {
private:
  std::vector<SetMonitoringDataType> setMonitoringData;

public:
  SetVariableMonitoringRequest(
      const std::vector<SetMonitoringDataType> &monitoringData)
      : setMonitoringData(monitoringData) {
    mAction = "SetVariableMonitoringRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() { mPayload["setMonitoringData"] = setMonitoringData; }
};

class SetVariablesRequest : public MessageCallRequest {
public:
  std::vector<SetVariableDataType> setVariableData;

  SetVariablesRequest() {
    this->build();
  }
  SetVariablesRequest(const std::vector<SetVariableDataType> &variableData)
      : setVariableData(variableData) {
    this->build();
  }

  friend void from_json(const nlohmann::json& j, SetVariablesRequest& data) {
    if (j.contains("setVariableData")) {
      data.setVariableData = j.at("setVariableData").get<std::vector<SetVariableDataType>>();
    }
    data.build();
  }
  friend void to_json(nlohmann::json& j, const SetVariablesRequest& data) {
    j.at("setVariableData") = data.setVariableData;
  }

private:
  void build(){
    this->mAction = "SetVariablesRequest";
    this->mPayload["setVariableData"] = setVariableData;
  }
};

class SignCertificateRequest : public MessageCallRequest {
private:
  std::string csr;
  CertificateSigningUseEnumType certificateType;

public:
  SignCertificateRequest(
      const std::string &csr,
      const CertificateSigningUseEnumType &certType =
          CertificateSigningUseEnumType::ChargingStationCertificate)
      : csr(csr), certificateType(certType) {
    mAction = "SignCertificateRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["csr"] = csr;
    mPayload["certificateType"] = magic_enum::enum_name(certificateType);
  }
};

class StatusNotificationRequest : public MessageCallRequest {
public:
  RFC3339DateTime timestamp;
  ConnectorStatusEnumType connectorStatus;
  int evseId;
  int connectorId;
  StatusNotificationRequest() {

    this->timestamp.setDateTime(std::chrono::system_clock::now());
    this->connectorStatus = ConnectorStatusEnumType::Unavailable;
    this->evseId = 0;
    this->connectorId = 0;
     this->mAction = "StatusNotification";
  }

  std::string toString() override{
    mPayload["timestamp"] = timestamp.toString();
    mPayload["connectorStatus"] = magic_enum::enum_name(connectorStatus);
    mPayload["evseId"] = evseId;
    mPayload["connectorId"] = connectorId;
    return this->build();
  }
};

class TransactionEventRequest : public MessageCallRequest {
private:
  TransactionEventEnumType eventType;
  std::string timestamp;
  TriggerReasonEnumType triggerReason;
  int seqNo;
  bool offline;
  int numberOfPhasesUsed;
  int cableMaxCurrent;
  int reservationId;
  TransactionType transactionInfo;
  IdTokenType idToken;
  EVSEType evse;
  std::vector<MeterValueType> meterValues;

public:
  TransactionEventRequest(const TransactionEventEnumType &eventType,
                          const std::string &timestamp,
                          const TriggerReasonEnumType &triggerReason, int seqNo,
                          bool offline, int numberOfPhasesUsed,
                          int cableMaxCurrent, int reservationId,
                          const TransactionType &transactionInfo,
                          const IdTokenType &idToken, const EVSEType &evse,
                          const std::vector<MeterValueType> &meterValues)
      : eventType(eventType), timestamp(timestamp),
        triggerReason(triggerReason), seqNo(seqNo), offline(offline),
        numberOfPhasesUsed(numberOfPhasesUsed),
        cableMaxCurrent(cableMaxCurrent), reservationId(reservationId),
        transactionInfo(transactionInfo), idToken(idToken), evse(evse),
        meterValues(meterValues) {
    mAction = "TransactionEventRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["eventType"] = magic_enum::enum_name(eventType);
    mPayload["timestamp"] = timestamp;
    mPayload["triggerReason"] = magic_enum::enum_name(triggerReason);
    mPayload["seqNo"] = seqNo;
    mPayload["offline"] = offline;
    mPayload["numberOfPhasesUsed"] = numberOfPhasesUsed;
    mPayload["cableMaxCurrent"] = cableMaxCurrent;
    mPayload["reservationId"] = reservationId;
    mPayload["transactionInfo"] = transactionInfo;
    mPayload["idToken"] = idToken;
    mPayload["evse"] = evse;

    mPayload["meterValues"] = meterValues;
  }
};

class TriggerMessageRequest : public MessageCallRequest {
private:
  MessageTriggerEnumType requestedMessage;
  EVSEType evse;

public:
  TriggerMessageRequest(const MessageTriggerEnumType &requestedMessage,
                        const EVSEType &evse)
      : requestedMessage(requestedMessage), evse(evse) {
    mAction = "TriggerMessageRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["requestedMessage"] = magic_enum::enum_name(requestedMessage);
    mPayload["evse"] = evse;
  }
};

class UnlockConnectorRequest : public MessageCallRequest {
private:
  int evseId;
  int connectorId;

public:
  UnlockConnectorRequest(int evseId, int connectorId)
      : evseId(evseId), connectorId(connectorId) {
    mAction = "UnlockConnectorRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["evseId"] = evseId;
    mPayload["connectorId"] = connectorId;
  }
};

class UnpublishFirmwareRequest : public MessageCallRequest {
private:
  std::string checksum;

public:
  UnpublishFirmwareRequest(const std::string &checksum) : checksum(checksum) {
    mAction = "UnpublishFirmwareRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() { mPayload["checksum"] = checksum; }
};

class UpdateFirmwareRequest : public MessageCallRequest {
private:
  int retries;
  int retryInterval;
  std::string requestId;
  FirmwareType firmware;

public:
  UpdateFirmwareRequest(int retries, int retryInterval,
                        const std::string &requestId,
                        const FirmwareType &firmware)
      : retries(retries), retryInterval(retryInterval), requestId(requestId),
        firmware(firmware) {
    mAction = "UpdateFirmwareRequest";
    mMessageId = Utility::generateMessageId();
    build();
  }

private:
  void build() {
    mPayload["retries"] = retries;
    mPayload["retryInterval"] = retryInterval;
    mPayload["requestId"] = requestId;
    mPayload["firmware"] =
        firmware; // Assuming FirmwareType has a toJson() method
  }
};
class HeartbeatRequest : public MessageCallRequest {
public:
  HeartbeatRequest() {
      MessageCallRequest::mAction = "Heartbeat";
      MessageCallRequest::mPayload = nlohmann::json::object();
  }
};

} // namespace OCPP201
#endif // ECHOOCPP_MESSAGEREQUEST_HPP
