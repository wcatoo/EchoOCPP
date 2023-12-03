//
// Created by 杨帆 on 2023/11/20.
//

#ifndef ECHOOCPP_DATATYPES_HPP
#define ECHOOCPP_DATATYPES_HPP

#include <iostream>

#include <magic_enum.hpp>
#include <sstream>

#include "Enumerations.hpp"
#include "PrimitiveDatatypes.hpp"


namespace OCPP201 {




/**
 * @class ACChargingParametersType
 * @brief Class representing AC charging parameters for an electric vehicle
 *
 * This class represents the AC charging parameters for an electric vehicle, including the amount of energy requested,
 * the minimum and maximum current supported by the vehicle, and the maximum voltage supported.
 */
class ACChargingParametersType {

private:
  // Required. Amount of energy requested (in Wh). This includes energy required for preconditioning.
  int energyAmount;
  // Required. Minimum current (amps) supported by the electric vehicle (per phase).
  int evMinCurrent;
  // Required. Maximum current (amps) supported by the electric vehicle (per phase). Includes cable capacity.
  int evMaxCurrent;
  // Required. Maximum voltage supported by the electric vehicle
  int evMaxVoltage;
public:
  ACChargingParametersType() = default;

  // Parameterized constructor
  ACChargingParametersType(int energyAmountParam,
                           int evMinCurrentParam,
                           int evMaxCurrentParam,
                           int evMaxVoltageParam)
      : energyAmount(energyAmountParam),
        evMinCurrent(evMinCurrentParam),
        evMaxCurrent(evMaxCurrentParam),
        evMaxVoltage(evMaxVoltageParam) {}

  // Getter and setter methods for `energyAmount`
  [[nodiscard]] int getEnergyAmount() const {
    return energyAmount;
  }

  void setEnergyAmount(int newEnergyAmount) {
    energyAmount = newEnergyAmount;
  }

  // Getter and setter methods for `evMinCurrent`
  [[nodiscard]] int getEvMinCurrent() const {
    return evMinCurrent;
  }

  void setEvMinCurrent(int newEvMinCurrent) {
    evMinCurrent = newEvMinCurrent;
  }

  // Getter and setter methods for `evMaxCurrent`
  [[nodiscard]] int getEvMaxCurrent() const {
    return evMaxCurrent;
  }

  void setEvMaxCurrent(int newEvMaxCurrent) {
    evMaxCurrent = newEvMaxCurrent;
  }

  // Getter and setter methods for `evMaxVoltage`
  [[nodiscard]] int getEvMaxVoltage() const {
    return evMaxVoltage;
  }

  void setEvMaxVoltage(int newEvMaxVoltage) {
    evMaxVoltage = newEvMaxVoltage;
  }
  friend void from_json(const nlohmann::json &json, ACChargingParametersType& tData) {
    if (json.contains("energyAmount")) {
      json.at("energyAmount").get_to(tData.energyAmount);
    }
    if (json.contains("evMinCurrent")) {
      json.at("evMinCurrent").get_to(tData.evMinCurrent);
    }
    if (json.contains("evMaxCurrent")) {
      json.at("evMaxCurrent").get_to(tData.evMaxCurrent);
    }
    if (json.contains("evMaxVoltage")) {
      json.at("evMaxVoltage").get_to(tData.evMaxVoltage);
    }
  }

  friend void to_json(nlohmann::json& json, const ACChargingParametersType &type) {
    json = nlohmann::json{
        {"energyAmount", type.energyAmount},
        {"evMinCurrent", type.evMinCurrent},
        {"evMaxCurrent", type.evMaxCurrent},
        {"evMaxVoltage", type.evMaxVoltage}};
  }
};

/**
 * @class AdditionalInfoType
 * @brief Represents additional information for a specific type.
 *
 * This class stores additional information for a specific type. It includes
 * the additional ID token and the type itself. The type is a custom type and
 * the implementation details need to be agreed upon by all involved parties.
 */
class AdditionalInfoType {
private:
  // Required. This field specifies the additional IdToken.
  std::string additionalIdToken;
  // Required. This defines the type of the additionalIdToken.
  // This is a custom type, so the implementation needs to be
  // agreed upon by all involved parties.
  std::string type;
public:

  AdditionalInfoType() = default;
  AdditionalInfoType(const std::string& additionalIdToken, const std::string& type)
      : additionalIdToken(additionalIdToken), type(type) {}

  [[nodiscard]]std::string getAdditionalIdToken() const {
    return additionalIdToken;
  }

  void setAdditionalIdToken(const std::string& newAdditionalIdToken) {
    additionalIdToken = newAdditionalIdToken;
  }

  // Getter and setter methods for `type`
  [[nodiscard]]std::string getType() const {
    return type;
  }

  void setType(const std::string& newType) {
    type = newType;
  }

  // Function to convert AdditionalInfoType object to JSON
  friend void to_json(nlohmann::json &tJson, const AdditionalInfoType &tData) {
    tJson = nlohmann::json { {"additionalIdToken", tData.additionalIdToken}, {"type", tData.type} };
  }

  friend void from_json(const nlohmann::json &tJson, AdditionalInfoType &tData) {
    if (tJson.contains("additionalIdToken")) {
      tData.additionalIdToken = tJson.at("additionalIdToken").get<std::string>();
    }

    if (tJson.contains("type")) {
      tData.type = tJson.at("type").get<std::string>();
    }
  }

};


/**
 * @class APNType
 * @brief Represents an Access Point Name (APN) configuration.
 *
 * The APNType class provides a representation of an APN configuration,
 * including fields such as APN name, username, password, SIM PIN, preferred network,
 * and APN authentication type. It also includes functions to convert the APNType object
 * to and from a JSON object.
 */
class APNType {
private:
  std::string apn;
  std::optional<std::string> apnUserName;
  std::optional<std::string> apnPassword;
  std::optional<int> simPin;
  std::optional<std::string> preferredNetwork;
  std::optional<bool> useOnlyPreferredNetwork;

public:

  APNType() = default;

  // Parameterized Constructor
  APNType(std::string  apnParam,
          const std::optional<std::string>& apnUserNameParam = std::nullopt,
          const std::optional<std::string>& apnPasswordParam = std::nullopt,
          const std::optional<int>& simPinParam = std::nullopt,
          const std::optional<std::string>& preferredNetworkParam = std::nullopt,
          const std::optional<bool>& useOnlyPreferredNetworkParam = std::nullopt)
      : apn(std::move(apnParam)),
        apnUserName(apnUserNameParam),
        apnPassword(apnPasswordParam),
        simPin(simPinParam),
        preferredNetwork(preferredNetworkParam),
        useOnlyPreferredNetwork(useOnlyPreferredNetworkParam) {}
  [[nodiscard]]std::string getApn() const {
    return apn;
  }

  void setApn(const std::string& newApn) {
    apn = newApn;
  }

  // Getter and setter methods for `apnUserName`
  [[nodiscard]] std::optional<std::string> getApnUserName() const {
    return apnUserName;
  }

  void setApnUserName(const std::string& newApnUserName) {
    apnUserName = newApnUserName;
  }

  // Getter and setter methods for `apnPassword`
  [[nodiscard]] std::optional<std::string> getApnPassword() const {
    return apnPassword;
  }

  void setApnPassword(const std::string& newApnPassword) {
    apnPassword = newApnPassword;
  }

  // Getter and setter methods for `simPin`
  [[nodiscard]] std::optional<int> getSimPin() const {
    return simPin;
  }

  void setSimPin(int newSimPin) {
    simPin = newSimPin;
  }

  // Getter and setter methods for `preferredNetwork`
  [[nodiscard]] std::optional<std::string> getPreferredNetwork() const {
    return preferredNetwork;
  }

  void setPreferredNetwork(const std::string& newPreferredNetwork) {
    preferredNetwork = newPreferredNetwork;
  }

  // Getter and setter methods for `useOnlyPreferredNetwork`
  [[nodiscard]] std::optional<bool> getUseOnlyPreferredNetwork() const {
    return useOnlyPreferredNetwork;
  }

  void setUseOnlyPreferredNetwork(bool newUseOnlyPreferredNetwork) {
    useOnlyPreferredNetwork = newUseOnlyPreferredNetwork;
  }

  // Getter and setter methods for `apnAuthentication`
  [[nodiscard]] APNAuthenticationEnumType getApnAuthentication() const {
    return apnAuthentication;
  }

  void setApnAuthentication(const APNAuthenticationEnumType& newApnAuthentication) {
    apnAuthentication = newApnAuthentication;
  }
  friend void to_json(nlohmann::json &tJson, const APNType &tData) {
    tJson.emplace("apn", tData.apn);
    if (tData.apnUserName.has_value()) {
      tJson.emplace("apnUserName", tData.apnUserName.value_or(""));
    }
    if (tData.apnPassword.has_value()) {
      tJson.emplace("apnPassword", tData.apnPassword.value_or(""));
    }
    if (tData.simPin.has_value()) {
      tJson.emplace("simPin", tData.simPin.value_or(0));
    }
    if (tData.preferredNetwork.has_value()) {
      tJson.emplace("preferredNetwork", tData.preferredNetwork.value_or(""));
    }
    if (tData.useOnlyPreferredNetwork.has_value()) {
      tJson.emplace("useOnlyPreferredNetwork", tData.useOnlyPreferredNetwork.value_or(false));
    }
    tJson.emplace("apnAuthentication", magic_enum::enum_name(tData.apnAuthentication));

  }

  friend void from_json(const nlohmann::json &tJson, APNType &tData) {
    tJson.at("apn").get_to(tData.apn);
    if (tJson.contains("apnUserName")) {
      tJson.at("apnUserName").get_to(tData.apnUserName.emplace());
    } else {
      tData.apnUserName.reset(); // Optional value not present in JSON
    }

    if (tJson.contains("apnPassword")) {
      tJson.at("apnPassword").get_to(tData.apnPassword.emplace());
    } else {
      tData.apnPassword.reset();
    }

    if (tJson.contains("simPin")) {
      tJson.at("simPin").get_to(tData.simPin.emplace());
    } else {
      tData.simPin.reset();
    }

    if (tJson.contains("preferredNetwork")) {
      tJson.at("preferredNetwork").get_to(tData.preferredNetwork.emplace());
    } else {
      tData.preferredNetwork.reset();
    }

    if (tJson.contains("useOnlyPreferredNetwork")) {
      tJson.at("useOnlyPreferredNetwork").get_to(tData.useOnlyPreferredNetwork.emplace());
    } else {
      tData.useOnlyPreferredNetwork.reset();
    }

    auto authTypeStr = tJson.at("apnAuthentication").get<std::string>();
    auto authTypeEnum =
        magic_enum::enum_cast<APNAuthenticationEnumType>(authTypeStr);

    if (authTypeEnum.has_value()) {
      tData.apnAuthentication = authTypeEnum.value();
    } else {
      tData.apnAuthentication = APNAuthenticationEnumType::NONE;
    }
  }
  APNAuthenticationEnumType apnAuthentication;
};

class IdTokenType {
private:
  std::string idToken;
  IdTokenEnumType type;
  std::vector<AdditionalInfoType> additionalInfo; // Optional

public:

  // Default Constructor
  IdTokenType() = default;

  // Parameterized Constructor
  IdTokenType(const std::string&  idTokenParam, const IdTokenEnumType& typeParam, const std::vector<AdditionalInfoType>& additionalInfoParam = {})
      : idToken(idTokenParam), type(typeParam), additionalInfo(additionalInfoParam) {}

  [[nodiscard]] std::string getIdToken() const {
    return idToken;
  }

  void setIdToken(const std::string& newIdToken) {
    idToken = newIdToken;
  }

  [[nodiscard]] IdTokenEnumType getType() const {
    return type;
  }

  void setType(const IdTokenEnumType& newType) {
    type = newType;
  }

  [[nodiscard]] std::vector<AdditionalInfoType> getAdditionalInfo() const {
    return additionalInfo;
  }

  void setAdditionalInfo(const std::vector<AdditionalInfoType>& newAdditionalInfo) {
    additionalInfo = newAdditionalInfo;
  }


  friend void to_json(nlohmann::json &tJson, const IdTokenType &tData) {
    tJson.emplace("idToken", tData.idToken);
    tJson.emplace("additionalInfo", tData.additionalInfo);
    tJson.emplace("type", magic_enum::enum_name(tData.type));
  }

  friend void from_json(const nlohmann::json &j, IdTokenType &tData) {
    tData.idToken = j.at("idToken").get<std::string>();
    auto tmp = magic_enum::enum_cast<IdTokenEnumType>(j.at("type").get<std::string>() );
    if (tmp.has_value()) {
      tData.type = tmp.value();
    }
    tData.additionalInfo.clear();
    for (const auto& element : j.at("additionalInfo")) {
      AdditionalInfoType info;
      from_json(element, info);
      tData.additionalInfo.push_back(info);
    }
  }
};


class MessageContentType {
private:
  MessageFormatEnumType format;
  std::string language;
  std::string content;

public:

  MessageContentType() = default;

  // Parameterized constructor
  MessageContentType(const MessageFormatEnumType& formatParam, std::string  languageParam, const std::string& contentParam)
      : format(formatParam), language(std::move(languageParam)), content(contentParam)
  {
  }


  [[nodiscard]]MessageFormatEnumType getFormat() const {
    return format;
  }

  void setFormat(const MessageFormatEnumType& newFormat) {
    format = newFormat;
  }

  [[nodiscard]]std::string getLanguage() const {
    return language;
  }

  void setLanguage(const std::string& newLanguage) {
    language = newLanguage;
  }

  [[nodiscard]]std::string getContent() const {
    return content;
  }

  void setContent(const std::string& newContent) {
    content = newContent;
  }

  friend void to_json(nlohmann::json &j, const MessageContentType &messageContent) {
    j.emplace("format", magic_enum::enum_name(messageContent.format));
    j.emplace("language", messageContent.language);
    j.emplace("content", messageContent.content);
  }

  friend void from_json(const nlohmann::json &j, MessageContentType &messageContent) {
    auto tmp = magic_enum::enum_cast<MessageFormatEnumType>(j.at("format").get<std::string>());
    if (tmp.has_value()) {
      messageContent.format = tmp.value();
    }
    messageContent.language = j.at("language").get<std::string>();
    messageContent.content = j.at("content").get<std::string>();
  }
};


class IdTokenInfoType {
private:
  AuthorizationStatusEnumType status;
  std::optional<std::string> cacheExpiryDateTime;
  std::optional<int> chargingPriority;
  std::optional<std::string> language1;
  std::optional<std::vector<int>> evseId;
  std::optional<std::string> language2;
  std::optional<IdTokenType> groupIdToken;
  std::optional<MessageContentType> personalMessage;

public:
  IdTokenInfoType() = default;
  explicit IdTokenInfoType(const AuthorizationStatusEnumType& statusParam,
                           const std::optional<std::string>& cacheExpiryDateTimeParam = std::nullopt,
                           const std::optional<int>& chargingPriorityParam = std::nullopt,
                           const std::optional<std::string>& language1Param = std::nullopt,
                           const std::optional<std::vector<int>>& evseIdParam = std::nullopt,
                           const std::optional<std::string>& language2Param = std::nullopt,
                           const std::optional<IdTokenType>& groupIdTokenParam = std::nullopt,
                           const std::optional<MessageContentType>& personalMessageParam = std::nullopt)
      : status(statusParam),
        cacheExpiryDateTime(cacheExpiryDateTimeParam),
        chargingPriority(chargingPriorityParam),
        language1(language1Param),
        evseId(evseIdParam),
        language2(language2Param),
        groupIdToken(groupIdTokenParam),
        personalMessage(personalMessageParam)
  {
  }

  [[nodiscard]] AuthorizationStatusEnumType getStatus() const {
    return status;
  }

  void setStatus(const AuthorizationStatusEnumType& newStatus) {
    status = newStatus;
  }

  [[nodiscard]] std::optional<std::string> getCacheExpiryDateTime() const {
    return cacheExpiryDateTime;
  }

  void setCacheExpiryDateTime(const std::string& newDateTime) {
    cacheExpiryDateTime = newDateTime;
  }

  [[nodiscard]] std::optional<int> getChargingPriority() const {
    return chargingPriority;
  }

  void setChargingPriority(int newPriority) {
    chargingPriority = newPriority;
  }

  [[nodiscard]] std::optional<std::string> getLanguage1() const {
    return language1;
  }

  void setLanguage1(const std::string& newLanguage) {
    language1 = newLanguage;
  }

  [[nodiscard]] std::optional<std::vector<int>> getEvseId() const {
    return evseId;
  }

  void setEvseId(const std::vector<int>& newEvseId) {
    evseId = newEvseId;
  }

  [[nodiscard]] std::optional<std::string> getLanguage2() const {
    return language2;
  }

  void setLanguage2(const std::string& newLanguage) {
    language2 = newLanguage;
  }

  [[nodiscard]] std::optional<IdTokenType> getGroupIdToken() const {
    return groupIdToken;
  }

