//
// Created by 杨帆 on 2023/11/20.
//

#ifndef ECHOOCPP_DATATYPES_HPP
#define ECHOOCPP_DATATYPES_HPP

#include <iostream>

#include <magic_enum.hpp>
#include <nlohmann/json.hpp>

#include "Enumerations.hpp"


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
    if (tJson.contains("certificateType")) {
//      tJson.at("certificateType").get_to(chainData.certificateType);

      auto tmp  = magic_enum::enum_cast<GetCertificateIdUseEnumType>(tJson.at("certificateType").get<std::string>());
      if (tmp.has_value()) {
        chainData.certificateType = tmp.value();
      }
//      auto authTypeEnum =
//          magic_enum::enum_cast<APNAuthenticationEnumType>(authTypeStr);
    }

    if (tJson.contains("certificateHashData")) {
      tJson.at("certificateHashData").get_to(chainData.certificateHashData);
    }

    if (tJson.contains("childCertificateHashData")) {
      tJson.at("childCertificateHashData").get_to(chainData.childCertificateHashData.emplace());
    }
  }
};



}

#endif // ECHOOCPP_DATATYPES_HPP
