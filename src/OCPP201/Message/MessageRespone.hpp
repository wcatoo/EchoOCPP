#ifndef ECHOOCPP_MESSAGERESPONE_HPP
#define ECHOOCPP_MESSAGERESPONE_HPP

namespace OCPP201 {
#include "../Datatypes.hpp"

class AuthorizeResponse {
private:
  AuthorizeCertificateStatusEnumType certificateStatus;
  IdTokenInfoType idTokenInfo;
public:
  AuthorizeCertificateStatusEnumType getCertificateStatus() {
    return this->certificateStatus;
  }
  IdTokenInfoType getIdTokenInfo() {
    return this->idTokenInfo;
  }
  friend void from_json(const nlohmann::json& tJson, AuthorizeResponse &tData) {
    if (tJson.contains("certificateStatus")) {
      auto tmp = magic_enum::enum_cast<AuthorizeCertificateStatusEnumType>(tJson.at("certificateStatus"));
      if (tmp.has_value()) {
        tData.certificateStatus = tmp.value();
      }
    }
    tData.idTokenInfo = tJson.at("idTokenInfo");
  }
};

class BootNotificationResponse {
private:
  RFC3339DateTime currentTime;
  int interval;
  RegistrationStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  BootNotificationResponse() = default;
  explicit BootNotificationResponse(
      const RFC3339DateTime& currentTimeParam,
      int intervalParam,
      RegistrationStatusEnumType statusParam,
      const std::optional<StatusInfoType>& statusInfoParam = std::nullopt)
      : currentTime(currentTimeParam),
        interval(intervalParam),
        status(statusParam),
        statusInfo(statusInfoParam) {}

  // Getter functions
  [[nodiscard]] RFC3339DateTime getCurrentTime() const { return currentTime; }
  [[nodiscard]] int getInterval() const { return interval; }
  [[nodiscard]] RegistrationStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, BootNotificationResponse& data) {
    data.currentTime = j.at("currentTime").get<RFC3339DateTime>();
    data.interval = j.at("interval").get<int>();
    data.status = j.at("status").get<RegistrationStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};


class CancelReservationResponse {
private:
  CancelReservationStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  CancelReservationResponse() = default;
  explicit CancelReservationResponse(
      CancelReservationStatusEnumType statusParam,
      const std::optional<StatusInfoType>& statusInfoParam = std::nullopt)
      : status(statusParam), statusInfo(statusInfoParam) {}