  void setGroupIdToken(const IdTokenType& newGroupIdToken) {
    groupIdToken = newGroupIdToken;
  }

  [[nodiscard]] std::optional<MessageContentType> getPersonalMessage() const {
    return personalMessage;
  }

  void setPersonalMessage(const MessageContentType& newMessage) {
    personalMessage = newMessage;
  }
  friend void to_json(nlohmann::json &tJson, const IdTokenInfoType &tData) {
    tJson.emplace("status", magic_enum::enum_name(tData.status));
    if (tData.cacheExpiryDateTime.has_value()) {
      tJson.emplace("cacheExpiryDateTime", tData.cacheExpiryDateTime.value_or(""));
    }
    if (tData.chargingPriority.has_value()) {
      tJson.emplace("chargingPriority", tData.chargingPriority.value_or(0));
    }
    if (tData.language1.has_value()) {
      tJson.emplace("language1", tData.language1.value_or(""));
    }
    if (tData.evseId.has_value()) {
      tJson.emplace("evseId", tData.evseId.value());
    }
    if (tData.language2.has_value()) {
      tJson.emplace("language2", tData.language2.value_or(""));
    }
    if (tData.groupIdToken.has_value()) {
      tJson.emplace("groupIdToken", nlohmann::json(tData.groupIdToken.value()));
    }
    if (tData.personalMessage.has_value()) {
      tJson.emplace("personalMessage", nlohmann::json(tData.personalMessage.value()));
    }
  }

  friend void from_json(const nlohmann::json &tJson, IdTokenInfoType &tData) {
    auto tmp = magic_enum::enum_cast<AuthorizationStatusEnumType>(tJson.at("status").get<std::string>());
    if (tmp.has_value()) {
      tData.status = tmp.value();
    }

    if (tJson.contains("cacheExpiryDateTime")) {
      tJson.at("cacheExpiryDateTime").get_to(tData.cacheExpiryDateTime.emplace());
    } else {
      tData.cacheExpiryDateTime.reset();
    }

    if (tJson.contains("chargingPriority")) {
      tJson.at("chargingPriority").get_to(tData.chargingPriority.emplace());
    } else {
      tData.chargingPriority.reset();
    }

    if (tJson.contains("language1")) {
      tJson.at("language1").get_to(tData.language1.emplace());
    } else {
      tData.language1.reset();
    }

    if (tJson.contains("evseId") && tJson["evseId"].is_array()) {
      std::vector<int> idVector;
      for (auto& id : tJson["evseId"]) {
        if (id.is_number_integer())
          idVector.push_back(id.get<int>());
      }
      tData.evseId = std::move(idVector);
    }

    if (tJson.contains("language2")) {
      tJson.at("language2").get_to(tData.language2.emplace());
    } else {
      tData.language2.reset();
    }

    if (tJson.contains("groupIdToken")) {
      tData.groupIdToken = tJson.at("groupIdToken").get<IdTokenType>();
    } else {
      tData.groupIdToken.reset();
    }

    if (tJson.contains("personalMessage")) {
      tData.personalMessage = tJson.at("personalMessage").get<MessageContentType>();
    } else {
      tData.personalMessage.reset();
    }
  }
};



class AuthorizationData {
private:
  std::optional<IdTokenInfoType> idTokenInfo;
  IdTokenType idToken;
public:
  AuthorizationData() = default;

  // Parameterized constructor
  explicit AuthorizationData(IdTokenType  idTokenParam, const std::optional<IdTokenInfoType>& idTokenInfoParam = std::nullopt)
      : idToken(std::move(idTokenParam)), idTokenInfo(idTokenInfoParam) { }
  // Getter for idTokenInfo
  [[nodiscard]]std::optional<IdTokenInfoType> getIdTokenInfo() const {
    return idTokenInfo;
  }

  // Setter for idTokenInfo
  void setIdTokenInfo(const IdTokenInfoType& newIdTokenInfo) {
    idTokenInfo = newIdTokenInfo;
  }

  // Getter for idToken
  [[nodiscard]]IdTokenType getIdToken() const {
    return idToken;
  }

  // Setter for idToken
  void setIdToken(const IdTokenType& newIdToken) {
    idToken = newIdToken;
  }


  friend void to_json(nlohmann::json &tJson, const AuthorizationData &authData) {
    tJson.emplace("idToken", authData.idToken);
    if (authData.idTokenInfo.has_value()) {
      tJson.emplace("idTokenInfo", nlohmann::json(authData.idTokenInfo.value()));
    }
  }

  friend void from_json(const nlohmann::json &tJson, AuthorizationData &authData) {
    if (tJson.contains("idTokenInfo")) {
      tJson.at("idTokenInfo").get_to(authData.idTokenInfo.emplace());
    }
    if (tJson.contains("idToken")) {
      tJson.at("idToken").get_to(authData.idToken);
    }
  }
};


class CertificateHashDataType {
private:
  HashAlgorithmEnumType hashAlgorithm;
  std::string issuerNameHash;
  std::string issuerKeyHash;
  std::string serialNumber;

public:
  CertificateHashDataType() = default;

  explicit CertificateHashDataType(HashAlgorithmEnumType hashAlgorithmParam,
                                   std::string issuerNameHashParam,
                                   std::string issuerKeyHashParam,
                                   std::string serialNumberParam)
      : hashAlgorithm(hashAlgorithmParam),
        issuerNameHash(std::move(issuerNameHashParam)),
        issuerKeyHash(std::move(issuerKeyHashParam)),
        serialNumber(std::move(serialNumberParam)) { }

  [[nodiscard]] HashAlgorithmEnumType getHashAlgorithm() const {
    return hashAlgorithm;
  }

  void setHashAlgorithm(const HashAlgorithmEnumType& newHashAlgorithm) {
    hashAlgorithm = newHashAlgorithm;
  }

  [[nodiscard]] std::string getIssuerNameHash() const {
    return issuerNameHash;
  }

  void setIssuerNameHash(const std::string& newIssuerNameHash) {
    issuerNameHash = newIssuerNameHash;
  }

  [[nodiscard]] std::string getIssuerKeyHash() const {
    return issuerKeyHash;
  }

  void setIssuerKeyHash(const std::string& newIssuerKeyHash) {
    issuerKeyHash = newIssuerKeyHash;
  }

  [[nodiscard]] std::string getSerialNumber() const {
    return serialNumber;
  }

  void setSerialNumber(const std::string& newSerialNumber) {
    serialNumber = newSerialNumber;
  }

  friend void to_json(nlohmann::json &tJson, const CertificateHashDataType &hashData) {
    tJson = nlohmann::json{{"hashAlgorithm", magic_enum::enum_name(hashData.hashAlgorithm)},
                           {"issuerNameHash", hashData.issuerNameHash},
                           {"issuerKeyHash", hashData.issuerKeyHash},
                           {"serialNumber", hashData.serialNumber}};
  }

  friend void from_json(const nlohmann::json &tJson, CertificateHashDataType &hashData) {
    if (tJson.contains("hashAlgorithm")) {
      hashData.hashAlgorithm = magic_enum::enum_cast<HashAlgorithmEnumType>(tJson.at("hashAlgorithm").get<std::string>()).value();


    }
    tJson.at("issuerNameHash").get_to(hashData.issuerNameHash);
    tJson.at("issuerKeyHash").get_to(hashData.issuerKeyHash);
    tJson.at("serialNumber").get_to(hashData.serialNumber);
  }
};


class CertificateHashDataChainType {
private:
  GetCertificateIdUseEnumType certificateType;
  CertificateHashDataType certificateHashData;
  std::optional<CertificateHashDataType> childCertificateHashData;

public:
  CertificateHashDataChainType() = default;

  explicit CertificateHashDataChainType(GetCertificateIdUseEnumType certificateTypeParam,
                                        CertificateHashDataType certificateHashDataParam,
                                        const std::optional<CertificateHashDataType>& childCertificateHashDataParam = std::nullopt)
      : certificateType(certificateTypeParam),
        certificateHashData(std::move(certificateHashDataParam)),
        childCertificateHashData(childCertificateHashDataParam) { }

  [[nodiscard]] GetCertificateIdUseEnumType getCertificateType() const {
    return certificateType;
  }

  void setCertificateType(GetCertificateIdUseEnumType newCertificateType) {
    certificateType = newCertificateType;
  }

  [[nodiscard]] CertificateHashDataType getCertificateHashData() const {
    return certificateHashData;
  }

  void setCertificateHashData(const CertificateHashDataType& newCertificateHashData) {
    certificateHashData = newCertificateHashData;
  }

  [[nodiscard]] std::optional<CertificateHashDataType> getChildCertificateHashData() const {
    return childCertificateHashData;
  }

  void setChildCertificateHashData(const CertificateHashDataType& newChildCertificateHashData) {
    childCertificateHashData.emplace(newChildCertificateHashData);
  }

  friend void to_json(nlohmann::json &tJson, const CertificateHashDataChainType &chainData) {
    tJson.emplace("certificateType", magic_enum::enum_name(chainData.certificateType));
    tJson.emplace("certificateHashData", nlohmann::json(chainData.certificateHashData)) ;

    if (chainData.childCertificateHashData.has_value()) {
      tJson.emplace("childCertificateHashData", nlohmann::json(chainData.childCertificateHashData.value()));
    }
  }

  friend void from_json(const nlohmann::json &tJson, CertificateHashDataChainType &chainData) {
    if (tJson.contains("certificateType") ) {
      auto tmp  = magic_enum::enum_cast<GetCertificateIdUseEnumType>(tJson.at("certificateType").get<std::string>());
      if (tmp.has_value()) {
        chainData.certificateType = tmp.value();
      }
    }

    if (tJson.contains("certificateHashData")&& tJson.at("certificateHashData").is_object()) {
      tJson.at("certificateHashData").get_to(chainData.certificateHashData);
    }

    if (tJson.contains("childCertificateHashData")) {
      tJson.at("childCertificateHashData").get_to(chainData.childCertificateHashData.emplace());
    }
  }
};


class DCChargingParametersType {
private:
  int evMaxCurrent;
  int evMaxVoltage;
  std::optional<int> energyAmount;
  std::optional<int> evMaxPower;
  std::optional<int> stateOfCharge;
  std::optional<int> evEnergyCapacity;
  std::optional<int> fullSoC;
  std::optional<int> bulkSoC;

public:
  DCChargingParametersType() = default;

  explicit DCChargingParametersType(int evMaxCurrentParam, int evMaxVoltageParam,
                                    const std::optional<int>& energyAmountParam = std::nullopt,
                                    const std::optional<int>& evMaxPowerParam = std::nullopt,
                                    const std::optional<int>& stateOfChargeParam = std::nullopt,
                                    const std::optional<int>& evEnergyCapacityParam = std::nullopt,
                                    const std::optional<int>& fullSoCParam = std::nullopt,
                                    const std::optional<int>& bulkSoCParam = std::nullopt)
      : evMaxCurrent(evMaxCurrentParam),
        evMaxVoltage(evMaxVoltageParam),
        energyAmount(energyAmountParam),
        evMaxPower(evMaxPowerParam),
        stateOfCharge(stateOfChargeParam),
        evEnergyCapacity(evEnergyCapacityParam),
        fullSoC(fullSoCParam),
        bulkSoC(bulkSoCParam) { }

  // Getters and setters...

  friend void to_json(nlohmann::json &json, const DCChargingParametersType &data) {
    json["evMaxCurrent"] = data.evMaxCurrent;
    json["evMaxVoltage"] = data.evMaxVoltage;

    if (data.energyAmount.has_value())
      json["energyAmount"] = data.energyAmount.value();

    if (data.evMaxPower.has_value())
      json["evMaxPower"] = data.evMaxPower.value();

    if (data.stateOfCharge.has_value())
      json["stateOfCharge"] = data.stateOfCharge.value();

    if (data.evEnergyCapacity.has_value())
      json["evEnergyCapacity"] = data.evEnergyCapacity.value();

    if (data.fullSoC.has_value())
      json["fullSoC"] = data.fullSoC.value();

    if (data.bulkSoC.has_value())
      json["bulkSoC"] = data.bulkSoC.value();
  }

  friend void from_json(const nlohmann::json &json, DCChargingParametersType &data) {
    json.at("evMaxCurrent").get_to(data.evMaxCurrent);
    json.at("evMaxVoltage").get_to(data.evMaxVoltage);

    if (json.contains("energyAmount"))
      json.at("energyAmount").get_to(data.energyAmount.emplace());

    if (json.contains("evMaxPower"))
      json.at("evMaxPower").get_to(data.evMaxPower.emplace());

    if (json.contains("stateOfCharge"))
      json.at("stateOfCharge").get_to(data.stateOfCharge.emplace());

    if (json.contains("evEnergyCapacity"))
      json.at("evEnergyCapacity").get_to(data.evEnergyCapacity.emplace());

    if (json.contains("fullSoC"))
      json.at("fullSoC").get_to(data.fullSoC.emplace());

    if (json.contains("bulkSoC"))
      json.at("bulkSoC").get_to(data.bulkSoC.emplace());
  }
};

class ChargingLimitType {
private:
  ChargingLimitSourceEnumType chargingLimitSource;
  std::optional<bool> isGridCritical;

public:
  ChargingLimitType() = default;

  explicit ChargingLimitType(ChargingLimitSourceEnumType chargingLimitSourceParam,
                             const std::optional<bool>& isGridCriticalParam = std::nullopt)
      : chargingLimitSource(chargingLimitSourceParam),
        isGridCritical(isGridCriticalParam) { }

  [[nodiscard]] ChargingLimitSourceEnumType getChargingLimitSource() const {
    return chargingLimitSource;
  }

  void setChargingLimitSource(ChargingLimitSourceEnumType newChargingLimitSource) {
    chargingLimitSource = newChargingLimitSource;
  }

  [[nodiscard]] std::optional<bool> getIsGridCritical() const {
    return isGridCritical;
  }

  void setIsGridCritical(const std::optional<bool>& newIsGridCritical) {
    isGridCritical = newIsGridCritical;
  }

  friend void to_json(nlohmann::json &j, const ChargingLimitType &data) {
    j["chargingLimitSource"] = magic_enum::enum_name(data.chargingLimitSource);

    if(data.isGridCritical.has_value())
      j["isGridCritical"] = data.isGridCritical.value();
  }

  friend void from_json(const nlohmann::json &j, ChargingLimitType &data) {
    if (j.contains("chargingLimitSource")) {
      auto tmp  = magic_enum::enum_cast<ChargingLimitSourceEnumType>(j.at("chargingLimitSource").get<std::string>());
      if (tmp.has_value()) {
        data.chargingLimitSource = tmp.value();
      }
    }

    if (j.contains("isGridCritical"))
      j.at("isGridCritical").get_to(data.isGridCritical.emplace());
  }
};

class ChargingNeedsType {
private:
  EnergyTransferModeEnumType requestedEnergyTransfer;
  std::optional<std::string> departureTime;
  std::optional<ACChargingParametersType> acChargingParameters;
  std::optional<DCChargingParametersType> dcChargingParameters;

public:
  ChargingNeedsType() = default;

  explicit ChargingNeedsType(EnergyTransferModeEnumType requestedEnergyTransferParam,
                             const std::optional<std::string>& departureTimeParam = std::nullopt,
                             const std::optional<ACChargingParametersType>& acChargingParametersParam = std::nullopt,
                             const std::optional<DCChargingParametersType>& dcChargingParametersParam = std::nullopt)
      : requestedEnergyTransfer(requestedEnergyTransferParam),
        departureTime(departureTimeParam),
        acChargingParameters(acChargingParametersParam),
        dcChargingParameters(dcChargingParametersParam) { }

  [[nodiscard]] EnergyTransferModeEnumType getRequestedEnergyTransfer() const {
    return requestedEnergyTransfer;
  }

  void setRequestedEnergyTransfer(EnergyTransferModeEnumType newRequestedEnergyTransfer) {
    requestedEnergyTransfer = newRequestedEnergyTransfer;
  }

  [[nodiscard]] std::optional<std::string> getDepartureTime() const {
    return departureTime;
  }

  void setDepartureTime(const std::optional<std::string>& newDepartureTime) {
    departureTime = newDepartureTime;
  }

  [[nodiscard]] std::optional<ACChargingParametersType> getAcChargingParameters() const {
    return acChargingParameters;
  }

  void setAcChargingParameters(const ACChargingParametersType& newAcChargingParameters) {
    acChargingParameters = newAcChargingParameters;
  }

  [[nodiscard]] std::optional<DCChargingParametersType> getDcChargingParameters() const {
    return dcChargingParameters;
  }

  void setDcChargingParameters(const DCChargingParametersType& newDcChargingParameters) {
    dcChargingParameters = newDcChargingParameters;
  }

  friend void to_json(nlohmann::json &json, const ChargingNeedsType &data) {
    json["requestedEnergyTransfer"] = magic_enum::enum_name(data.requestedEnergyTransfer);

    if(data.departureTime.has_value())
      json["departureTime"] = data.departureTime.value();

    if(data.acChargingParameters.has_value())
      json["acChargingParameters"] = data.acChargingParameters.value();

    if(data.dcChargingParameters.has_value())
      json["dcChargingParameters"] = data.dcChargingParameters.value();
  }

