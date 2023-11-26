namespace OCPP201 {

enum class APNAuthenticationEnumType {
  CHAP,  // Use CHAP authentication
  NONE,  // Use no authentication
  PAP,   // Use PAP authentication
  AUTO   // Sequentially try CHAP, PAP, NONE.
};
enum class AttributeEnumType {
  Actual,  // The actual value of the variable.
  Target,  // The target value for this variable.
  MinSet,  // The minimal allowed value for this variable
  MaxSet   // The maximum allowed value for this variable
};

enum class AuthorizeCertificateStatusEnumType {
  Accepted,           // Positive response
  SignatureError,     // If the validation of the Security element in the message header failed.
  CertificateExpired, // If the OEMProvisioningCert in the CertificateInstallationReq, the Contract Certificate in the CertificateUpdateReq, or the ContractCertificate in the PaymentDetailsReq is expired.
  CertificateRevoked, // Used when the SECC or CSMS matches the ContractCertificate contained in a CertificateUpdateReq or PaymentDetailsReq with a CRL and the Contract Certificate is marked as revoked, OR when the SECC or CSMS matches the OEM Provisioning Certificate contained in a CertificateInstallationReq with a CRL and the OEM Provisioning Certificate is marked as revoked. The revocation status can alternatively be obtained through an OCSP responder.
  NoCertificateAvailable, // If the new certificate cannot be retrieved from secondary actor within the specified timeout
  CertChainError,   // If the ContractSignatureCertChain contained in the CertificateInstallationReq message is not valid.
  ContractCancelled // If the EMAID provided by EVCC during CertificateUpdateReq is not accepted by secondary actor.
};


enum class AuthorizationStatusEnumType {
  Accepted,         // Identifier is allowed for charging.
  Blocked,          // Identifier has been blocked. Not allowed for charging.
  ConcurrentTx,     // Identifier is already involved in another transaction and multiple transactions are not allowed. (Only relevant for the response to a transactionEventRequest(eventType=Started).)
  Expired,          // Identifier has expired. Not allowed for charging.
  Invalid,          // Identifier is invalid. Not allowed for charging.
  NoCredit,         // Identifier is valid, but EV Driver doesn’t have enough credit to start charging. Not allowed for charging.
  NotAllowedTypeEVS,// Identifier is valid, but not allowed to charge at this type of EVSE.
  NotAtThisLocation,// Identifier is valid, but not allowed to charge at this location.
  NotAtThisTime,    // Identifier is valid, but not allowed to charge at this location at this time.
  Unknown           // Identifier is unknown. Not allowed for charging.
};

enum class BootReasonEnumType {
  ApplicationReset,  // The Charging Station rebooted due to an application error.
  FirmwareUpdate,    // The Charging Station rebooted due to a firmware update.
  LocalReset,        // The Charging Station rebooted due to a local reset command.
  PowerUp,           // The Charging Station powered up and registers itself with the CSMS.
  RemoteReset,       // The Charging Station rebooted due to a remote reset command.
  ScheduledReset,    // The Charging Station rebooted due to a scheduled reset command.
  Triggered,         // Requested by the CSMS via a TriggerMessage
  Unknown,           // The boot reason is unknown.
  Watchdog           // The Charging Station rebooted due to an elapsed watchdog timer.
};

enum class CancelReservationStatusEnumType {
  Accepted,  // Reservation for the identifier has been canceled.
  Rejected   // Reservation could not be canceled, because there is no reservation active for the identifier.
};

enum class CertificateActionEnumType {
  Install,  // Install the provided certificate.
  Update    // Update the provided certificate.
};

enum class CertificateSignedStatusEnumType {
  Accepted,  // Signed certificate is valid.
  Rejected   // Signed certificate is invalid.
};

enum class CertificateSigningUseEnumType {
  ChargingStationCertificate,  // Client side certificate used by the Charging Station to connect the the CSMS.
  V2GCertificate              // Use for certificate for 15118 connections. This means that the certificate should be derived from the V2G root.
};

enum class ChangeAvailabilityStatusEnumType {
  Accepted,  // Request has been accepted and will be executed.
  Rejected,  // Request has not been accepted and will not be executed.
  Scheduled  // Request has been accepted and will be executed when transaction(s) in progress have finished.
};

enum class ChargingLimitSourceEnumType {
  EMS,   // Indicates that an Energy Management System has sent a charging limit.
  Other, // Indicates that an external source, not being an EMS or system operator, has sent a charging limit.
  SO,    // Indicates that a System Operator (DSO or TSO) has sent a charging limit.
  CSO    // Indicates that the CSO has set this charging profile.
};

enum class ChargingProfileKindEnumType {
  Absolute,  // Schedule periods are relative to a fixed point in time defined in the schedule. This requires that startSchedule is set to a starting point in time.
  Recurring, // The schedule restarts periodically at the first schedule period. To be most useful, this requires that startSchedule is set to a starting point in time.
  Relative   // Charging schedule periods should start when the EVSE is ready to deliver energy. i.e. when the EV driver is authorized and the EV is connected. When a ChargingProfile is received for a transaction that is already charging, then the charging schedule periods should remain relative to the PowerPathClosed moment. No value for startSchedule should be supplied.
};

enum class ChargingProfilePurposeEnumType {
  ChargingStationExternalConstraints,
  ChargingStationMaxProfile,
  TxDefaultProfile,
  TxProfile
};

enum class ChargingProfileStatusEnumType {
  Accepted,
  Rejected
};


enum class ChargingRateUnitEnumType {
  W,
  A
};


enum ChargingStateEnumType {
  Charging,
  EVConnected,
  SuspendedEV,
  SuspendedEVSE,
  Idle
};
enum class ClearCacheStatusEnumType {
  Accepted,
  Rejected
};

enum class ClearChargingProfileStatusEnumType {
  Accepted,
  Unknown
};

enum class ClearMessageStatusEnumType {
  Accepted,
  Unknown
};

enum class ClearMonitoringStatusEnumType {
  Accepted,
  Rejected,
  NotFound
};

enum class ComponentCriterionEnumType {
  Active,
  Available,
  Enabled,
  Problem
};

enum class ConnectorEnumType {
  cCCS1,
  cCCS2,
  cG105,
  cTesla,
  cType1,
  cType2,
  s309_1P_16A,
  s309_1P_32A,
  s309_3P_16A,
  s309_3P_32A,
  sBS1361,
  sCEE_7_7,
  sType2,
  sType3,
  Other1PhMax16A,
  Other1PhOver16A,
  Other3Ph,
  Pan,
  wInductive,
  wResonant,
  Undetermined,
  Unknown
};

enum class ConnectorStatusEnumType {
  Available,
  Occupied,
  Reserved,
  Unavailable,
  Faulted
};

enum class CostKindEnumType {
  CarbonDioxideEmission,
  RelativePricePercentage,
  RenewableGenerationPercentage
};


enum class CustomerInformationStatusEnumType {
  Accepted,
  Rejected,
  Invalid
};

enum class DataEnumType {
  StringType,
  DecimalType,
  IntegerType,
  DateTimeType,
  BooleanType,
  OptionListType,
  SequenceListType,
  MemberListType
};

enum DataTransferStatusEnumType {
  Accepted,
  Rejected,
  UnknownMessageId,
  UnknownVendorId
};

enum class DeleteCertificateStatusEnumType {
  Accepted,
  Failed,
  NotFound
};


enum class DisplayMessageStatusEnumType {
  Accepted,
  NotSupportedMessageFormat,
  Rejected,
  NotSupportedPriority,
  NotSupportedState,
  UnknownTransaction
};

enum class EnergyTransferModeEnumType {
  DC,
  AC_single_phase,
  AC_two_phase,
  AC_three_phase
};

enum class EventNotificationEnumType {
  HardWiredNotification,
  HardWiredMonitor,
  PreconfiguredMonitor,
  CustomMonitor
};


enum class EventTriggerEnumType {
  Alerting,
  Delta,
  Periodic
};


enum class FirmwareStatusEnumType {
  Downloaded, DownloadFailed, Downloading, DownloadScheduled, DownloadPaused, Idle, InstallationFailed, Installing, Installed, InstallRebooting, InstallScheduled, InstallVerificationFailed, InvalidSignature, SignatureVerified
};


enum class GenericDeviceModelStatusEnumType {
  Accepted,
  Rejected,
  NotSupported,
  EmptyResultSet
};

enum class GenericStatusEnumType {
  Accepted,
  Rejected
};

enum class GetCertificateIdUseEnumType {
  V2GRootCertificate,
  MORootCertificate,
  CSMSRootCertificate,
  V2GCertificateChain,
  ManufacturerRootCertificate
};

enum class GetCertificateStatusEnumType {
  Accepted,
  Failed
};

enum class GetChargingProfileStatusEnumType {
  Accepted,
  NoProfiles
};

enum class GetDisplayMessagesStatusEnumType {
  Accepted,
  Unknown
};

enum class GetInstalledCertificateStatusEnumType {
  Accepted,
  NotFound
};

enum class GetVariableStatusEnumType {
  Accepted,
  Rejected,
  UnknownComponent,
  UnknownVariable,
  NotSupportedAttributeType
};

enum class HashAlgorithmEnumType {
  SHA256,
  SHA384,
  SHA512
};

enum class IdTokenEnumType {
  Central,
  eMAID,
  ISO14443,
  ISO15693,
  KeyCode,
  Local,
  MacAddress,
  NoAuthorization
};

// 3.44. InstallCertificateStatusEnumType
enum class InstallCertificateStatusEnumType {
  Accepted,
  Rejected,
  Failed
};

// 3.45. InstallCertificateUseEnumType
enum class InstallCertificateUseEnumType {
  V2GRootCertificate,
  MORootCertificate,
  CSMSRootCertificate,
  ManufacturerRootCertificate
};

// 3.46. Iso15118EVCertificateStatusEnumType
enum class Iso15118EVCertificateStatusEnumType {
  Accepted,
  Failed
};

// 3.47. LocationEnumType
enum class LocationEnumType {
  Body,
  Cable,
  EV,
  Inlet,
  Outlet
};

// 3.48. LogEnumType
enum class LogEnumType {
  DiagnosticsLog,
  SecurityLog
};

// 3.49. LogStatusEnumType
enum class LogStatusEnumType {
  Accepted,
  Rejected,
  AcceptedCanceled
};

// 3.50. MeasurandEnumType
enum class MeasurandEnumType {
  CurrentExport,
  CurrentImport,
  CurrentOffered,
  EnergyActiveExportRegister,
  EnergyActiveImportRegister,
  EnergyReactiveExportRegister,
  EnergyReactiveImportRegister,
  EnergyActiveExportInterval,
  EnergyActiveImportInterval,
  EnergyReactiveExportInterval,
  EnergyReactiveImportInterval,
  EnergyReactiveNet,
  EnergyApparentNet,
  EnergyApparentImport,
  EnergyApparentExport,
  Frequency,
  PowerActiveExport,
  PowerActiveImport,
  PowerFactor,
  PowerOffered,
  PowerReactiveExport,
  PowerReactiveImport,
  SoC,
  Voltage
};

// 3.51. MessageFormatEnumType
enum class MessageFormatEnumType {
  ASCII,
  HTML,
  URI,
  UTF8
};

// 3.52. MessagePriorityEnumType
enum class MessagePriorityEnumType {
  AlwaysFront,
  InFront,
  NormalCycle
};

// 3.53. MessageStateEnumType
enum class MessageStateEnumType {
  Charging,
  Faulted,
  Idle,
  Unavailable
};

// 3.54. MessageTriggerEnumType
enum class MessageTriggerEnumType {
  BootNotification,
  LogStatusNotification,
  FirmwareStatusNotification,
  Heartbeat,
  MeterValues,
  SignChargingStationCertificate,
  SignV2GCertificate,
  StatusNotification,
  TransactionEvent,
  SignCombinedCertificate,
  PublishFirmwareStatusNotification
};

// 3.55. MonitorEnumType
enum class MonitorEnumType {
  UpperThreshold,
  LowerThreshold,
  Delta,
  Periodic,
  PeriodicClockAligned
};

// 3.56. MonitoringBaseEnumType
enum class MonitoringBaseEnumType {
  All,
  FactoryDefault,
  HardWiredOnly
};

// 3.57. MonitoringCriterionEnumType
enum class MonitoringCriterionEnumType {
  ThresholdMonitoring,
  DeltaMonitoring,
  PeriodicMonitoring
};

// 3.58. MutabilityEnumType
enum class MutabilityEnumType {
  ReadOnly,
  WriteOnly,
  ReadWrite
};

// 3.59. NotifyEVChargingNeedsStatusEnumType
enum class NotifyEVChargingNeedsStatusEnumType {
  Accepted,
  Rejected,
  Processing
};

// 3.60. OCPPInterfaceEnumType
enum class OCPPInterfaceEnumType {
  Wired0,
  Wired1,
  Wired2,
  Wired3,
  Wireless0,
  Wireless1,
  Wireless2,
  Wireless3
};

// 3.61. OCPPTransportEnumType
enum class OCPPTransportEnumType {
  JSON,
  SOAP
};

// 3.62. OCPPVersionEnumType
enum class OCPPVersionEnumType {
  OCPP12,
  OCPP15,
  OCPP16,
  OCPP20
};

// 3.63. OperationalStatusEnumType
enum class OperationalStatusEnumType {
  Inoperative,
  Operative
};

// 3.64. PhaseEnumType
enum class PhaseEnumType {
  L1,
  L2,
  L3,
  N,
  L1N,
  L2N,
  L3N,
  L1L2,
  L2L3,
  L3L1
};

// 3.65. PublishFirmwareStatusEnumType
enum class PublishFirmwareStatusEnumType {
  Idle,
  DownloadScheduled,
  Downloading,
  Downloaded,
  Published,
  DownloadFailed,
  DownloadPaused,
  InvalidChecksum,
  ChecksumVerified,
  PublishFailed
};

// 3.66. ReadingContextEnumType
enum class ReadingContextEnumType {
  InterruptionBegin,
  InterruptionEnd,
  Other,
  SampleClock,
  SamplePeriodic,
  TransactionBegin,
  TransactionEnd,
  Trigger
};

// 3.67. ReasonEnumType
enum class ReasonEnumType {
  DeAuthorized,
  EmergencyStop,
  EnergyLimitReached,
  EVDisconnected,
  GroundFault,
  ImmediateReset,
  Local,
  LocalOutOfCredit,
  MasterPass,
  Other,
  OvercurrentFault,
  PowerLoss,
  PowerQuality,
  Reboot,
  Remote,
  SOCLimitReached
};

// 3.68. RecurrencyKindEnumType
enum class RecurrencyKindEnumType {
  Daily,
  Weekly
};

// 3.69. RegistrationStatusEnumType
enum class RegistrationStatusEnumType {
  Accepted,
  Pending,
  Rejected
};
// 3.70. ReportBaseEnumType
enum class ReportBaseEnumType {
  ConfigurationInventory,
  FullInventory,
  SummaryInventory
};

// 3.71. RequestStartStopStatusEnumType
enum class RequestStartStopStatusEnumType {
  Accepted,
  Rejected
};

// 3.72. ReservationUpdateStatusEnumType
enum class ReservationUpdateStatusEnumType {
  Expired,
  Removed
};

// 3.73. ReserveNowStatusEnumType
enum class ReserveNowStatusEnumType {
  Accepted,
  Faulted,
  Occupied,
  Rejected,
  Unavailable
};

// 3.74. ResetEnumType
enum class ResetEnumType {
  Immediate,
  OnIdle
};

// 3.75. ResetStatusEnumType
enum class ResetStatusEnumType {
  Accepted,
  Rejected,
  Scheduled
};

// 3.76. SendLocalListStatusEnumType
enum class SendLocalListStatusEnumType {
  Accepted,
  Failed,
  VersionMismatch
};

// 3.77. SetMonitoringStatusEnumType
enum class SetMonitoringStatusEnumType {
  Accepted,
  UnknownComponent,
  UnknownVariable,
  UnsupportedMonitorType,
  Rejected,
  Duplicate
};

// 3.78. SetNetworkProfileStatusEnumType
enum class SetNetworkProfileStatusEnumType {
  Accepted,
  Rejected,
  Failed
};

// 3.79. SetVariableStatusEnumType
enum class SetVariableStatusEnumType {
  Accepted,
  Rejected,
  UnknownComponent,
  UnknownVariable,
  NotSupportedAttributeType,
  RebootRequired
};

// 3.80. TransactionEventEnumType
enum class TransactionEventEnumType {
  Ended,
  Started,
  Updated
};

// 3.81. TriggerMessageStatusEnumType
enum class TriggerMessageStatusEnumType {
  Accepted,
  Rejected,
  NotImplemented
};

// 3.82. TriggerReasonEnumType
enum class TriggerReasonEnumType {
  Authorized,
  CablePluggedIn,
  ChargingRateChanged,
  ChargingStateChanged,
  Deauthorized,
  EnergyLimitReached,
  EVCommunicationLost,
  EVConnectTimeout,
  MeterValueClock,
  MeterValuePeriodic,
  TimeLimitReached,
  Trigger,
  UnlockCommand,
  StopAuthorized,
  EVDeparted,
  EVDetected,
  RemoteStop,
  RemoteStart,
  AbnormalCondition,
  SignedDataReceived,
  ResetCommand
};

// 3.83. UnlockStatusEnumType
enum class UnlockStatusEnumType {
  Unlocked,
  UnlockFailed,
  OngoingAuthorizedTransaction,
  UnknownConnector
};

// 3.84. UnpublishFirmwareStatusEnumType
enum class UnpublishFirmwareStatusEnumType {
  DownloadOngoing,
  NoFirmware,
  Unpublished
};

// 3.85. UpdateEnumType
enum class UpdateEnumType {
  Differential,
  Full
};

// 3.86. UpdateFirmwareStatusEnumType
enum class UpdateFirmwareStatusEnumType {
  Accepted,
  Rejected,
  AcceptedCanceled,
  InvalidCertificate,
  RevokedCertificate
};

// 3.87. UploadLogStatusEnumType
enum class UploadLogStatusEnumType {
  BadMessage,
  Idle,
  NotSupportedOperation,
  PermissionDenied,
  Uploaded,
  UploadFailure,
  Uploading,
  AcceptedCanceled
};

// 3.88. VPNEnumType
enum class VPNEnumType {
  IKEv2,
  IPSec,
  L2TP,
  PPTP
};


}