  [[nodiscard]] CancelReservationStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  friend void from_json(const nlohmann::json& j, CancelReservationResponse& data) {
    data.status = j.at("status").get<CancelReservationStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class CertificateSignedResponse {
private:
  CertificateSignedStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  CertificateSignedResponse() = default;
  explicit CertificateSignedResponse(
      CertificateSignedStatusEnumType statusParam,
      const std::optional<StatusInfoType>& statusInfoParam = std::nullopt)
      : status(statusParam), statusInfo(statusInfoParam) {}

  [[nodiscard]] CertificateSignedStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  friend void from_json(const nlohmann::json& j, CertificateSignedResponse& data) {
    data.status = j.at("status").get<CertificateSignedStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class ChangeAvailabilityResponse {
private:
  ChangeAvailabilityStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  ChangeAvailabilityResponse() = default;
  explicit ChangeAvailabilityResponse(
      ChangeAvailabilityStatusEnumType statusParam,
      const std::optional<StatusInfoType>& statusInfoParam = std::nullopt)
      : status(statusParam), statusInfo(statusInfoParam) {}

  [[nodiscard]] ChangeAvailabilityStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  friend void from_json(const nlohmann::json& j, ChangeAvailabilityResponse& data) {
    data.status = j.at("status").get<ChangeAvailabilityStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};


class ClearChargingProfileResponse {
private:
  ClearChargingProfileStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  ClearChargingProfileResponse() = default;
  explicit ClearChargingProfileResponse(
      ClearChargingProfileStatusEnumType statusParam,
      const std::optional<StatusInfoType>& statusInfoParam = std::nullopt)
      : status(statusParam), statusInfo(statusInfoParam) {}

  [[nodiscard]] ClearChargingProfileStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  friend void from_json(const nlohmann::json& j, ClearChargingProfileResponse& data) {
    data.status = j.at("status").get<ClearChargingProfileStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class ClearDisplayMessageResponse {
private:
  ClearMessageStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  ClearDisplayMessageResponse() = default;
  explicit ClearDisplayMessageResponse(
      ClearMessageStatusEnumType statusParam,
      const std::optional<StatusInfoType>& statusInfoParam = std::nullopt)
      : status(statusParam), statusInfo(statusInfoParam) {}

  [[nodiscard]] ClearMessageStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  friend void from_json(const nlohmann::json& j, ClearDisplayMessageResponse& data) {
    data.status = j.at("status").get<ClearMessageStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};


class ClearVariableMonitoringResponse {
private:
  std::vector<ClearMonitoringResultType> clearMonitoringResult;

public:
  // Getter function
  [[nodiscard]] const std::vector<ClearMonitoringResultType>& getClearMonitoringResult() const {
    return clearMonitoringResult;
  }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, ClearVariableMonitoringResponse& data) {
    data.clearMonitoringResult = j.at("clearMonitoringResult").get<std::vector<ClearMonitoringResultType>>();
  }
};

class CustomerInformationResponse {
private:
  CustomerInformationStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] CustomerInformationStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, CustomerInformationResponse& data) {
    data.status = j.at("status").get<CustomerInformationStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class DataTransferResponse {
private:
  DataTransferStatusEnumType status;
//  std::optional<anyType> data;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] DataTransferStatusEnumType getStatus() const { return status; }
//  [[nodiscard]] std::optional<anyType> getData() const { return data; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, DataTransferResponse& data) {
    data.status = j.at("status").get<DataTransferStatusEnumType>();

    if (j.contains("data")) {
//      data.data = j.at("data").get<anyType>();
    }

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class DeleteCertificateResponse {
private:
  DeleteCertificateStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] DeleteCertificateStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, DeleteCertificateResponse& data) {
    data.status = j.at("status").get<DeleteCertificateStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class Get15118EVCertificateResponse {
private:
  Iso15118EVCertificateStatusEnumType status;
  std::string exiResponse;
  std::optional<StatusInfoType> statusInfo;

public:
  [[nodiscard]] Iso15118EVCertificateStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::string getExiResponse() const { return exiResponse; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  friend void from_json(const nlohmann::json& j, Get15118EVCertificateResponse& data) {
    data.status = j.at("status").get<Iso15118EVCertificateStatusEnumType>();
    data.exiResponse = j.at("exiResponse").get<std::string>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class GetBaseReportResponse {
private:
  GenericDeviceModelStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  [[nodiscard]] GenericDeviceModelStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  friend void from_json(const nlohmann::json& j, GetBaseReportResponse& data) {
    data.status = j.at("status").get<GenericDeviceModelStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class GetCertificateStatusResponse {
private:
  GetCertificateStatusEnumType status;
  std::optional<std::string> ocspResult;
  std::optional<StatusInfoType> statusInfo;

public:
  [[nodiscard]] GetCertificateStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<std::string> getOcspResult() const { return ocspResult; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  friend void from_json(const nlohmann::json& j, GetCertificateStatusResponse& data) {
    data.status = j.at("status").get<GetCertificateStatusEnumType>();

    if (j.contains("ocspResult")) {
      data.ocspResult = j.at("ocspResult").get<std::string>();
    }

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class GetChargingProfilesResponse {
private:
  GetChargingProfileStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] GetChargingProfileStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, GetChargingProfilesResponse& data) {
    data.status = j.at("status").get<GetChargingProfileStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class GetCompositeScheduleResponse {
private:
  GenericStatusEnumType status;
  std::optional<CompositeScheduleType> schedule;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] GenericStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<CompositeScheduleType> getSchedule() const { return schedule; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, GetCompositeScheduleResponse& data) {
    data.status = j.at("status").get<GenericStatusEnumType>();

    if (j.contains("schedule")) {
      data.schedule = j.at("schedule").get<CompositeScheduleType>();
    }

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};
#include "nlohmann/json.hpp"

class GetDisplayMessagesResponse {
private:
  GetDisplayMessagesStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  [[nodiscard]] GetDisplayMessagesStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  friend void from_json(const nlohmann::json& j, GetDisplayMessagesResponse& data) {
    data.status = j.at("status").get<GetDisplayMessagesStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class GetInstalledCertificateIdsResponse {
private:
  GetInstalledCertificateStatusEnumType status;
  std::vector<CertificateHashDataChainType> certificateHashDataChain;
  std::optional<StatusInfoType> statusInfo;

public:
  [[nodiscard]] GetInstalledCertificateStatusEnumType getStatus() const { return status; }
  [[nodiscard]] const std::vector<CertificateHashDataChainType>& getCertificateHashDataChain() const { return certificateHashDataChain; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  friend void from_json(const nlohmann::json& j, GetInstalledCertificateIdsResponse& data) {
    data.status = j.at("status").get<GetInstalledCertificateStatusEnumType>();

    if (j.contains("certificateHashDataChain")) {
      data.certificateHashDataChain = j.at("certificateHashDataChain").get<std::vector<CertificateHashDataChainType>>();
    }

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class GetLocalListVersionResponse {
private:
  int versionNumber;

public:
  [[nodiscard]] int getVersionNumber() const { return versionNumber; }

  friend void from_json(const nlohmann::json& j, GetLocalListVersionResponse& data) {
    data.versionNumber = j.at("versionNumber").get<int>();
  }
};

class GetLogResponse {
private:
  LogStatusEnumType status;
  std::optional<std::string> filename;
  std::optional<StatusInfoType> statusInfo;

public:
  [[nodiscard]] LogStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<std::string> getFilename() const { return filename; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  friend void from_json(const nlohmann::json& j, GetLogResponse& data) {
    data.status = j.at("status").get<LogStatusEnumType>();

    if (j.contains("filename")) {
      data.filename = j.at("filename").get<std::string>();
    }

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class GetMonitoringReportResponse {
private:
  GenericDeviceModelStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] GenericDeviceModelStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, GetMonitoringReportResponse& data) {
    data.status = j.at("status").get<GenericDeviceModelStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class GetReportResponse {
private:
  GenericDeviceModelStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] GenericDeviceModelStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, GetReportResponse& data) {
    data.status = j.at("status").get<GenericDeviceModelStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class GetTransactionStatusResponse {
private:
  bool ongoingIndicator;
  bool messagesInQueue;

public:
  // Getter functions
  [[nodiscard]] bool getOngoingIndicator() const { return ongoingIndicator; }
  [[nodiscard]] bool getMessagesInQueue() const { return messagesInQueue; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, GetTransactionStatusResponse& data) {
    if (j.contains("ongoingIndicator")) {
      data.ongoingIndicator = j.at("ongoingIndicator").get<bool>();
    }

    data.messagesInQueue = j.at("messagesInQueue").get<bool>();
  }
};
class GetVariablesResponse {
private:
  GetVariableResultType getVariableResult;
public:
  // Getter functions
  [[nodiscard]] GetVariableResultType getGetVariableResult() const { return getVariableResult; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, GetVariablesResponse& data) {
    data.getVariableResult = j.at("getVariableResult");
  }
};


class HeartbeatResponse {
private:
  RFC3339DateTime currentTime;

public:
  [[nodiscard]] RFC3339DateTime getCurrentTime() const { return currentTime; }

  friend void from_json(const nlohmann::json& j, HeartbeatResponse& data) {
    data.currentTime = j.at("currentTime").get<RFC3339DateTime>();
  }
};

class InstallCertificateResponse {
private:
  InstallCertificateStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  [[nodiscard]] InstallCertificateStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  friend void from_json(const nlohmann::json& j, InstallCertificateResponse& data) {
    data.status = j.at("status").get<InstallCertificateStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class NotifyEVChargingNeedsResponse {
private:
  NotifyEVChargingNeedsStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  [[nodiscard]] NotifyEVChargingNeedsStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  friend void from_json(const nlohmann::json& j, NotifyEVChargingNeedsResponse& data) {
    data.status = j.at("status").get<NotifyEVChargingNeedsStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo.emplace(j.at("statusInfo").get<StatusInfoType>());
    }
  }
};


class NotifyEVChargingScheduleResponse {
private:
  GenericStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] GenericStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, NotifyEVChargingScheduleResponse& data) {
    data.status = j.at("status").get<GenericStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class PublishFirmwareResponse {
private:
  GenericStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] GenericStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, PublishFirmwareResponse& data) {
    data.status = j.at("status").get<GenericStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class RequestStartTransactionResponse {
private:
  RequestStartStopStatusEnumType status;
  std::optional<std::string> transactionId;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] RequestStartStopStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<std::string> getTransactionId() const { return transactionId; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, RequestStartTransactionResponse& data) {
    data.status = j.at("status").get<RequestStartStopStatusEnumType>();

    if (j.contains("transactionId")) {
      data.transactionId = j.at("transactionId").get<std::string>();
    }

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class RequestStopTransactionResponse {
private:
  RequestStartStopStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] RequestStartStopStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, RequestStopTransactionResponse& data) {
    data.status = j.at("status").get<RequestStartStopStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class ReserveNowResponse {
private:
  ReserveNowStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] ReserveNowStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, ReserveNowResponse& data) {
    data.status = j.at("status").get<ReserveNowStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class ResetResponse {
private:
  ResetStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] ResetStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, ResetResponse& data) {
    data.status = j.at("status").get<ResetStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class SendLocalListResponse {
private:
  SendLocalListStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] SendLocalListStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, SendLocalListResponse& data) {
    data.status = j.at("status").get<SendLocalListStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};


class SetChargingProfileResponse {
private:
  ChargingProfileStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] ChargingProfileStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, SetChargingProfileResponse& data) {
    data.status = j.at("status").get<ChargingProfileStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class SetDisplayMessageResponse {
private:
  DisplayMessageStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] DisplayMessageStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, SetDisplayMessageResponse& data) {
    data.status = j.at("status").get<DisplayMessageStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class SetMonitoringBaseResponse {
private:
  GenericDeviceModelStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] GenericDeviceModelStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, SetMonitoringBaseResponse& data) {
    data.status = j.at("status").get<GenericDeviceModelStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class SetMonitoringLevelResponse {
private:
  GenericStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] GenericStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, SetMonitoringLevelResponse& data) {
    data.status = j.at("status").get<GenericStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class SetNetworkProfileResponse {
private:
  SetNetworkProfileStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] SetNetworkProfileStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, SetNetworkProfileResponse& data) {
    data.status = j.at("status").get<SetNetworkProfileStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class SetVariableMonitoringResponse {
private:
  std::vector<SetMonitoringResultType> setMonitoringResult;

public:
  // Getter function
  [[nodiscard]] const std::vector<SetMonitoringResultType>& getSetMonitoringResult() const {
    return setMonitoringResult;
  }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, SetVariableMonitoringResponse& data) {
    data.setMonitoringResult = j.at("setMonitoringResult").get<std::vector<SetMonitoringResultType>>();
  }
};

class SetVariablesResponse {
private:
  std::vector<SetVariableResultType> setVariableResult;

public:
  // Getter function
  [[nodiscard]] const std::vector<SetVariableResultType>& getSetVariableResult() const {
    return setVariableResult;
  }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, SetVariablesResponse& data) {
    data.setVariableResult = j.at("setVariableResult").get<std::vector<SetVariableResultType>>();
  }
};

class SignCertificateResponse {
private:
  GenericStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] GenericStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, SignCertificateResponse& data) {
    data.status = j.at("status").get<GenericStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class TransactionEventResponse {
private:
  std::optional<double> totalCost;
  std::optional<int> chargingPriority;
  std::optional<IdTokenInfoType> idTokenInfo;
  std::optional<MessageContentType> updatedPersonalMessage;

public:
  // Getter functions
  [[nodiscard]] std::optional<double> getTotalCost() const { return totalCost; }
  [[nodiscard]] std::optional<int> getChargingPriority() const { return chargingPriority; }
  [[nodiscard]] std::optional<IdTokenInfoType> getIdTokenInfo() const { return idTokenInfo; }
  [[nodiscard]] std::optional<MessageContentType> getUpdatedPersonalMessage() const {
    return updatedPersonalMessage;
  }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, TransactionEventResponse& data) {
    if (j.contains("totalCost")) {
      data.totalCost = j.at("totalCost").get<double>();
    }

    if (j.contains("chargingPriority")) {
      data.chargingPriority = j.at("chargingPriority").get<int>();
    }

    if (j.contains("idTokenInfo")) {
      data.idTokenInfo = j.at("idTokenInfo").get<IdTokenInfoType>();
    }

    if (j.contains("updatedPersonalMessage")) {
      data.updatedPersonalMessage = j.at("updatedPersonalMessage").get<MessageContentType>();
    }
  }
};

class TriggerMessageResponse {
private:
  TriggerMessageStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] TriggerMessageStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, TriggerMessageResponse& data) {
    data.status = j.at("status").get<TriggerMessageStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class UnlockConnectorResponse {
private:
  UnlockStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] UnlockStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, UnlockConnectorResponse& data) {
    data.status = j.at("status").get<UnlockStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

class UnpublishFirmwareResponse {
private:
  UnpublishFirmwareStatusEnumType status;

public:
  // Getter function
  [[nodiscard]] UnpublishFirmwareStatusEnumType getStatus() const { return status; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, UnpublishFirmwareResponse& data) {
    data.status = j.at("status").get<UnpublishFirmwareStatusEnumType>();
  }
};

class UpdateFirmwareResponse {
private:
  UpdateFirmwareStatusEnumType status;
  std::optional<StatusInfoType> statusInfo;

public:
  // Getter functions
  [[nodiscard]] UpdateFirmwareStatusEnumType getStatus() const { return status; }
  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const { return statusInfo; }

  // JSON serialization functions
  friend void from_json(const nlohmann::json& j, UpdateFirmwareResponse& data) {
    data.status = j.at("status").get<UpdateFirmwareStatusEnumType>();

    if (j.contains("statusInfo")) {
      data.statusInfo = j.at("statusInfo").get<StatusInfoType>();
    }
  }
};

}
#endif // ECHOOCPP_MESSAGERESPONE_HPP