  friend void from_json(const nlohmann::json &json, ChargingNeedsType &data) {
    if (json.contains("requestedEnergyTransfer")) {
      auto tmp = magic_enum::enum_cast<EnergyTransferModeEnumType>(json.at("requestedEnergyTransfer").get<std::string>());
      if (tmp.has_value()) {
        data.requestedEnergyTransfer = tmp.value();
      }
    }
    if (json.contains("departureTime"))
      json.at("departureTime").get_to(data.departureTime.emplace());

    if (json.contains("acChargingParameters"))
      json.at("acChargingParameters").get_to(data.acChargingParameters.emplace());

    if (json.contains("dcChargingParameters"))
      json.at("dcChargingParameters").get_to(data.dcChargingParameters.emplace());
  }
};

class ChargingProfileCriterionType {
private:
  std::optional<ChargingProfilePurposeEnumType> chargingProfilePurpose;
  std::optional<int> stackLevel;
  std::vector<int> chargingProfileId;
  std::vector<ChargingLimitSourceEnumType> chargingLimitSource;

public:
  ChargingProfileCriterionType() = default;

  explicit ChargingProfileCriterionType(const std::optional<ChargingProfilePurposeEnumType>& chargingProfilePurposeParam = std::nullopt,
                                        const std::optional<int>& stackLevelParam = std::nullopt,
                                        const std::vector<int>& chargingProfileIdParam = {},
                                        const std::vector<ChargingLimitSourceEnumType>& chargingLimitSourceParam = {})
      : chargingProfilePurpose(chargingProfilePurposeParam),
        stackLevel(stackLevelParam),
        chargingProfileId(chargingProfileIdParam),
        chargingLimitSource(chargingLimitSourceParam) { }

  // Getters and setters...

  friend void to_json(nlohmann::json &j, const ChargingProfileCriterionType &data) {
    if(data.chargingProfilePurpose.has_value())
      j["chargingProfilePurpose"] = magic_enum::enum_name(data.chargingProfilePurpose.value());

    if(data.stackLevel.has_value())
      j["stackLevel"] = data.stackLevel.value();

    j["chargingProfileId"] = data.chargingProfileId;
    j["chargingLimitSource"] = data.chargingLimitSource;
  }

  friend void from_json(const nlohmann::json &j, ChargingProfileCriterionType &data) {
    if (j.contains("chargingProfilePurpose")) {
      auto tmp = magic_enum::enum_cast<ChargingProfilePurposeEnumType>(j.at("chargingProfilePurpose").get<std::string>());
      if (tmp.has_value()) {
        data.chargingProfilePurpose = tmp.value();
      }
    }

    if (j.contains("stackLevel"))
      j.at("stackLevel").get_to(data.stackLevel.emplace());

    j.at("chargingProfileId").get_to(data.chargingProfileId);
    j.at("chargingLimitSource").get_to(data.chargingLimitSource);
  }
};


class ChargingSchedulePeriodType {
private:
  int startPeriod;
  double limit;
  std::optional<int> numberPhases;
  std::optional<int> phaseToUse;

public:
  ChargingSchedulePeriodType() = default;

  explicit ChargingSchedulePeriodType(int startPeriodParam, double limitParam,
                                      const std::optional<int>& numberPhasesParam = std::nullopt,
                                      const std::optional<int>& phaseToUseParam = std::nullopt)
      : startPeriod(startPeriodParam),
        limit(limitParam),
        numberPhases(numberPhasesParam),
        phaseToUse(phaseToUseParam) { }

  [[nodiscard]] int getStartPeriod() const {
    return startPeriod;
  }

  [[nodiscard]] double getLimit() const {
    return limit;
  }

  [[nodiscard]] std::optional<int> getNumberPhases() const {
    return numberPhases;
  }

  [[nodiscard]] std::optional<int> getPhaseToUse() const {
    return phaseToUse;
  }

  // Setters
  void setStartPeriod(int newStartPeriod) {
    startPeriod = newStartPeriod;
  }

  void setLimit(double newLimit) {
    limit = newLimit;
  }

  void setNumberPhases(const std::optional<int>& newNumberPhases) {
    numberPhases = newNumberPhases;
  }

  void setPhaseToUse(const std::optional<int>& newPhaseToUse) {
    phaseToUse = newPhaseToUse;
  }

  friend void to_json(nlohmann::json &j, const ChargingSchedulePeriodType &data) {
    j["startPeriod"] = data.startPeriod;
    j["limit"] = data.limit;

    if(data.numberPhases.has_value())
      j["numberPhases"] = data.numberPhases.value();

    if(data.phaseToUse.has_value())
      j["phaseToUse"] = data.phaseToUse.value();
  }

  friend void from_json(const nlohmann::json &j, ChargingSchedulePeriodType &data) {
    j.at("startPeriod").get_to(data.startPeriod);
    j.at("limit").get_to(data.limit);

    if(j.contains("numberPhases"))
      j.at("numberPhases").get_to(data.numberPhases.emplace());

    if(j.contains("phaseToUse"))
      j.at("phaseToUse").get_to(data.phaseToUse.emplace());
  }
};

class RelativeTimeIntervalType {
private:
  int start;
  std::optional<int> duration;

public:
  RelativeTimeIntervalType() = default;

  explicit RelativeTimeIntervalType(int startParam, const std::optional<int>& durationParam = std::nullopt)
      : start(startParam),
        duration(durationParam) {}

  // Getters
  [[nodiscard]] int getStart() const {
    return start;
  }

  [[nodiscard]] std::optional<int> getDuration() const {
    return duration;
  }

  // Setters
  void setStart(int newStart) {
    start = newStart;
  }

  void setDuration(const std::optional<int>& newDuration) {
    duration = newDuration;
  }

  friend void to_json(nlohmann::json& j, const RelativeTimeIntervalType& data) {
    j.emplace("start",data.start);
    if (data.duration.has_value()) {
      j.emplace("duration", data.duration.value());
    }
  }

  friend void from_json(const nlohmann::json& j, RelativeTimeIntervalType& data) {
    j.at("start").get_to(data.start);

    if (j.contains("duration")) {
      j.at("duration").get_to(data.duration.emplace());
    }
  }
};

class CostType {
private:
  CostKindEnumType costKind;
  int amount;
  std::optional<int> amountMultiplier;

public:
  CostType() = default;

  explicit CostType(CostKindEnumType costKindParam, int amountParam, const std::optional<int>& amountMultiplierParam = std::nullopt)
      : costKind(costKindParam),
        amount(amountParam),
        amountMultiplier(amountMultiplierParam) {}

  // Getters
  [[nodiscard]] CostKindEnumType getCostKind() const {
    return costKind;
  }

  [[nodiscard]] int getAmount() const {
    return amount;
  }

  [[nodiscard]] std::optional<int> getAmountMultiplier() const {
    return amountMultiplier;
  }

  // Setters
  void setCostKind(CostKindEnumType newCostKind) {
    costKind = newCostKind;
  }

  void setAmount(int newAmount) {
    amount = newAmount;
  }

  void setAmountMultiplier(const std::optional<int>& newAmountMultiplier) {
    amountMultiplier = newAmountMultiplier;
  }

  // to_json and from_json functions
  friend void to_json(nlohmann::json& j, const CostType& data) {
    j.emplace("costKind", magic_enum::enum_name(data.costKind));
    j.emplace("amount", data.amount);
    if (data.amountMultiplier.has_value()) {
      j.emplace("amountMultiplier", data.amountMultiplier.value());

    }
  }

  friend void from_json(const nlohmann::json& j, CostType& data) {
    j.at("costKind").get_to(data.costKind);
    j.at("amount").get_to(data.amount);

    if (j.contains("amountMultiplier")) {
      j.at("amountMultiplier").get_to(data.amountMultiplier.emplace());
    }
  }
};



class ConsumptionCostType {
private:
  double startValue;
  std::vector<CostType> costDetails;

public:
  ConsumptionCostType() = default;

  explicit ConsumptionCostType(double startValueParam, const std::vector<CostType>& costDetailsParam)
      : startValue(startValueParam),
        costDetails(costDetailsParam) {}

  // Getters
  [[nodiscard]] double getStartValue() const {
    return startValue;
  }

  [[nodiscard]] const std::vector<CostType>& getCostDetails() const {
    return costDetails;
  }

  // Setters
  void setStartValue(double newStartValue) {
    startValue = newStartValue;
  }

  void setCostDetails(const std::vector<CostType>& newCostDetails) {
    costDetails = newCostDetails;
  }

  // to_json and from_json functions
  friend void to_json(nlohmann::json& j, const ConsumptionCostType& data) {
    j = nlohmann::json{
        {"startValue", data.startValue},
        {"costDetails", data.costDetails},
    };
  }

  friend void from_json(const nlohmann::json& j, ConsumptionCostType& data) {
    j.at("startValue").get_to(data.startValue);
    j.at("costDetails").get_to(data.costDetails);
  }
};

class SalesTariffEntryType {
private:
  int ePriceLevel;
  RelativeTimeIntervalType relativeTimeInterval;
  std::vector<ConsumptionCostType> consumptionCost;

public:
  SalesTariffEntryType() = default;

  explicit SalesTariffEntryType(int ePriceLevelParam, const RelativeTimeIntervalType& relativeTimeIntervalParam,
                                const std::vector<ConsumptionCostType>& consumptionCostParam = {})
      : ePriceLevel(ePriceLevelParam),
        relativeTimeInterval(relativeTimeIntervalParam),
        consumptionCost(consumptionCostParam) {}

  // Getters
  [[nodiscard]] int getEPriceLevel() const {
    return ePriceLevel;
  }

  [[nodiscard]] const RelativeTimeIntervalType& getRelativeTimeInterval() const {
    return relativeTimeInterval;
  }

  [[nodiscard]] const std::vector<ConsumptionCostType>& getConsumptionCost() const {
    return consumptionCost;
  }

  // Setters
  void setEPriceLevel(int newEPriceLevel) {
    ePriceLevel = newEPriceLevel;
  }

  void setRelativeTimeInterval(const RelativeTimeIntervalType& newRelativeTimeInterval) {
    relativeTimeInterval = newRelativeTimeInterval;
  }

  void setConsumptionCost(const std::vector<ConsumptionCostType>& newConsumptionCost) {
    consumptionCost = newConsumptionCost;
  }
  friend void to_json(nlohmann::json& j, const SalesTariffEntryType& data) {
    j = nlohmann::json{
        {"ePriceLevel", data.ePriceLevel},
        {"relativeTimeInterval", data.relativeTimeInterval},
        {"consumptionCost", data.consumptionCost},
    };
  }

  friend void from_json(const nlohmann::json& j, SalesTariffEntryType& data) {
    j.at("ePriceLevel").get_to(data.ePriceLevel);
    j.at("relativeTimeInterval").get_to(data.relativeTimeInterval);
    j.at("consumptionCost").get_to(data.consumptionCost);
  }

};

class SalesTariffType {
private:
  int id;
  std::optional<std::string> salesTariffDescription;
  std::optional<int> numEPriceLevels;
  std::vector<SalesTariffEntryType> salesTariffEntry;

public:
  SalesTariffType() = default;

  explicit SalesTariffType(int idParam,
                           const std::optional<std::string>& salesTariffDescriptionParam = std::nullopt,
                           const std::optional<int>& numEPriceLevelsParam = std::nullopt,
                           const std::vector<SalesTariffEntryType>& salesTariffEntryParam = {})
      : id(idParam),
        salesTariffDescription(salesTariffDescriptionParam),
        numEPriceLevels(numEPriceLevelsParam),
        salesTariffEntry(salesTariffEntryParam) {}

  [[nodiscard]] int getId() const {
    return id;
  }

  [[nodiscard]] std::optional<std::string> getSalesTariffDescription() const {
    return salesTariffDescription;
  }

  [[nodiscard]] std::optional<int> getNumEPriceLevels() const {
    return numEPriceLevels;
  }

  [[nodiscard]] const std::vector<SalesTariffEntryType>& getSalesTariffEntry() const {
    return salesTariffEntry;
  }

  void setId(int newId) {
    id = newId;
  }

  void setSalesTariffDescription(const std::optional<std::string>& newSalesTariffDescription) {
    salesTariffDescription = newSalesTariffDescription;
  }

  void setNumEPriceLevels(const std::optional<int>& newNumEPriceLevels) {
    numEPriceLevels = newNumEPriceLevels;
  }

  void setSalesTariffEntry(const std::vector<SalesTariffEntryType>& newSalesTariffEntry) {
    salesTariffEntry = newSalesTariffEntry;
  }
  friend void to_json(nlohmann::json& j, const SalesTariffType& data) {
    j.emplace("id", data.id);
    j.emplace("salesTariffEntry", data.salesTariffEntry);
    if (data.numEPriceLevels.has_value()) {
      j.emplace("numEPriceLevels", data.numEPriceLevels.value());
    }
    if (data.salesTariffDescription.has_value()) {
      j.emplace("salesTariffDescription", data.salesTariffDescription.value_or(""));
    }
  }

  friend void from_json(const nlohmann::json& j, SalesTariffType& data) {
    j.at("id").get_to(data.id);
    j.at("salesTariffDescription").get_to(data.salesTariffDescription.emplace());
    j.at("numEPriceLevels").get_to(data.numEPriceLevels.emplace());
    j.at("salesTariffEntry").get_to(data.salesTariffEntry);
  }
};



class ChargingScheduleType {
private:
  int id;
  std::optional<RFC3339DateTime> startSchedule;
  std::optional<int> duration;
  ChargingRateUnitEnumType chargingRateUnit;
  std::optional<double> minChargingRate;
  std::vector<ChargingSchedulePeriodType> chargingSchedulePeriod;
  std::optional<SalesTariffType> salesTariff;

public:
  ChargingScheduleType() = default;

  explicit ChargingScheduleType(int idParam,
                                const std::optional<RFC3339DateTime>& startScheduleParam = std::nullopt,
                                const std::optional<int>& durationParam = std::nullopt,
                                ChargingRateUnitEnumType chargingRateUnitParam = ChargingRateUnitEnumType::W,
                                const std::optional<double>& minChargingRateParam = std::nullopt,
                                const std::vector<ChargingSchedulePeriodType>& chargingSchedulePeriodParam = {},
                                const std::optional<SalesTariffType>& salesTariffParam = std::nullopt)
      : id(idParam),
        startSchedule(startScheduleParam),
        duration(durationParam),
        chargingRateUnit(chargingRateUnitParam),
        minChargingRate(minChargingRateParam),
        chargingSchedulePeriod(chargingSchedulePeriodParam),
        salesTariff(salesTariffParam) {}

  [[nodiscard]] int getId() const {
    return id;
  }

  void setId(int newId) {
    id = newId;
  }

  [[nodiscard]] std::optional<RFC3339DateTime> getStartSchedule() const {
    return startSchedule;
  }

  void setStartSchedule(const std::optional<RFC3339DateTime>& newStartSchedule) {
    startSchedule = newStartSchedule;
  }

  [[nodiscard]] std::optional<int> getDuration() const {
    return duration;
  }

  void setDuration(const std::optional<int>& newDuration) {
    duration = newDuration;
  }

  [[nodiscard]] ChargingRateUnitEnumType getChargingRateUnit() const {
    return chargingRateUnit;
  }

  void setChargingRateUnit(ChargingRateUnitEnumType newChargingRateUnit) {
    chargingRateUnit = newChargingRateUnit;
  }

  [[nodiscard]] std::optional<double> getMinChargingRate() const {
    return minChargingRate;
  }

  void setMinChargingRate(const std::optional<double>& newMinChargingRate) {
    minChargingRate = newMinChargingRate;
  }

  [[nodiscard]] const std::vector<ChargingSchedulePeriodType>& getChargingSchedulePeriod() const {
    return chargingSchedulePeriod;
  }

  void setChargingSchedulePeriod(const std::vector<ChargingSchedulePeriodType>& newChargingSchedulePeriod) {
    chargingSchedulePeriod = newChargingSchedulePeriod;
  }

  [[nodiscard]] std::optional<SalesTariffType> getSalesTariff() const {
    return salesTariff;
  }

  void setSalesTariff(const std::optional<SalesTariffType>& newSalesTariff) {
    salesTariff = newSalesTariff;
  }

  friend void to_json(nlohmann::json& j, const ChargingScheduleType& data) {
    j.emplace("id", data.id);
    if (data.startSchedule.has_value()) {
      j.emplace("startSchedule", data.startSchedule.value().toString());
    }
    if (data.duration.has_value()) {
      j.emplace("duration", data.duration.value());
    }
    j.emplace("chargingRateUnit", magic_enum::enum_name(data.chargingRateUnit));
    if (data.minChargingRate.has_value()) {
      j.emplace("minChargingRate", data.minChargingRate.value());
    }
    j.emplace("chargingSchedulePeriod", data.chargingSchedulePeriod);
    if (data.salesTariff.has_value()) {
      j.emplace("salesTariff", data.salesTariff.value());
    }

  }

  friend void from_json(const nlohmann::json& j, ChargingScheduleType& data) {
    j.at("id").get_to(data.id);
    if (j.contains("startSchedule"))
      data.startSchedule.emplace(RFC3339DateTime::fromString(j.at("startSchedule")));
    if (j.contains("duration"))
      j.at("duration").get_to(data.duration.emplace());
    j.at("chargingRateUnit").get_to(data.chargingRateUnit);
    if (j.contains("minChargingRate"))
      j.at("minChargingRate").get_to(data.minChargingRate.emplace());
    j.at("chargingSchedulePeriod").get_to(data.chargingSchedulePeriod);
    if (j.contains("salesTariff"))
      j.at("salesTariff").get_to(data.salesTariff.emplace());
  }
};



class ChargingProfileType {
private:
  int id;
  int stackLevel;
  ChargingProfilePurposeEnumType chargingProfilePurpose;
  ChargingProfileKindEnumType chargingProfileKind;
  std::optional<RecurrencyKindEnumType> recurrencyKind;
  std::optional<std::string> validFrom;
  std::optional<std::string> validTo;
  std::optional<std::string> transactionId;
  std::vector<ChargingScheduleType> chargingSchedule;

public:
  ChargingProfileType() = default;

  explicit ChargingProfileType(int idParam, int stackLevelParam,
                               ChargingProfilePurposeEnumType chargingProfilePurposeParam,
                               ChargingProfileKindEnumType chargingProfileKindParam,
                               const std::optional<RecurrencyKindEnumType>& recurrencyKindParam = std::nullopt,
                               const std::optional<std::string>& validFromParam = std::nullopt,
                               const std::optional<std::string>& validToParam = std::nullopt,
                               const std::optional<std::string>& transactionIdParam = std::nullopt,
                               const std::vector<ChargingScheduleType>& chargingScheduleParam = {})
      : id(idParam),
        stackLevel(stackLevelParam),
        chargingProfilePurpose(chargingProfilePurposeParam),
        chargingProfileKind(chargingProfileKindParam),
        recurrencyKind(recurrencyKindParam),
        validFrom(validFromParam),
        validTo(validToParam),
        transactionId(transactionIdParam),
        chargingSchedule(chargingScheduleParam) { }


  [[nodiscard]] const int getId() const {
    return this->id;
  }

  void setId(int newID) {
    this->id = newID;
  }
  ChargingProfilePurposeEnumType getChargingProfilePurpose() const {
    return chargingProfilePurpose;
  }

  void setChargingProfilePurpose(ChargingProfilePurposeEnumType newPurpose) {
    chargingProfilePurpose = newPurpose;
  }

  ChargingProfileKindEnumType getChargingProfileKind() const {
    return chargingProfileKind;
  }

  void setChargingProfileKind(ChargingProfileKindEnumType newKind) {
    chargingProfileKind = newKind;
  }

  std::optional<RecurrencyKindEnumType> getRecurrencyKind() const {
    return recurrencyKind;
  }

  void setRecurrencyKind(const std::optional<RecurrencyKindEnumType>& newRecurrencyKind) {
    recurrencyKind = newRecurrencyKind;
  }

  std::optional<std::string> getValidFrom() const {
    return validFrom;
  }

  void setValidFrom(const std::optional<std::string>& newValidFrom) {
    validFrom = newValidFrom;
  }

  std::optional<std::string> getValidTo() const {
    return validTo;
  }

  void setValidTo(const std::optional<std::string>& newValidTo) {
    validTo = newValidTo;
  }

  std::optional<std::string> getTransactionId() const {
    return transactionId;
  }

  void setTransactionId(const std::optional<std::string>& newTransactionId) {
    transactionId = newTransactionId;
  }

  std::vector<ChargingScheduleType> getChargingSchedule() const {
    return chargingSchedule;
  }

  void setChargingSchedule(const std::vector<ChargingScheduleType>& newChargingSchedule) {
    chargingSchedule = newChargingSchedule;
  }


  friend void to_json(nlohmann::json &j, const ChargingProfileType &data) {
    j["id"] = data.id;
    j["stackLevel"] = data.stackLevel;
    j["chargingProfilePurpose"] = magic_enum::enum_name(data.chargingProfilePurpose);
    j["chargingProfileKind"] = magic_enum::enum_name(data.chargingProfileKind);

    if(data.recurrencyKind.has_value())
      j["recurrencyKind"] = magic_enum::enum_name(data.recurrencyKind.value());

    if(data.validFrom.has_value())
      j["validFrom"] = data.validFrom.value();

    if(data.validTo.has_value())
      j["validTo"] = data.validTo.value();

    if(data.transactionId.has_value())
      j["transactionId"] = data.transactionId.value();

    j["chargingSchedule"] = data.chargingSchedule;
  }

  friend void from_json(const nlohmann::json &j, ChargingProfileType &data) {
    j.at("id").get_to(data.id);
    j.at("stackLevel").get_to(data.stackLevel);

    auto tmp1 = magic_enum::enum_cast<ChargingProfilePurposeEnumType>(j.at("chargingProfilePurpose").get<std::string>());
    if (tmp1.has_value()) {
      data.chargingProfilePurpose = tmp1.value();
    }

    auto tmp2 = magic_enum::enum_cast<ChargingProfileKindEnumType>(j.at("chargingProfileKind").get<std::string>());
    if (tmp2.has_value()) {
      data.chargingProfileKind = tmp2.value();
    }

    if (j.contains("recurrencyKind")) {
      auto tmp3 = magic_enum::enum_cast<RecurrencyKindEnumType>(j.at("recurrencyKind").get<std::string>());
      if (tmp3.has_value()) {
        data.recurrencyKind = tmp3.value();
      }
    }

    if (j.contains("validFrom"))
      j.at("validFrom").get_to(data.validFrom.emplace());

    if (j.contains("validTo"))
      j.at("validTo").get_to(data.validTo.emplace());

    if (j.contains("transactionId"))
      j.at("transactionId").get_to(data.transactionId.emplace());

    j.at("chargingSchedule").get_to(data.chargingSchedule);
  }
};

class ModemType {
private:
  std::optional<IdentifierString> iccid;
  std::optional<IdentifierString> imsi;

public:
  ModemType() = default;

  explicit ModemType(const std::optional<IdentifierString>& iccidParam = std::nullopt,
                     const std::optional<IdentifierString>& imsiParam = std::nullopt)
      : iccid(iccidParam),
        imsi(imsiParam) {}
  std::optional<IdentifierString> getIccid() const {
    return iccid;
  }

  void setIccid(const std::optional<IdentifierString>& newIccid) {
    iccid = newIccid;
  }

  std::optional<IdentifierString> getImsi() const {
    return imsi;
  }

  void setImsi(const std::optional<IdentifierString>& newImsi) {
    imsi = newImsi;
  }


  friend void to_json(nlohmann::json& j, const ModemType& data) {
    if (data.iccid.has_value())
      j["iccid"] = data.iccid.value();

    if (data.imsi.has_value())
      j["imsi"] = data.imsi.value();
  }

  friend void from_json(const nlohmann::json& j, ModemType& data) {
    if (j.contains("iccid"))
      j.at("iccid").get_to(data.iccid.emplace());

    if (j.contains("imsi"))
      j.at("imsi").get_to(data.imsi.emplace());
  }
};


class ChargingStationType {
private:
  std::optional<std::string> serialNumber;
  std::string model;
  std::string vendorName;
  std::optional<std::string> firmwareVersion;
  std::optional<ModemType> modem;

public:
  ChargingStationType() = default;

  explicit ChargingStationType(const std::string& modelParam,
                               const std::string& vendorNameParam,
                               const std::optional<std::string>& serialNumberParam = std::nullopt,
                               const std::optional<std::string>& firmwareVersionParam = std::nullopt,
                               const std::optional<ModemType>& modemParam = std::nullopt)
      : serialNumber(serialNumberParam),
        model(modelParam),
        vendorName(vendorNameParam),
        firmwareVersion(firmwareVersionParam),
        modem(modemParam) { }

  std::optional<std::string> getSerialNumber() const {
    return serialNumber;
  }

  void setSerialNumber(const std::optional<std::string>& newSerialNumber) {
    serialNumber = newSerialNumber;
  }

  std::string getModel() const {
    return model;
  }

  void setModel(const std::string& newModel) {
    model = newModel;
  }

  std::string getVendorName() const {
    return vendorName;
  }

  void setVendorName(const std::string& newVendorName) {
    vendorName = newVendorName;
  }

  std::optional<std::string> getFirmwareVersion() const {
    return firmwareVersion;
  }

  void setFirmwareVersion(const std::optional<std::string>& newFirmwareVersion) {
    firmwareVersion = newFirmwareVersion;
  }

  std::optional<ModemType> getModem() const {
    return modem;
  }

  void setModem(const std::optional<ModemType>& newModem) {
    modem = newModem;
  }


  friend void to_json(nlohmann::json &j, const ChargingStationType &data) {
    if(data.serialNumber.has_value())
      j["serialNumber"] = data.serialNumber.value();

    j["model"] = data.model;
    j["vendorName"] = data.vendorName;

    if(data.firmwareVersion.has_value())
      j["firmwareVersion"] = data.firmwareVersion.value();

    if(data.modem.has_value())
      j["modem"] = data.modem.value();
  }

  friend void from_json(const nlohmann::json &j, ChargingStationType &data) {
    if(j.contains("serialNumber"))
      j.at("serialNumber").get_to(data.serialNumber.emplace());

    j.at("model").get_to(data.model);
    j.at("vendorName").get_to(data.vendorName);

    if(j.contains("firmwareVersion"))
      j.at("firmwareVersion").get_to(data.firmwareVersion.emplace());

    if(j.contains("modem"))
      data.modem.emplace(j.at("modem"));
  }
};

class ClearChargingProfileType {
private:
  std::optional<int> evseId;
  std::optional<ChargingProfilePurposeEnumType> chargingProfilePurpose;
  std::optional<int> stackLevel;

public:
  ClearChargingProfileType() = default;

  explicit ClearChargingProfileType(const std::optional<int>& evseIdParam = std::nullopt,
                                    const std::optional<ChargingProfilePurposeEnumType>& chargingProfilePurposeParam = std::nullopt,
                                    const std::optional<int>& stackLevelParam = std::nullopt)
      : evseId(evseIdParam),
        chargingProfilePurpose(chargingProfilePurposeParam),
        stackLevel(stackLevelParam) {}

  friend void to_json(nlohmann::json& j, const ClearChargingProfileType& data) {
    if (data.evseId.has_value())
      j["evseId"] = data.evseId.value();

    if (data.chargingProfilePurpose.has_value())
      j["chargingProfilePurpose"] = magic_enum::enum_name(data.chargingProfilePurpose.value());

    if (data.stackLevel.has_value())
      j["stackLevel"] = data.stackLevel.value();
  }

  friend void from_json(const nlohmann::json& j, ClearChargingProfileType& data) {
    if (j.contains("evseId"))
      j.at("evseId").get_to(data.evseId.emplace());

    if (j.contains("chargingProfilePurpose")) {
      auto tmp = magic_enum::enum_cast<ChargingProfilePurposeEnumType>(j.at("chargingProfilePurpose").get<std::string>());
      if (tmp.has_value()) {
        data.chargingProfilePurpose = tmp.value();
      }
    }

    if (j.contains("stackLevel"))
      j.at("stackLevel").get_to(data.stackLevel.emplace());
  }
};


class StatusInfoType {
public:
  std::string reasonCode;
  std::optional<std::string> additionalInfo;

  // Constructors
  StatusInfoType() = default;

  StatusInfoType(const std::string& reasonCodeParam, const std::optional<std::string>& additionalInfoParam = std::nullopt)
      : reasonCode(reasonCodeParam), additionalInfo(additionalInfoParam) {}

  const std::string& getReasonCode() const {
    return reasonCode;
  }

  void setReasonCode(const std::string& newReasonCode) {
    reasonCode = newReasonCode;
  }

  const std::optional<std::string>& getAdditionalInfo() const {
    return additionalInfo;
  }

  void setAdditionalInfo(const std::optional<std::string>& newAdditionalInfo) {
    additionalInfo = newAdditionalInfo;
  }

  friend void to_json(nlohmann::json& j, const StatusInfoType& data) {
    j["reasonCode"] = data.reasonCode;
    if (data.additionalInfo.has_value()) {
      j["additionalInfo"] = data.additionalInfo.value();
    }
  }

  friend void from_json(const nlohmann::json& j, StatusInfoType& data) {
    j.at("reasonCode").get_to(data.reasonCode);
    if (j.contains("additionalInfo")) {
      j.at("additionalInfo").get_to(data.additionalInfo.emplace());
    }
  }
};


class ClearMonitoringResultType {
private:
  ClearMonitoringStatusEnumType status;
  int id;
  std::optional<StatusInfoType> statusInfo;

public:
  ClearMonitoringResultType() = default;

  explicit ClearMonitoringResultType(ClearMonitoringStatusEnumType statusParam,
                                     int idParam,
                                     const std::optional<StatusInfoType>& statusInfoParam = std::nullopt)
      : status(statusParam),
        id(idParam),
        statusInfo(statusInfoParam) { }

  [[nodiscard]] ClearMonitoringStatusEnumType getStatus() const {
    return this->status;
  }

  void setStatus(ClearMonitoringStatusEnumType newStatus) {
    this->status = newStatus;
  }

  [[nodiscard]] int getId() const {
    return this->id;
  }

  void setId(int newId) {
    this->id = newId;
  }

  [[nodiscard]] std::optional<StatusInfoType> getStatusInfo() const {
    return this->statusInfo;
  }

  void setStatusInfo(const std::optional<StatusInfoType>& newStatusInfo) {
    this->statusInfo = newStatusInfo;
  }

  friend void to_json(nlohmann::json &j, const ClearMonitoringResultType &data) {
    j["status"] = magic_enum::enum_name(data.status);
    j["id"] = data.id;

    if(data.statusInfo.has_value())
      j["statusInfo"] = data.statusInfo.value();
  }

  friend void from_json(const nlohmann::json &j, ClearMonitoringResultType &data) {
    auto tmp1 = magic_enum::enum_cast<ClearMonitoringStatusEnumType>(j.at("status").get<std::string>());
    if (tmp1.has_value()) {
      data.status = tmp1.value();
    }

    j.at("id").get_to(data.id);

    if (j.contains("statusInfo"))
      data.statusInfo = j.at("statusInfo");
  }
};


class EVSEType {
public:
  // Fields
  int id;                     // EVSE Identifier
  std::optional<int> connectorId;  // Optional connector identifier

  // Constructors
  EVSEType() : id(0), connectorId(std::nullopt) {}

  EVSEType(int idParam, const std::optional<int>& connectorIdParam = std::nullopt)
      : id(idParam), connectorId(connectorIdParam) {}

  // Getter and setter functions for member variables
  int getId() const {
    return id;
  }

  void setId(int newId) {
    id = newId;
  }

  const std::optional<int>& getConnectorId() const {
    return connectorId;
  }

  void setConnectorId(const std::optional<int>& newConnectorId) {
    connectorId = newConnectorId;
  }

  // JSON serialization functions
  friend void to_json(nlohmann::json& j, const EVSEType& data) {
    j.emplace("id", data.id);
    if (data.connectorId.has_value()) {
      j.emplace("connectorId", data.connectorId.value());
    }
  }

  friend void from_json(const nlohmann::json& j, EVSEType& data) {
    j.at("id").get_to(data.id);
    if (j.contains("connectorId")) {
      j.at("connectorId").get_to(data.connectorId.emplace());
    }
  }
};



class ComponentType {
public:
  // Fields
  std::string name;      // Name of the component
  std::string instance;  // Name of the instance in case the component exists as multiple instances
  EVSEType evse;         // Specifies the EVSE when the component is located at EVSE level

  // Constructors
  ComponentType() = default;

  ComponentType(const std::string& nameParam, const std::string& instanceParam = "", const EVSEType& evseParam = EVSEType())
      : name(nameParam), instance(instanceParam), evse(evseParam) {}

  // Getter and setter functions for member variables
  const std::string& getName() const {
    return name;
  }

  void setName(const std::string& newName) {
    name = newName;
  }

  const std::string& getInstance() const {
    return instance;
  }

  void setInstance(const std::string& newInstance) {
    instance = newInstance;
  }

  const EVSEType& getEVSE() const {
    return evse;
  }

  void setEVSE(const EVSEType& newEVSE) {
    evse = newEVSE;
  }

  // JSON serialization functions (you may need to adjust these based on your implementation)
  friend void to_json(nlohmann::json& j, const ComponentType& data) {
    j["name"] = data.name;
    j["instance"] = data.instance;
    j["evse"] = data.evse;
  }

  friend void from_json(const nlohmann::json& j, ComponentType& data) {
    j.at("name").get_to(data.name);
    j.at("instance").get_to(data.instance);
    j.at("evse").get_to(data.evse);
  }
};


class VariableType {
public:
  std::string name;
  std::optional<std::string> instance;

  VariableType() = default;

  VariableType(const std::string& nameParam, const std::optional<std::string>& instanceParam = std::nullopt)
      : name(nameParam), instance(instanceParam) {}

  const std::string& getName() const {
    return name;
  }

  void setName(const std::string& newName) {
    name = newName;
  }

  const std::optional<std::string>& getInstance() const {
    return instance;
  }

  void setInstance(const std::optional<std::string>& newInstance) {
    instance = newInstance;
  }

  // JSON serialization functions
  friend void to_json(nlohmann::json& j, const VariableType& data) {
    j.emplace("name", data.name);
    if (data.instance.has_value()) {
      j.emplace("instance", data.instance.value());
    }
  }

  friend void from_json(const nlohmann::json& j, VariableType& data) {
    j.at("name").get_to(data.name);
    if (j.contains("instance")) {
      j.at("instance").get_to(data.instance.emplace());
    }
  }
};


class ComponentVariableType {
public:
  // Fields
  ComponentType component;        // Component for which a report of Variable is requested
  std::optional<VariableType> variable;  // Optional Variable(s) for which the report is requested

  // Constructors
  ComponentVariableType() = default;

  ComponentVariableType(const ComponentType& componentParam, const std::optional<VariableType>& variableParam = std::nullopt)
      : component(componentParam), variable(variableParam) {}

  // Getter and setter functions
  const ComponentType& getComponent() const {
    return component;
  }

  void setComponent(const ComponentType& newComponent) {
    component = newComponent;
  }

  const std::optional<VariableType>& getVariable() const {
    return variable;
  }

  void setVariable(const std::optional<VariableType>& newVariable) {
    variable = newVariable;
  }

  // JSON serialization functions
  friend void to_json(nlohmann::json& j, const ComponentVariableType& data) {
    j.emplace("component", data.component);
    if (data.variable.has_value()) {
      j.emplace("variable", data.variable.value());
    }
  }

  friend void from_json(const nlohmann::json& j, ComponentVariableType& data) {
    j.at("component").get_to(data.component);
    if (j.contains("variable")) {
      j.at("variable").get_to(data.variable.emplace());
    }
  }
};


class CompositeScheduleType {
public:
  // Fields
  int evseId;                                    // The ID of the EVSE for which the schedule is requested
  int duration;                                  // Duration of the schedule in seconds
  std::string scheduleStart;                     // Date and time at which the schedule becomes active
  ChargingRateUnitEnumType chargingRateUnit;    // The unit of measure Limit is expressed in
  std::vector<ChargingSchedulePeriodType> chargingSchedulePeriod;  // List of ChargingSchedulePeriod elements

  // Constructors
  CompositeScheduleType() = default;

  CompositeScheduleType(int evseIdParam, int durationParam, const std::string& scheduleStartParam,
                        ChargingRateUnitEnumType chargingRateUnitParam,
                        const std::vector<ChargingSchedulePeriodType>& chargingSchedulePeriodParam)
      : evseId(evseIdParam), duration(durationParam), scheduleStart(scheduleStartParam),
        chargingRateUnit(chargingRateUnitParam), chargingSchedulePeriod(chargingSchedulePeriodParam) {}

  // Getter and setter functions
  int getEvseId() const {
    return evseId;
  }

  void setEvseId(int newEvseId) {
    evseId = newEvseId;
  }

  int getDuration() const {
    return duration;
  }

  void setDuration(int newDuration) {
    duration = newDuration;
  }

  const std::string& getScheduleStart() const {
    return scheduleStart;
  }

  void setScheduleStart(const std::string& newScheduleStart) {
    scheduleStart = newScheduleStart;
  }

  ChargingRateUnitEnumType getChargingRateUnit() const {
    return chargingRateUnit;
  }

  void setChargingRateUnit(ChargingRateUnitEnumType newChargingRateUnit) {
    chargingRateUnit = newChargingRateUnit;
  }

  const std::vector<ChargingSchedulePeriodType>& getChargingSchedulePeriod() const {
    return chargingSchedulePeriod;
  }

  void setChargingSchedulePeriod(const std::vector<ChargingSchedulePeriodType>& newChargingSchedulePeriod) {
    chargingSchedulePeriod = newChargingSchedulePeriod;
  }

  // JSON serialization functions
  friend void to_json(nlohmann::json& j, const CompositeScheduleType& data) {
    j = nlohmann::json{
        {"evseId", data.evseId},
        {"duration", data.duration},
        {"scheduleStart", data.scheduleStart},
        {"chargingRateUnit", static_cast<int>(data.chargingRateUnit)},
        {"chargingSchedulePeriod", data.chargingSchedulePeriod}
    };
  }

  friend void from_json(const nlohmann::json& j, CompositeScheduleType& data) {
    j.at("evseId").get_to(data.evseId);
    j.at("duration").get_to(data.duration);
    j.at("scheduleStart").get_to(data.scheduleStart);
    j.at("chargingRateUnit").get_to(data.chargingRateUnit);
    j.at("chargingSchedulePeriod").get_to(data.chargingSchedulePeriod);
  }
};


class EventDataType {
public:
  // Fields
  int eventId;
  RFC3339DateTime timestamp;
  EventTriggerEnumType trigger;
  std::optional<int> cause;
  std::string actualValue;
  std::optional<std::string> techCode;
  std::optional<std::string> techInfo;
  std::optional<bool> cleared;
  std::optional<IdentifierString> transactionId;
  std::optional<int> variableMonitoringId;
  EventNotificationEnumType eventNotificationType;
  ComponentType component;
  VariableType variable;

  // Constructors
  EventDataType() = default;

  EventDataType(int eventIdParam, const RFC3339DateTime& timestampParam, EventTriggerEnumType triggerParam,
                const std::optional<int>& causeParam, const std::string& actualValueParam,
                const std::optional<std::string>& techCodeParam = std::nullopt,
                const std::optional<std::string>& techInfoParam = std::nullopt,
                const std::optional<bool>& clearedParam = std::nullopt,
                const std::optional<IdentifierString>& transactionIdParam = std::nullopt,
                const std::optional<int>& variableMonitoringIdParam = std::nullopt,
                EventNotificationEnumType eventNotificationTypeParam = EventNotificationEnumType::CustomMonitor,
                const ComponentType& componentParam = ComponentType(), const VariableType& variableParam = VariableType())
      : eventId(eventIdParam), timestamp(timestampParam), trigger(triggerParam),
        cause(causeParam), actualValue(actualValueParam), techCode(techCodeParam),
        techInfo(techInfoParam), cleared(clearedParam), transactionId(transactionIdParam),
        variableMonitoringId(variableMonitoringIdParam), eventNotificationType(eventNotificationTypeParam),
        component(componentParam), variable(variableParam) {}

  // Getter and setter functions for member variables

  int getEventId() const {
    return eventId;
  }

  void setEventId(int newEventId) {
    eventId = newEventId;
  }

  const RFC3339DateTime& getTimestamp() const {
    return timestamp;
  }

  void setTimestamp(const RFC3339DateTime& newTimestamp) {
    timestamp = newTimestamp;
  }

  EventTriggerEnumType getTrigger() const {
    return trigger;
  }

  void setTrigger(EventTriggerEnumType newTrigger) {
    trigger = newTrigger;
  }

  const std::optional<int>& getCause() const {
    return cause;
  }

  void setCause(const std::optional<int>& newCause) {
    cause = newCause;
  }

  const std::string& getActualValue() const {
    return actualValue;
  }

  void setActualValue(const std::string& newActualValue) {
    actualValue = newActualValue;
  }

  const std::optional<std::string>& getTechCode() const {
    return techCode;
  }

  void setTechCode(const std::optional<std::string>& newTechCode) {
    techCode = newTechCode;
  }

  const std::optional<std::string>& getTechInfo() const {
    return techInfo;
  }

  void setTechInfo(const std::optional<std::string>& newTechInfo) {
    techInfo = newTechInfo;
  }

  const std::optional<bool>& getCleared() const {
    return cleared;
  }

  void setCleared(const std::optional<bool>& newCleared) {
    cleared = newCleared;
  }

  const std::optional<IdentifierString>& getTransactionId() const {
    return transactionId;
  }

  void setTransactionId(const std::optional<IdentifierString>& newTransactionId) {
    transactionId = newTransactionId;
  }

  const std::optional<int>& getVariableMonitoringId() const {
    return variableMonitoringId;
  }

  void setVariableMonitoringId(const std::optional<int>& newVariableMonitoringId) {
    variableMonitoringId = newVariableMonitoringId;
  }

  EventNotificationEnumType getEventNotificationType() const {
    return eventNotificationType;
  }

  void setEventNotificationType(EventNotificationEnumType newEventNotificationType) {
    eventNotificationType = newEventNotificationType;
  }

  const ComponentType& getComponent() const {
    return component;
  }

  void setComponent(const ComponentType& newComponent) {
    component = newComponent;
  }

  const VariableType& getVariable() const {
    return variable;
  }

  void setVariable(const VariableType& newVariable) {
    variable = newVariable;
  }



  friend void to_json(nlohmann::json& j, const EventDataType& data) {
    j.emplace("eventId", data.eventId);
    j.emplace("timestamp", data.timestamp);
    j.emplace("trigger", magic_enum::enum_name(data.trigger));
    if (data.cause.has_value()) {
      j.emplace("cause", data.cause.value());
    }
    j.emplace("actualValue", data.actualValue);
    if (data.techCode.has_value()) {
      j.emplace("techCode", data.techCode.value());
    }
    if (data.cleared.has_value()) {
      j.emplace("cleared",data.cleared.value());
    }
    if (data.techInfo.has_value()) {
      j.emplace("techInfo", data.techInfo.value());
    }
    if (data.transactionId.has_value()) {
      j.emplace("transactionId", data.transactionId.value());
    }
    if (data.variableMonitoringId.has_value()) {
      j.emplace("variableMonitoringId", data.variableMonitoringId.value());
    }

    j.emplace("eventNotificationType", magic_enum::enum_name(data.eventNotificationType));
    j.emplace("component", data.component);

    j.emplace("variable", data.variable);
  }

  friend void from_json(const nlohmann::json& j, EventDataType& data) {
    if (j.contains("eventId") && j.at("eventId").is_number_integer()) {
      j.at("eventId").get_to(data.eventId);
    }
    if (j.contains("timestamp") && j.at("timestamp").is_string()) {
      data.timestamp = j.at("timestamp");
    }
    if (j.contains("trigger") &&  j.at("trigger").is_string()) {
      auto tmp = magic_enum::enum_cast<EventTriggerEnumType>(j.at("trigger"));
      if (tmp.has_value()) {
        data.trigger = tmp.value();
      } else {
        data.trigger = EventTriggerEnumType::Alerting;
      }
    }

    if (j.contains("cause") && j.at("cause").is_number_integer()) {
      j.at("cause").get_to(data.cause.emplace());
    }

    if (j.contains("acturalValue") && j.at("actualValue").is_string()) {
      j.at("actualValue").get_to(data.actualValue);
    }
    if (j.contains("techCode") && j.at("techCode").is_string()) {
      j.at("techCode").get_to(data.techCode.emplace());
    }
    if (j.contains("transactionId") && j.at("transactionId").is_string()) {
      j.at("transactionId").get_to(data.transactionId.emplace());
    }

    if (j.contains("variableMonitoringId") && j.at("variableMonitoringId").is_number_integer()) {
      j.at("variableMonitoringId").get_to(data.variableMonitoringId.emplace());
    }

    if (j.contains("eventNotificationType") && j.at("eventNotificationType").is_string()) {
      auto tmp = magic_enum::enum_cast<EventNotificationEnumType>(j.at("eventNotificationType"));
      if (tmp.has_value()) {
        data.eventNotificationType = tmp.value();
      }
    }

    if (j.contains("component") && j.at("component").is_object()) {
      j.at("component").get_to(data.component);
    }
    if (j.contains("variable") && j.at("variable").is_object()) {
      j.at("variable").get_to(data.variable);
    }

  }
};


class FirmwareType {
public:
  // Fields
  std::string location;
  RFC3339DateTime retrieveDateTime;
  std::optional<RFC3339DateTime> installDateTime;
  std::optional<std::string> signingCertificate;
  std::optional<std::string> signature;

  // Constructors
  FirmwareType() = default;

  FirmwareType(const std::string& locationParam,
               const RFC3339DateTime& retrieveDateTimeParam,
               const std::optional<RFC3339DateTime>& installDateTimeParam = std::nullopt,
               const std::optional<std::string>& signingCertificateParam = std::nullopt,
               const std::optional<std::string>& signatureParam = std::nullopt)
      : location(locationParam),
        retrieveDateTime(retrieveDateTimeParam),
        installDateTime(installDateTimeParam),
        signingCertificate(signingCertificateParam),
        signature(signatureParam) {}

  // Getter and setter functions for member variables
  const std::string& getLocation() const {
    return location;
  }

  void setLocation(const std::string& newLocation) {
    location = newLocation;
  }

  const RFC3339DateTime& getRetrieveDateTime() const {
    return retrieveDateTime;
  }

  void setRetrieveDateTime(const RFC3339DateTime& newRetrieveDateTime) {
    retrieveDateTime = newRetrieveDateTime;
  }

  const std::optional<RFC3339DateTime>& getInstallDateTime() const {
    return installDateTime;
  }

  void setInstallDateTime(const std::optional<RFC3339DateTime>& newInstallDateTime) {
    installDateTime = newInstallDateTime;
  }

  const std::optional<std::string>& getSigningCertificate() const {
    return signingCertificate;
  }

  void setSigningCertificate(const std::optional<std::string>& newSigningCertificate) {
    signingCertificate = newSigningCertificate;
  }

  const std::optional<std::string>& getSignature() const {
    return signature;
  }

  void setSignature(const std::optional<std::string>& newSignature) {
    signature = newSignature;
  }

  friend void to_json(nlohmann::json& j, const FirmwareType& data) {
    j = nlohmann::json{
        {"location", data.location},
        {"retrieveDateTime", data.retrieveDateTime}
    };
    if (data.installDateTime) {
      j.emplace("installDateTime", data.installDateTime.value());
    }
    if (data.signingCertificate) {
      j.emplace("signingCertificate", data.signingCertificate.value());
    }
    if (data.signature) {
      j.emplace("signature", data.signature.value());
    }
  }

  friend void from_json(const nlohmann::json& j, FirmwareType& data) {
    j.at("location").get_to(data.location);
    j.at("retrieveDateTime").get_to(data.retrieveDateTime);

    if (j.contains("installDateTime")) {
      j.at("installDateTime").get_to(data.installDateTime.emplace());
    }
    if (j.contains("signingCertificate")) {
      j.at("signingCertificate").get_to(data.signingCertificate.emplace());
    }
    if (j.contains("signature")) {
      j.at("signature").get_to(data.signature.emplace());
    }
  }
};


class GetVariableDataType {
public:
  // Fields
  std::optional<AttributeEnumType> attributeType;
  ComponentType component;
  VariableType variable;

  // Constructors
  GetVariableDataType() = default;

  GetVariableDataType(const ComponentType& componentParam,
                      const VariableType& variableParam,
                      const std::optional<AttributeEnumType>& attributeTypeParam = std::nullopt)
      : component(componentParam),
        variable(variableParam),
        attributeType(attributeTypeParam) {}

  // Getter and setter functions for member variables
  const std::optional<AttributeEnumType>& getAttributeType() const {
    return attributeType;
  }

  void setAttributeType(const std::optional<AttributeEnumType>& newAttributeType) {
    attributeType = newAttributeType;
  }

  const ComponentType& getComponent() const {
    return component;
  }

  void setComponent(const ComponentType& newComponent) {
    component = newComponent;
  }

  const VariableType& getVariable() const {
    return variable;
  }

  void setVariable(const VariableType& newVariable) {
    variable = newVariable;
  }

  friend void to_json(nlohmann::json& j, const GetVariableDataType& data) {
    j = nlohmann::json{
        {"component", data.component},
        {"variable", data.variable}
    };
    if (data.attributeType) {
      j["attributeType"] = magic_enum::enum_name(data.attributeType.value());
    }
  }

  friend void from_json(const nlohmann::json& j, GetVariableDataType& data) {
    j.at("component").get_to(data.component);
    j.at("variable").get_to(data.variable);
    if (j.contains("attributeType")) {
      auto attr_type = magic_enum::enum_cast<AttributeEnumType>(j.at("attributeType").get<std::string>());
      if (attr_type.has_value()) {
        data.attributeType = attr_type.value();
      }
    }
  }
};


class GetVariableResultType {
public:
  // Fields
  GetVariableStatusEnumType attributeStatus;
  std::optional<AttributeEnumType> attributeType;
  std::optional<std::string> attributeValue;
  ComponentType component;
  VariableType variable;
  std::optional<StatusInfoType> attributeStatusInfo;

  // Constructors
  GetVariableResultType() = default;

  GetVariableResultType(const GetVariableStatusEnumType& attributeStatusParam,
                        const ComponentType& componentParam,
                        const VariableType& variableParam,
                        const std::optional<AttributeEnumType>& attributeTypeParam = std::nullopt,
                        const std::optional<std::string>& attributeValueParam = std::nullopt,
                        const std::optional<StatusInfoType>& attributeStatusInfoParam = std::nullopt)
      : attributeStatus(attributeStatusParam),
        component(componentParam),
        variable(variableParam),
        attributeType(attributeTypeParam),
        attributeValue(attributeValueParam),
        attributeStatusInfo(attributeStatusInfoParam) {}

  // Getter and setter functions for member variables
  GetVariableStatusEnumType getAttributeStatus() const {
    return attributeStatus;
  }

  void setAttributeStatus(GetVariableStatusEnumType newAttributeStatus) {
    attributeStatus = newAttributeStatus;
  }

  const std::optional<AttributeEnumType>& getAttributeType() const {
    return attributeType;
  }

  void setAttributeType(const std::optional<AttributeEnumType>& newAttributeType) {
    attributeType = newAttributeType;
  }

  const std::optional<std::string>& getAttributeValue() const {
    return attributeValue;
  }

  void setAttributeValue(const std::optional<std::string>& newAttributeValue) {
    attributeValue = newAttributeValue;
  }

  const ComponentType& getComponent() const {
    return component;
  }

  void setComponent(const ComponentType& newComponent) {
    component = newComponent;
  }

  const VariableType& getVariable() const {
    return variable;
  }

  void setVariable(const VariableType& newVariable) {
    variable = newVariable;
  }

  const std::optional<StatusInfoType>& getAttributeStatusInfo() const {
    return attributeStatusInfo;
  }

  void setAttributeStatusInfo(const std::optional<StatusInfoType>& newAttributeStatusInfo) {
    attributeStatusInfo = newAttributeStatusInfo;
  }

  friend void to_json(nlohmann::json& j, const GetVariableResultType& data) {
    j = nlohmann::json{
        {"attributeStatus", magic_enum::enum_name(data.attributeStatus)},
        {"component", data.component},
        {"variable", data.variable}
    };
    if (data.attributeType) {
      j["attributeType"] = magic_enum::enum_name(data.attributeType.value());
    }
    if (data.attributeValue) {
      j["attributeValue"] = data.attributeValue.value();
    }
    if (data.attributeStatusInfo) {
      j["attributeStatusInfo"] = data.attributeStatusInfo.value();
    }
  }

  friend void from_json(const nlohmann::json& j, GetVariableResultType& data) {
    auto attr_status = magic_enum::enum_cast<GetVariableStatusEnumType>(j.at("attributeStatus").get<std::string>());
    if (attr_status.has_value()) {
      data.attributeStatus = attr_status.value();
    }

    j.at("component").get_to(data.component);
    j.at("variable").get_to(data.variable);

    if (j.contains("attributeType")) {
      auto attr_type = magic_enum::enum_cast<AttributeEnumType>(j.at("attributeType").get<std::string>());
      if (attr_type.has_value()) {
        data.attributeType = attr_type.value();
      }
    }
    if (j.contains("attributeValue")) {
      j.at("attributeValue").get_to(data.attributeValue.emplace());
    }
    if (j.contains("attributeStatusInfo")) {
      j.at("attributeStatusInfo").get_to(data.attributeStatusInfo.emplace());
    }
  }
};


class LogParametersType {
public:
  // Fields
  std::string remoteLocation;
  std::optional<RFC3339DateTime> oldestTimestamp;
  std::optional<RFC3339DateTime> latestTimestamp;

  // Constructors
  LogParametersType() = default;

  LogParametersType(const std::string& remoteLocationParam,
                    const std::optional<RFC3339DateTime>& oldestTimestampParam = std::nullopt,
                    const std::optional<RFC3339DateTime>& latestTimestampParam = std::nullopt)
      : remoteLocation(remoteLocationParam),
        oldestTimestamp(oldestTimestampParam),
        latestTimestamp(latestTimestampParam) {}

  // Getter and setter functions for member variables. Add getters and setters here

  friend void to_json(nlohmann::json& j, const LogParametersType& data) {
    j = nlohmann::json{
        {"remoteLocation", data.remoteLocation}
    };
    if (data.oldestTimestamp) {
      j["oldestTimestamp"] = data.oldestTimestamp.value();
    }
    if (data.latestTimestamp) {
      j["latestTimestamp"] = data.latestTimestamp.value();
    }
  }

  friend void from_json(const nlohmann::json& j, LogParametersType& data) {
    j.at("remoteLocation").get_to(data.remoteLocation);
    if (j.contains("oldestTimestamp")) {
      data.oldestTimestamp = j.at("oldestTimestamp");
    }
    if (j.contains("latestTimestamp")) {
      data.latestTimestamp = j.at("latestTimestamp");
    }
  }
};



class MessageInfoType {
public:
  // Fields
  int id;
  MessagePriorityEnumType priority;
  std::optional<MessageStateEnumType> state;
  std::optional<RFC3339DateTime> startDateTime;
  std::optional<RFC3339DateTime> endDateTime;
  std::optional<IdentifierString> transactionId;
  MessageContentType message;
  std::optional<ComponentType> display;

  // Constructors
  MessageInfoType() = default;

  MessageInfoType(int idParam, const MessagePriorityEnumType& priorityParam,
                  const MessageContentType& messageParam,
                  const std::optional<MessageStateEnumType>& stateParam = std::nullopt,
                  const std::optional<RFC3339DateTime>& startDateTimeParam = std::nullopt,
                  const std::optional<RFC3339DateTime>& endDateTimeParam = std::nullopt,
                  const std::optional<IdentifierString>& transactionIdParam = std::nullopt,
                  const std::optional<ComponentType>& displayParam = std::nullopt)
      : id(idParam), priority(priorityParam), state(stateParam),
        startDateTime(startDateTimeParam), endDateTime(endDateTimeParam),
        transactionId(transactionIdParam), message(messageParam), display(displayParam) {}

  // Getter and setter functions for member variables
  int getId() const {
    return id;
  }

  void setId(int newId) {
    id = newId;
  }

  MessagePriorityEnumType getPriority() const {
    return priority;
  }

  void setPriority(MessagePriorityEnumType newPriority) {
    priority = newPriority;
  }

  const std::optional<MessageStateEnumType>& getState() const {
    return state;
  }

  void setState(const std::optional<MessageStateEnumType>& newState) {
    state = newState;
  }

  const std::optional<RFC3339DateTime>& getStartDateTime() const {
    return startDateTime;
  }

  void setStartDateTime(const std::optional<RFC3339DateTime>& newStartDateTime) {
    startDateTime = newStartDateTime;
  }

  const std::optional<RFC3339DateTime>& getEndDateTime() const {
    return endDateTime;
  }

  void setEndDateTime(const std::optional<RFC3339DateTime>& newEndDateTime) {
    endDateTime = newEndDateTime;
  }

  const std::optional<IdentifierString>& getTransactionId() const {
    return transactionId;
  }

  void setTransactionId(const std::optional<IdentifierString>& newTransactionId) {
    transactionId = newTransactionId;
  }

  const MessageContentType& getMessage() const {
    return message;
  }

  void setMessage(const MessageContentType& newMessage) {
    message = newMessage;
  }

  const std::optional<ComponentType>& getDisplay() const {
    return display;
  }

  void setDisplay(const std::optional<ComponentType>& newDisplay) {
    display = newDisplay;
  }

  // JSON serialization functions
  friend void to_json(nlohmann::json& j, const MessageInfoType& data) {
    j = nlohmann::json{
        {"id", data.id},
        {"priority", magic_enum::enum_name(data.priority)},
        {"message", data.message}
        // Include other fields here
    };
    if (data.state.has_value()) {
      j["state"] = magic_enum::enum_name(data.state.value());
    }
    if (data.startDateTime.has_value()) {
      j["startDateTime"] = data.startDateTime.value().toString();
    }
    if (data.endDateTime.has_value()) {
      j["endDateTime"] = data.endDateTime.value().toString();
    }
    if (data.transactionId.has_value()) {
      j["transactionId"] = data.transactionId.value();
    }
    if (data.display.has_value()) {
      j["display"] = data.display.value();
    }
  }

  friend void from_json(const nlohmann::json& j, MessageInfoType& data) {
    data.setId(j.at("id").get<int>());
    data.setPriority(magic_enum::enum_cast<MessagePriorityEnumType>(j.at("priority").get<std::string>()).value());

    if (j.contains("state")) {
      data.setState(magic_enum::enum_cast<MessageStateEnumType>(j.at("state").get<std::string>()));
    }

    if (j.contains("startDateTime")) {
      j.at("startDateTime").get_to(data.startDateTime.emplace());
    }

    if (j.contains("endDateTime")) {
      j.at("endDateTime").get_to(data.endDateTime.emplace());
    }

    if (j.contains("transactionId")) {
      j.at("transactionId").get_to(data.transactionId.emplace());
    }

    j.at("message").get_to(data.message);

    if (j.contains("display")) {
      j.at("display").get_to(data.display.emplace());
    }
  }
};

class SignedMeterValueType {
private:
  std::string signedMeterData;
  std::string signingMethod;
  std::string encodingMethod;
  std::string publicKey;

public:
  SignedMeterValueType() = default;

  SignedMeterValueType(const std::string& signedMeterDataParam, const std::string& signingMethodParam,
                       const std::string& encodingMethodParam, const std::string& publicKeyParam)
      : signedMeterData(signedMeterDataParam), signingMethod(signingMethodParam),
        encodingMethod(encodingMethodParam), publicKey(publicKeyParam) {}

  // Getter and setter functions
  const std::string& getSignedMeterData() const {
    return signedMeterData;
  }

  void setSignedMeterData(const std::string& newSignedMeterData) {
    signedMeterData = newSignedMeterData;
  }

  const std::string& getSigningMethod() const {
    return signingMethod;
  }

  void setSigningMethod(const std::string& newSigningMethod) {
    signingMethod = newSigningMethod;
  }

  const std::string& getEncodingMethod() const {
    return encodingMethod;
  }

  void setEncodingMethod(const std::string& newEncodingMethod) {
    encodingMethod = newEncodingMethod;
  }

  const std::string& getPublicKey() const {
    return publicKey;
  }

  void setPublicKey(const std::string& newPublicKey) {
    publicKey = newPublicKey;
  }

  friend void to_json(nlohmann::json& j, const SignedMeterValueType& data) {
    j = nlohmann::json{
        {"signedMeterData", data.getSignedMeterData()},
        {"signingMethod", data.getSigningMethod()},
        {"encodingMethod", data.getEncodingMethod()},
        {"publicKey", data.getPublicKey()}
    };
  }

  friend void from_json(const nlohmann::json& j, SignedMeterValueType& data) {
    // Implement logic to deserialize SignedMeterValueType from JSON object
    try {
      data.setSignedMeterData(j.at("signedMeterData").get<std::string>());
      data.setSigningMethod(j.at("signingMethod").get<std::string>());
      data.setEncodingMethod(j.at("encodingMethod").get<std::string>());
      data.setPublicKey(j.at("publicKey").get<std::string>());
    } catch (const nlohmann::json::exception& e) {
      std::cerr << "Error parsing SignedMeterValueType JSON: " << e.what() << std::endl;
    }
  }
};

class UnitOfMeasureType {
private:
  std::string unit;
  int multiplier;

public:
  UnitOfMeasureType() : multiplier(0) {}

  UnitOfMeasureType(const std::string& unitParam, int multiplierParam = 0)
      : unit(unitParam), multiplier(multiplierParam) {}

  // Getter and setter functions
  const std::string& getUnit() const {
    return unit;
  }

  void setUnit(const std::string& newUnit) {
    unit = newUnit;
  }

  int getMultiplier() const {
    return multiplier;
  }

  void setMultiplier(int newMultiplier) {
    multiplier = newMultiplier;
  }

  friend void to_json(nlohmann::json& j, const UnitOfMeasureType& data) {
    j = nlohmann::json{
        {"unit", data.getUnit()},
        {"multiplier", data.getMultiplier()}
    };
  }

  friend void from_json(const nlohmann::json& j, UnitOfMeasureType& data) {
    data.setUnit(j.at("unit").get<std::string>());
    data.setMultiplier(j.at("multiplier").get<int>());
  }
};


class SampledValueType {
private:
  double value;
  std::optional<ReadingContextEnumType> context;
  std::optional<MeasurandEnumType> measurand;
  std::optional<PhaseEnumType> phase;
  std::optional<LocationEnumType> location;
  std::optional<SignedMeterValueType> signedMeterValue;
  std::optional<UnitOfMeasureType> unitOfMeasure;

public:
  SampledValueType() = default;

  SampledValueType(double value,
                   const std::optional<ReadingContextEnumType> &context = std::nullopt,
                   const std::optional<MeasurandEnumType> &measurand = std::nullopt,
                   const std::optional<PhaseEnumType> &phase = std::nullopt,
                   const std::optional<LocationEnumType> &location = std::nullopt,
                   const std::optional<SignedMeterValueType> &signedMeterValue = std::nullopt,
                   const std::optional<UnitOfMeasureType> &unitOfMeasure = std::nullopt)
      : value(value), context(context), measurand(measurand), phase(phase),
        location(location), signedMeterValue(signedMeterValue),
        unitOfMeasure(unitOfMeasure) {}

  // Getter and setter functions
  double getValue() const { return value; }

  void setValue(double newValue) { value = newValue; }

  const std::optional<ReadingContextEnumType> &getContext() const {
    return context;
  }

  void setContext(const std::optional<ReadingContextEnumType> &newContext) {
    context = newContext;
  }

  const std::optional<MeasurandEnumType> &getMeasurand() const {
    return measurand;
  }

  void setMeasurand(const std::optional<MeasurandEnumType> &newMeasurand) {
    measurand = newMeasurand;
  }

  const std::optional<PhaseEnumType> &getPhase() const { return phase; }

  void setPhase(const std::optional<PhaseEnumType> &newPhase) {
    phase = newPhase;
  }

  const std::optional<LocationEnumType> &getLocation() const {
    return location;
  }

  void setLocation(const std::optional<LocationEnumType> &newLocation) {
    location = newLocation;
  }

  const std::optional<SignedMeterValueType> &getSignedMeterValue() const {
    return signedMeterValue;
  }

  void setSignedMeterValue(
      const std::optional<SignedMeterValueType> &newSignedMeterValue) {
    signedMeterValue = newSignedMeterValue;
  }

  const std::optional<UnitOfMeasureType> &getUnitOfMeasure() const {
    return unitOfMeasure;
  }

  void
  setUnitOfMeasure(const std::optional<UnitOfMeasureType> &newUnitOfMeasure) {
    unitOfMeasure = newUnitOfMeasure;
  }

  friend void to_json(nlohmann::json& j, const SampledValueType& data) {
    j = nlohmann::json{
        {"value", data.getValue()}
        // Include other fields here
    };
    if (data.getContext().has_value()) {
      j["context"] = magic_enum::enum_name(data.getContext().value());
    }
    if (data.getMeasurand().has_value()) {
      j["measurand"] = magic_enum::enum_name(data.getMeasurand().value());
    }
  }

  friend void from_json(const nlohmann::json& j, SampledValueType& data) {
    data.setValue(j.at("value").get<double>());
    if (j.contains("context")) {
      auto tmp = magic_enum::enum_cast<ReadingContextEnumType>(j.at("context").get<std::string>());
      if (tmp.has_value()) {
        data.setContext(tmp);
      }
    }
    if (j.contains("measurand")) {
      auto tmp = magic_enum::enum_cast<MeasurandEnumType>(j.at("measurand").get<std::string>());
      if (tmp.has_value()) {
        data.setMeasurand(tmp);
      }
    }
  }
};



class MeterValueType {
private:
  RFC3339DateTime timestamp;
  std::vector<SampledValueType> sampledValues;

public:
  MeterValueType() = default;

  MeterValueType(const RFC3339DateTime& timestamp, const std::vector<SampledValueType>& sampledValues)
      : timestamp(timestamp), sampledValues(sampledValues) {}

  // Getter and setter functions
  const RFC3339DateTime& getTimestamp() const {
    return timestamp;
  }

  void setTimestamp(const RFC3339DateTime& newTimestamp) {
    timestamp = newTimestamp;
  }

  const std::vector<SampledValueType>& getSampledValues() const {
    return sampledValues;
  }

  void setSampledValues(const std::vector<SampledValueType>& newSampledValues) {
    sampledValues = newSampledValues;
  }

  friend void to_json(nlohmann::json& j, const MeterValueType& data) {
    j = nlohmann::json{
        {"timestamp", data.timestamp},
        {"sampledValue", data.sampledValues}
    };
  }

  friend void from_json(const nlohmann::json& j, MeterValueType& data) {
    j.at("timestamp").get_to(data.timestamp);
    j.at("sampledValue").get_to(data.sampledValues);
  }
};


class VariableMonitoringType {
private:
  int id;
  bool transaction;
  double value;
  MonitorEnumType type;
  int severity;

public:
  VariableMonitoringType() = default;

  explicit VariableMonitoringType(
      int id_param,
      bool transaction_param,
      double value_param,
      MonitorEnumType type_param,
      int severity_param
  )
      : id(id_param),
        transaction(transaction_param),
        value(value_param),
        type(type_param),
        severity(severity_param) { }

  // Getters
  [[nodiscard]] int getId() const { return id; }
  [[nodiscard]] bool getTransaction() const { return transaction; }
  [[nodiscard]] double getValue() const { return value; }
  [[nodiscard]] MonitorEnumType getType() const { return type; }
  [[nodiscard]] int getSeverity() const { return severity; }

  // Setters
  void setId(int new_id) { id = new_id; }
  void setTransaction(bool new_transaction) { transaction = new_transaction; }
  void setValue(double new_value) { value = new_value; }
  void setType(MonitorEnumType new_type) { type = new_type; }
  void setSeverity(int new_severity) { severity = new_severity; }

  // Function to convert class object to json
  friend void to_json(nlohmann::json& j , const VariableMonitoringType& obj) {
    j = nlohmann::json{
        {"id", obj.getId()},
        {"transaction", obj.getTransaction()},
        {"value", obj.getValue()},
        {"type", magic_enum::enum_name(obj.getType())},
        {"severity", obj.getSeverity()}
    };
  }

  // Function to convert json to class object
  friend void from_json(const nlohmann::json& j, VariableMonitoringType& obj) {
    obj.setId(j.at("id").get<int>());
    obj.setTransaction(j.at("transaction").get<bool>());
    obj.setValue(j.at("value").get<double>());
    auto tmp = magic_enum::enum_cast<MonitorEnumType>(j.at("type").get<std::string>());
    if(tmp.has_value()) {
      obj.setType(tmp.value());
    }
    obj.setSeverity(j.at("severity").get<int>());
  }
};


class MonitoringDataType {
private:
  ComponentType component;
  VariableType variable;
  std::vector<VariableMonitoringType> variableMonitoring;

public:
  MonitoringDataType() = default;

  explicit MonitoringDataType(
      const ComponentType& component_param,
      const VariableType& variable_param,
      const std::vector<VariableMonitoringType>& variable_monitoring_param
  )
      : component(component_param),
        variable(variable_param),
        variableMonitoring(variable_monitoring_param) {}

  // Getters
  [[nodiscard]] const ComponentType& getComponent() const { return component; }
  [[nodiscard]] const VariableType& getVariable() const { return variable; }
  [[nodiscard]] const std::vector<VariableMonitoringType>& getVariableMonitoring() const { return variableMonitoring; }

  // Setters
  void setComponent(const ComponentType& new_component) { component = new_component; }
  void setVariable(const VariableType& new_variable) { variable = new_variable; }
  void setVariableMonitoring(const std::vector<VariableMonitoringType>& new_variable_monitoring) {
    variableMonitoring = new_variable_monitoring;
  }

  // Function to convert class object to json
  friend void to_json(nlohmann::json& j , const MonitoringDataType& obj) {
    j = nlohmann::json{
        {"component", obj.getComponent()},                        // Assumes to_json() is defined for ComponentType
        {"variable", obj.getVariable()},                          // Assumes to_json() is defined for VariableType
        {"variableMonitoring", obj.getVariableMonitoring()}       // Assumes to_json() is defined for VariableMonitoringType
    };
  }

  // Function to convert json to class object
  friend void from_json(const nlohmann::json& j, MonitoringDataType& obj) {
    obj.setComponent(j.at("component").get<ComponentType>());
    obj.setVariable(j.at("variable").get<VariableType>());
    obj.setVariableMonitoring(j.at("variableMonitoring").get<std::vector<VariableMonitoringType>>());
  }
};


class VPNType {
private:
  std::string server;
  std::string user;
  std::optional<std::string> group;
  std::string password;
  std::string key;
  VPNEnumType type;

public:
  VPNType() = default;

  explicit VPNType(
      const std::string& serverParam,
      const std::string& userParam,
      const std::string& passwordParam,
      const std::string& keyParam,
      VPNEnumType typeParam,
      const std::optional<std::string>& groupParam = std::nullopt
  )
      : server(serverParam),
        user(userParam),
        password(passwordParam),
        key(keyParam),
        type(typeParam),
        group(groupParam) {}

  // Getters
  [[nodiscard]] std::string getServer() const { return server; }
  [[nodiscard]] std::string getUser() const { return user; }
  [[nodiscard]] std::optional<std::string> getGroup() const { return group; }
  [[nodiscard]] std::string getPassword() const { return password; }
  [[nodiscard]] std::string getKey() const { return key; }
  [[nodiscard]] VPNEnumType getType() const { return type; }

  // Setters
  void setServer(const std::string& newServer) { server = newServer; }
  void setUser(const std::string& newUser) { user = newUser; }
  void setGroup(const std::string& newGroup) { group = newGroup; }
  void setPassword(const std::string& newPassword) { password = newPassword; }
  void setKey(const std::string& newKey) { key = newKey; }
  void setType(VPNEnumType newType) { type = newType; }

  // Function to convert class object to json
  friend void to_json(nlohmann::json& j , const VPNType& obj) {
    j = nlohmann::json{
        {"server", obj.getServer()},
        {"user", obj.getUser()},
        {"password", obj.getPassword()},
        {"key", obj.getKey()},
        {"type", magic_enum::enum_name(obj.getType())},
    };

    if(obj.getGroup().has_value())
      j["group"] = obj.getGroup().value();
  }

  // Function to convert json to class object
  friend void from_json(const nlohmann::json& j, VPNType& obj) {
    obj.setServer(j.at("server").get<std::string>());
    obj.setUser(j.at("user").get<std::string>());
    obj.setPassword(j.at("password").get<std::string>());
    obj.setKey(j.at("key").get<std::string>());
    obj.setType(magic_enum::enum_cast<VPNEnumType>(j.at("type").get<std::string>()).value_or(VPNEnumType::IKEv2));

    if(j.contains("group"))
      obj.setGroup(j.at("group").get<std::string>());
  }
};

class NetworkConnectionProfileType {
private:
  OCPPVersionEnumType ocppVersion;
  OCPPTransportEnumType ocppTransport;
  std::string ocppCsmsUrl;
  int messageTimeout;
  int securityProfile;
  OCPPInterfaceEnumType ocppInterface;
  std::optional<VPNType> vpn;
  std::optional<APNType> apn;

public:
  NetworkConnectionProfileType() = default;

  explicit NetworkConnectionProfileType(
      OCPPVersionEnumType ocppVersionParam,
      OCPPTransportEnumType ocppTransportParam,
      const std::string& ocppCsmsUrlParam,
      int messageTimeoutParam,
      int securityProfileParam,
      OCPPInterfaceEnumType ocppInterfaceParam,
      const std::optional<VPNType>& vpnParam = std::nullopt,
      const std::optional<APNType>& apnParam = std::nullopt
  )
      : ocppVersion(ocppVersionParam),
        ocppTransport(ocppTransportParam),
        ocppCsmsUrl(ocppCsmsUrlParam),
        messageTimeout(messageTimeoutParam),
        securityProfile(securityProfileParam),
        ocppInterface(ocppInterfaceParam),
        vpn(vpnParam),
        apn(apnParam) {}

  // Getters
  [[nodiscard]] OCPPVersionEnumType getOCPPVersion() const { return ocppVersion; }
  [[nodiscard]] OCPPTransportEnumType getOCPPTransport() const { return ocppTransport; }
  [[nodiscard]] std::string getOCPPCsmsUrl() const { return ocppCsmsUrl; }
  [[nodiscard]] int getMessageTimeout() const { return messageTimeout; }
  [[nodiscard]] int getSecurityProfile() const { return securityProfile; }
  [[nodiscard]] OCPPInterfaceEnumType getOCPPInterface() const { return ocppInterface; }
  [[nodiscard]] std::optional<VPNType> getVPN() const { return vpn; }
  [[nodiscard]] std::optional<APNType> getAPN() const { return apn; }

  // Setters
  void setOCPPVersion(OCPPVersionEnumType newOCPPVersion) { ocppVersion = newOCPPVersion; }
  void setOCPPTransport(OCPPTransportEnumType newOCPPTransport) { ocppTransport = newOCPPTransport; }
  void setOCPPCsmsUrl(const std::string& newOCPPCsmsUrl) { ocppCsmsUrl = newOCPPCsmsUrl; }
  void setMessageTimeout(int newMessageTimeout) { messageTimeout = newMessageTimeout; }
  void setSecurityProfile(int newSecurityProfile) { securityProfile = newSecurityProfile; }
  void setOCPPInterface(OCPPInterfaceEnumType newOCPPInterface) { ocppInterface = newOCPPInterface; }
  void setVPN(const VPNType& newVPN) { vpn = newVPN; }
  void setAPN(const APNType& newAPN) { apn = newAPN; }

  // to_json method;
  friend void to_json(nlohmann::json &j, const NetworkConnectionProfileType &v) {
    j = nlohmann::json{
        {"ocppVersion", magic_enum::enum_name(v.getOCPPVersion())},
        {"ocppTransport", magic_enum::enum_name(v.getOCPPTransport())},
        {"ocppCsmsUrl", v.getOCPPCsmsUrl()},
        {"messageTimeout", v.getMessageTimeout()},
        {"securityProfile", v.getSecurityProfile()},
        {"ocppInterface", magic_enum::enum_name(v.getOCPPInterface())},
    };

    if(v.getVPN().has_value())
      j["vpn"] = v.getVPN().value();

    if(v.getAPN().has_value())
      j["apn"] = v.getAPN().value();
  }

  // from_json method;
  friend void from_json(const nlohmann::json &j, NetworkConnectionProfileType &v) {
    v.setOCPPVersion(magic_enum::enum_cast<OCPPVersionEnumType>(j.at("ocppVersion").get<std::string>()).value_or(OCPPVersionEnumType::OCPP20));
    v.setOCPPTransport(magic_enum::enum_cast<OCPPTransportEnumType>(j.at("ocppTransport").get<std::string>()).value_or(OCPPTransportEnumType::JSON));
    v.setOCPPCsmsUrl(j.at("ocppCsmsUrl").get<std::string>());
    v.setMessageTimeout(j.at("messageTimeout").get<int>());
    v.setSecurityProfile(j.at("securityProfile").get<int>());
    v.setOCPPInterface(magic_enum::enum_cast<OCPPInterfaceEnumType>(j.at("ocppInterface").get<std::string>()).value_or(OCPPInterfaceEnumType::Wired0));

    if(j.contains("vpn"))
      j.at("vpn").get_to(v.getVPN().emplace());

    if(j.contains("apn"))
      j.at("apn").get_to(v.getAPN().emplace());
  }
};

class OCSPRequestDataType {
private:
  HashAlgorithmEnumType hashAlgorithm;
  IdentifierString issuerNameHash;
  std::string issuerKeyHash;
  IdentifierString serialNumber;
  std::string responderURL;

public:
  OCSPRequestDataType() = default;

  explicit OCSPRequestDataType(
      HashAlgorithmEnumType hashAlgorithmParam,
      const IdentifierString
      & issuerNameHashParam,
      const std::string& issuerKeyHashParam,
      const IdentifierString& serialNumberParam,
      const std::string& responderURLParam
  )
      : hashAlgorithm(hashAlgorithmParam),
        issuerNameHash(issuerNameHashParam),
        issuerKeyHash(issuerKeyHashParam),
        serialNumber(serialNumberParam),
        responderURL(responderURLParam) {}

  [[nodiscard]] HashAlgorithmEnumType getHashAlgorithm() const { return hashAlgorithm; }
  [[nodiscard]] IdentifierString getIssuerNameHash() const { return issuerNameHash; }
  [[nodiscard]] std::string getIssuerKeyHash() const { return issuerKeyHash; }
  [[nodiscard]] IdentifierString getSerialNumber() const { return serialNumber; }
  [[nodiscard]] std::string getResponderURL() const { return responderURL; }

  void setHashAlgorithm(HashAlgorithmEnumType newHashAlgorithm) { hashAlgorithm = newHashAlgorithm; }
  void setIssuerNameHash(const IdentifierString& newIssuerNameHash) { issuerNameHash = newIssuerNameHash; }
  void setIssuerKeyHash(const std::string& newIssuerKeyHash) { issuerKeyHash = newIssuerKeyHash; }
  void setSerialNumber(const IdentifierString& newSerialNumber) { serialNumber = newSerialNumber; }
  void setResponderURL(const std::string& newResponderURL) { responderURL = newResponderURL; }

  friend void to_json(nlohmann::json& j , const OCSPRequestDataType& obj) {
    j = nlohmann::json{
        {"hashAlgorithm", magic_enum::enum_name(obj.getHashAlgorithm())},
        {"issuerNameHash", obj.getIssuerNameHash()},
        {"issuerKeyHash", obj.getIssuerKeyHash()},
        {"serialNumber", obj.getSerialNumber()},
        {"responderURL", obj.getResponderURL()}
    };
  }

  friend void from_json(const nlohmann::json& j, OCSPRequestDataType& obj) {
    obj.setHashAlgorithm(magic_enum::enum_cast<HashAlgorithmEnumType>(j.at("hashAlgorithm").get<std::string>()).value_or(HashAlgorithmEnumType::SHA256));
    obj.setIssuerNameHash(j.at("issuerNameHash").get<IdentifierString>());
    obj.setIssuerKeyHash(j.at("issuerKeyHash").get<std::string>());
    obj.setSerialNumber(j.at("serialNumber").get<IdentifierString>());
    obj.setResponderURL(j.at("responderURL").get<std::string>());
  }
};



class SetMonitoringDataType {
private:
  std::optional<int> id;
  std::optional<bool> transaction;
  double value;
  MonitorEnumType type;
  int severity;
  ComponentType component;
  VariableType variable;

public:
  SetMonitoringDataType() = default;

  explicit SetMonitoringDataType(
      double valueParam,
      MonitorEnumType typeParam,
      int severityParam,
      const ComponentType& componentParam,
      const VariableType& variableParam,
      const std::optional<int>& idParam = std::nullopt,
      const std::optional<bool>& transactionParam = std::nullopt
  )
      : value(valueParam),
        type(typeParam),
        severity(severityParam),
        component(componentParam),
        variable(variableParam),
        id(idParam),
        transaction(transactionParam) {}

  // Getters
  [[nodiscard]] std::optional<int> getId() const { return id; }
  [[nodiscard]] std::optional<bool> getTransaction() const { return transaction; }
  [[nodiscard]] double getValue() const { return value; }
  [[nodiscard]] MonitorEnumType getType() const { return type; }
  [[nodiscard]] int getSeverity() const { return severity; }
  [[nodiscard]] ComponentType getComponent() const { return component; }
  [[nodiscard]] VariableType getVariable() const { return variable; }

  // Setters
  void setId(const std::optional<int>& newId) { id = newId; }
  void setTransaction(const std::optional<bool>& newTransaction) { transaction = newTransaction; }
  void setValue(double newValue) { value = newValue; }
  void setType(MonitorEnumType newType) { type = newType; }
  void setSeverity(int newSeverity) { severity = newSeverity; }
  void setComponent(const ComponentType& newComponent) { component = newComponent; }
  void setVariable(const VariableType& newVariable) { variable = newVariable; }

  // to_json and from_json will be added below.
  friend void to_json(nlohmann::json& j, const SetMonitoringDataType& data) {
    j = nlohmann::json{
        {"value", data.value},
        {"type", magic_enum::enum_name(data.type)},
        {"severity", data.severity},
        {"component", data.component},
        {"variable", data.variable}
    };
    if (data.id.has_value()) {
      j.emplace("id", data.getId().value());
    }
    if (data.transaction.has_value()) {
      j.emplace("transaction", data.getTransaction().value());
    }
  }

  friend void from_json(const nlohmann::json& j, SetMonitoringDataType& data) {
    if (j.contains("id")) {
      j.at("id").get_to(data.id.emplace());
    }

    if (j.contains("transaction")) {
      j.at("transaction").get_to(data.transaction.emplace());
    }

    j.at("value").get_to(data.value);
    data.type = magic_enum::enum_cast<MonitorEnumType>(j.at("type").get<std::string>()).value();
    j.at("severity").get_to(data.severity);
    j.at("component").get_to(data.component);
    j.at("variable").get_to(data.variable);
  }
};


class SetMonitoringResultType {
private:
  std::optional<int> id;
  SetMonitoringStatusEnumType status;
  MonitorEnumType type;
  int severity;
  ComponentType component;
  VariableType variable;

public:
  SetMonitoringResultType() = default;

  SetMonitoringResultType(
      const SetMonitoringStatusEnumType& statusParam,
      const MonitorEnumType& typeParam,
      int severityParam,
      const ComponentType& componentParam,
      const VariableType& variableParam,
      const std::optional<int>& idParam = std::nullopt)
      : status(statusParam),
        type(typeParam),
        severity(severityParam),
        component(componentParam),
        variable(variableParam),
        id(idParam) {}

  // Getter functions
  [[nodiscard]] std::optional<int> getId() const { return id; }
  [[nodiscard]] SetMonitoringStatusEnumType getStatus() const { return status; }
  [[nodiscard]] MonitorEnumType getType() const { return type; }
  [[nodiscard]] int getSeverity() const { return severity; }
  [[nodiscard]] ComponentType getComponent() const { return component; }
  [[nodiscard]] VariableType getVariable() const { return variable; }

  // Setter functions
  void setId(const std::optional<int>& newId) { id = newId; }
  void setStatus(const SetMonitoringStatusEnumType& newStatus) { status = newStatus; }
  void setType(const MonitorEnumType& newType) { type = newType; }
  void setSeverity(int newSeverity) { severity = newSeverity; }
  void setComponent(const ComponentType& newComponent) { component = newComponent; }
  void setVariable(const VariableType& newVariable) { variable = newVariable; }

  friend void to_json(nlohmann::json& j, const SetMonitoringResultType& data) {
    j = nlohmann::json{
        {"status", magic_enum::enum_name(data.status)},
        {"type", magic_enum::enum_name(data.type)},
        {"severity", data.severity},
        {"component", data.component},
        {"variable", data.variable}
    };
    if (data.id.has_value()) {
      j.emplace("id", data.id.value());
    }
  }

  friend void from_json(const nlohmann::json& j, SetMonitoringResultType& data) {
    // Implement logic to deserialize SetMonitoringResultType from JSON object
    if (j.contains("id")) {
      j.at("id").get_to(data.id.emplace());
    }
    data.status = magic_enum::enum_cast<SetMonitoringStatusEnumType>(j.at("status").get<std::string>()).value();
    data.type = magic_enum::enum_cast<MonitorEnumType>(j.at("type").get<std::string>()).value();
    j.at("severity").get_to(data.severity);
    j.at("component").get_to(data.component);
    j.at("variable").get_to(data.variable);
  }
};

class SetVariableDataType {
private:
  std::optional<AttributeEnumType> attributeType;
  std::string attributeValue;
  ComponentType component;
  VariableType variable;

public:
  SetVariableDataType() = default;

  SetVariableDataType(
      const ComponentType& componentParam,
      const VariableType& variableParam,
      const std::optional<AttributeEnumType>& attributeTypeParam = std::nullopt,
      const std::string& attributeValueParam = "")
      : component(componentParam),
        variable(variableParam),
        attributeType(attributeTypeParam),
        attributeValue(attributeValueParam) {}

  // Getter functions
  [[nodiscard]] std::optional<AttributeEnumType> getAttributeType() const { return attributeType; }
  [[nodiscard]] std::string getAttributeValue() const { return attributeValue; }
  [[nodiscard]] ComponentType getComponent() const { return component; }
  [[nodiscard]] VariableType getVariable() const { return variable; }

  // Setter functions
  void setAttributeType(const std::optional<AttributeEnumType>& newAttributeType) { attributeType = newAttributeType; }
  void setAttributeValue(const std::string& newAttributeValue) { attributeValue = newAttributeValue; }
  void setComponent(const ComponentType& newComponent) { component = newComponent; }
  void setVariable(const VariableType& newVariable) { variable = newVariable; }

  friend void to_json(nlohmann::json& j, const SetVariableDataType& data) {
    j = nlohmann::json{
        {"attributeValue", data.getAttributeValue()},
        {"component", data.getComponent()},
        {"variable", data.getVariable()}
    };
    if (data.attributeType.has_value()) {
      j.emplace("attributeType", magic_enum::enum_name(data.getAttributeType().value()));
    }
  }

  friend void from_json(const nlohmann::json& j, SetVariableDataType& data) {
    if (j.contains("attributeType")) {
      auto tmp = magic_enum::enum_cast<AttributeEnumType>(j.at("attributeType").get<std::string>());
      if (tmp.has_value()) {
        data.attributeType = tmp.value();
      }
    }
    if (j.contains("attributeValue")) {
      data.setAttributeValue(j.at("attributeValue").get<std::string>());
    }
    if (j.contains("component")) {
      data.setComponent(j.at("component").get<ComponentType>());
    }
    if (j.contains("variable")) {
      data.setVariable(j.at("variable").get<VariableType>());
    }
  }
};




class SetVariableResultType {
private:
    std::optional<AttributeEnumType> attributeType;
    SetVariableStatusEnumType attributeStatus;
    ComponentType component;
    VariableType variable;
    std::optional<StatusInfoType> attributeStatusInfo;

public:
    SetVariableResultType() = default;

    // Getter functions
    [[nodiscard]] std::optional<AttributeEnumType> getAttributeType() const { return attributeType; }
    [[nodiscard]] SetVariableStatusEnumType getAttributeStatus() const { return attributeStatus; }
    [[nodiscard]] ComponentType getComponent() const { return component; }
    [[nodiscard]] VariableType getVariable() const { return variable; }
    [[nodiscard]] std::optional<StatusInfoType> getAttributeStatusInfo() const { return attributeStatusInfo; }

    // Setter functions
    void setAttributeType(const std::optional<AttributeEnumType>& newAttributeType) { attributeType = newAttributeType; }
    void setAttributeStatus(SetVariableStatusEnumType newAttributeStatus) { attributeStatus = newAttributeStatus; }
    void setComponent(const ComponentType& newComponent) { component = newComponent; }
    void setVariable(const VariableType& newVariable) { variable = newVariable; }
    void setAttributeStatusInfo(const std::optional<StatusInfoType>& newAttributeStatusInfo) {
        attributeStatusInfo = newAttributeStatusInfo;
    }

    // JSON serialization functions
    friend void to_json(nlohmann::json& j, const SetVariableResultType& data) {
        j = nlohmann::json{
            {"attributeStatus", magic_enum::enum_name(data.getAttributeStatus())},
            {"component", data.getComponent()},
            {"variable", data.getVariable()}
            // Include other fields here
        };
        if (data.getAttributeType().has_value()) {
            j["attributeType"] = magic_enum::enum_name(data.getAttributeType().value());
        }
        if (data.getAttributeStatusInfo().has_value()) {
            j["attributeStatusInfo"] = data.getAttributeStatusInfo().value();
        }
    }

    friend void from_json(const nlohmann::json& j, SetVariableResultType& data) {
        if (j.contains("attributeType")) {
            auto tmp = magic_enum::enum_cast<AttributeEnumType>(j.at("attributeType").get<std::string>());
            if (tmp.has_value()) {
                data.attributeType = tmp.value();
            }
        }
        data.setAttributeStatus(magic_enum::enum_cast<SetVariableStatusEnumType>(j.at("attributeStatus").get<std::string>()).value());
        data.setComponent(j.at("component").get<ComponentType>());
        data.setVariable(j.at("variable").get<VariableType>());

        if (j.contains("attributeStatusInfo")) {
            data.setAttributeStatusInfo(j.at("attributeStatusInfo").get<StatusInfoType>());
        }
    }
};


class TransactionType {
private:
    IdentifierString transactionId;
    std::optional<ChargingStateEnumType> chargingState;
    std::optional<int> timeSpentCharging;
    std::optional<ReasonEnumType> stoppedReason;
    std::optional<int> remoteStartId;

public:
    TransactionType() = default;

    // Getter functions
    const IdentifierString& getTransactionId() const { return transactionId; }
    std::optional<ChargingStateEnumType> getChargingState() const { return chargingState; }
    std::optional<int> getTimeSpentCharging() const { return timeSpentCharging; }
    std::optional<ReasonEnumType> getStoppedReason() const { return stoppedReason; }
    std::optional<int> getRemoteStartId() const { return remoteStartId; }

    // Setter functions
    void setTransactionId(const IdentifierString& newTransactionId) { transactionId = newTransactionId; }
    void setChargingState(const std::optional<ChargingStateEnumType>& newChargingState) { chargingState = newChargingState; }
    void setTimeSpentCharging(const std::optional<int>& newTimeSpentCharging) { timeSpentCharging = newTimeSpentCharging; }
    void setStoppedReason(const std::optional<ReasonEnumType>& newStoppedReason) { stoppedReason = newStoppedReason; }
    void setRemoteStartId(const std::optional<int>& newRemoteStartId) { remoteStartId = newRemoteStartId; }

    // JSON serialization functions
    friend void to_json(nlohmann::json& j, const TransactionType& data) {
        j = nlohmann::json{
            {"transactionId", data.getTransactionId()},
        };
        if (data.getChargingState().has_value()) {
            j["chargingState"] = magic_enum::enum_name(data.getChargingState().value());
        }
        if (data.getTimeSpentCharging().has_value()) {
            j["timeSpentCharging"] = data.getTimeSpentCharging().value();
        }
        if (data.getStoppedReason().has_value()) {
            j["stoppedReason"] = magic_enum::enum_name(data.getStoppedReason().value());
        }
        if (data.getRemoteStartId().has_value()) {
            j["remoteStartId"] = data.getRemoteStartId().value();
        }
    }

    friend void from_json(const nlohmann::json& j, TransactionType& data) {
        data.setTransactionId(j.at("transactionId").get<IdentifierString>());

        if (j.contains("chargingState")) {
            auto tmp = magic_enum::enum_cast<ChargingStateEnumType>(j.at("chargingState").get<std::string>());
            if (tmp.has_value()) {
                data.setChargingState(tmp.value());
            }
        }
        if (j.contains("timeSpentCharging")) {
            data.setTimeSpentCharging(j.at("timeSpentCharging").get<int>());
        }
        if (j.contains("stoppedReason")) {
            auto tmp = magic_enum::enum_cast<ReasonEnumType>(j.at("stoppedReason").get<std::string>());
            if (tmp.has_value()) {
                data.setStoppedReason(tmp.value());
            }
        }
        if (j.contains("remoteStartId")) {
            data.setRemoteStartId(j.at("remoteStartId").get<int>());
        }
    }
};




class VariableAttributeType {
private:
    std::optional<AttributeEnumType> type;
    std::optional<std::string> value;
    std::optional<MutabilityEnumType> mutability;
    std::optional<bool> persistent;
    std::optional<bool> constant;

public:
    VariableAttributeType() = default;

    // Getter functions
    const std::optional<AttributeEnumType>& getType() const { return type; }
    const std::optional<std::string>& getValue() const { return value; }
    const std::optional<MutabilityEnumType>& getMutability() const { return mutability; }
    const std::optional<bool>& getPersistent() const { return persistent; }
    const std::optional<bool>& getConstant() const { return constant; }

    // Setter functions
    void setType(const std::optional<AttributeEnumType>& newType) { type = newType; }
    void setValue(const std::optional<std::string>& newValue) { value = newValue; }
    void setMutability(const std::optional<MutabilityEnumType>& newMutability) { mutability = newMutability; }
    void setPersistent(const std::optional<bool>& newPersistent) { persistent = newPersistent; }
    void setConstant(const std::optional<bool>& newConstant) { constant = newConstant; }

    // JSON serialization functions
    friend void to_json(nlohmann::json& j, const VariableAttributeType& data) {
        j = nlohmann::json{};
        if (data.getType().has_value()) {
            j["type"] = magic_enum::enum_name(data.getType().value());
        }
        if (data.getValue().has_value()) {
            j["value"] = data.getValue().value();
        }
        if (data.getMutability().has_value()) {
            j["mutability"] = magic_enum::enum_name(data.getMutability().value());
        }
        if (data.getPersistent().has_value()) {
            j["persistent"] = data.getPersistent().value();
        }
        if (data.getConstant().has_value()) {
            j["constant"] = data.getConstant().value();
        }
    }

    friend void from_json(const nlohmann::json& j, VariableAttributeType& data) {
        if (j.contains("type")) {
            auto tmp = magic_enum::enum_cast<AttributeEnumType>(j.at("type").get<std::string>());
            if (tmp.has_value()) {
                data.setType(tmp.value());
            }
        }
        if (j.contains("value")) {
            data.setValue(j.at("value").get<std::string>());
        }
        if (j.contains("mutability")) {
            auto tmp = magic_enum::enum_cast<MutabilityEnumType>(j.at("mutability").get<std::string>());
            if (tmp.has_value()) {
                data.setMutability(tmp.value());
            }
        }
        if (j.contains("persistent")) {
            data.setPersistent(j.at("persistent").get<bool>());
        }
        if (j.contains("constant")) {
            data.setConstant(j.at("constant").get<bool>());
        }
    }
};



class VariableCharacteristicsType {
private:
    std::optional<std::string> unit;
    DataEnumType dataType;
    std::optional<double> minLimit;
    std::optional<double> maxLimit;
    std::optional<std::string> valuesList;
    bool supportsMonitoring;

public:
    VariableCharacteristicsType() = default;

    // Getter functions
    const std::optional<std::string>& getUnit() const { return unit; }
    DataEnumType getDataType() const { return dataType; }
    const std::optional<double>& getMinLimit() const { return minLimit; }
    const std::optional<double>& getMaxLimit() const { return maxLimit; }
    const std::optional<std::string>& getValuesList() const { return valuesList; }
    bool getSupportsMonitoring() const { return supportsMonitoring; }

    // Setter functions
    void setUnit(const std::optional<std::string>& newUnit) { unit = newUnit; }
    void setDataType(DataEnumType newDataType) { dataType = newDataType; }
    void setMinLimit(const std::optional<double>& newMinLimit) { minLimit = newMinLimit; }
    void setMaxLimit(const std::optional<double>& newMaxLimit) { maxLimit = newMaxLimit; }
    void setValuesList(const std::optional<std::string>& newValuesList) { valuesList = newValuesList; }
    void setSupportsMonitoring(bool newSupportsMonitoring) { supportsMonitoring = newSupportsMonitoring; }

    // JSON serialization functions
    friend void to_json(nlohmann::json& j, const VariableCharacteristicsType& data) {
        j = nlohmann::json{
            {"dataType", magic_enum::enum_name(data.getDataType())},
            {"supportsMonitoring", data.getSupportsMonitoring()}
            // Include other fields here
        };
        if (data.getUnit().has_value()) {
            j["unit"] = data.getUnit().value();
        }
        if (data.getMinLimit().has_value()) {
            j["minLimit"] = data.getMinLimit().value();
        }
        if (data.getMaxLimit().has_value()) {
            j["maxLimit"] = data.getMaxLimit().value();
        }
        if (data.getValuesList().has_value()) {
            j["valuesList"] = data.getValuesList().value();
        }
    }

    friend void from_json(const nlohmann::json& j, VariableCharacteristicsType& data) {
        if (j.contains("unit")) {
            data.setUnit(j.at("unit").get<std::string>());
        }
        data.setDataType(magic_enum::enum_cast<DataEnumType>(j.at("dataType").get<std::string>()).value());
        if (j.contains("minLimit")) {
            data.setMinLimit(j.at("minLimit").get<double>());
        }
        if (j.contains("maxLimit")) {
            data.setMaxLimit(j.at("maxLimit").get<double>());
        }
        if (j.contains("valuesList")) {
            data.setValuesList(j.at("valuesList").get<std::string>());
        }
        data.setSupportsMonitoring(j.at("supportsMonitoring").get<bool>());
    }
};

#include <nlohmann/json.hpp>

// Enums and other classes...

class VariableMonitoringType {
private:
    int id;
    bool transaction;
    double value;
    MonitorEnumType type;
    int severity;

public:
    VariableMonitoringType() = default;

    // Getter functions
    int getId() const { return id; }
    bool getTransaction() const { return transaction; }
    double getValue() const { return value; }
    MonitorEnumType getType() const { return type; }
    int getSeverity() const { return severity; }

    // Setter functions
    void setId(int newId) { id = newId; }
    void setTransaction(bool newTransaction) { transaction = newTransaction; }
    void setValue(double newValue) { value = newValue; }
    void setType(MonitorEnumType newType) { type = newType; }
    void setSeverity(int newSeverity) { severity = newSeverity; }

    // JSON serialization functions
    friend void to_json(nlohmann::json& j, const VariableMonitoringType& data) {
        j = nlohmann::json{
            {"id", data.getId()},
            {"transaction", data.getTransaction()},
            {"value", data.getValue()},
            {"type", magic_enum::enum_name(data.getType())},
            {"severity", data.getSeverity()}
        };
    }

    friend void from_json(const nlohmann::json& j, VariableMonitoringType& data) {
        data.setId(j.at("id").get<int>());
        data.setTransaction(j.at("transaction").get<bool>());
        data.setValue(j.at("value").get<double>());
        data.setType(magic_enum::enum_cast<MonitorEnumType>(j.at("type").get<std::string>()).value());
        data.setSeverity(j.at("severity").get<int>());
    }
};


}
#endif // ECHOOCPP_DATATYPES_HPP
