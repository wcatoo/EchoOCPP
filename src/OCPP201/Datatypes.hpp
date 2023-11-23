//
// Created by 杨帆 on 2023/11/20.
//

#ifndef ECHOOCPP_DATATYPES_HPP
#define ECHOOCPP_DATATYPES_HPP
#include <magic_enum.hpp>

#include <iostream>

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


#include <nlohmann/json.hpp>

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
public:
  // Required. This field specifies the additional IdToken.
  std::string additionalIdToken;
  // Required. This defines the type of the additionalIdToken.
  // This is a custom type, so the implementation needs to be
  // agreed upon by all involved parties.
  std::string type;

//  AdditionalInfoType(const std::string& additionalIdToken, const std::string& type)
//      : additionalIdToken(additionalIdToken), type(type) {}

  // Function to convert AdditionalInfoType object to JSON
  friend void to_json(nlohmann::json &tJson, const AdditionalInfoType &tData) {
    tJson = nlohmann::json { {"additionalIdToken", tData.additionalIdToken}, {"type", tData.type} };
  }

  friend void from_json(const nlohmann::json &tJson, AdditionalInfoType &tData) {
      if (tJson.contains("additionalIdToken")) {
        tJson.at("additionalIdToken").get<std::string>();
      }

      if (tJson.contains("type")) {
        tJson.at("type").get<std::string>();
      }
  }

};



enum class APNAuthenticationEnumType {
  CHAP,
  NONE,
  PAP,
  AUTO
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
public:
  std::string apn;
  std::optional<std::string> apnUserName;
  std::optional<std::string> apnPassword;
  std::optional<int> simPin;
  std::optional<std::string> preferredNetwork;
  std::optional<bool> useOnlyPreferredNetwork;
  APNAuthenticationEnumType apnAuthentication;

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
};





struct IdTokenInfoType {
  // Define IdTokenInfoType fields as needed
};

struct IdTokenType {
  // Define IdTokenType fields as needed
};

class AuthorizationData {
public:
  std::optional<IdTokenInfoType> idTokenInfo;
  IdTokenType idToken;

  friend void to_json(nlohmann::json &j, const AuthorizationData &authData) {
//    j = nlohmann::json{
//        {"updateType", magic_enum::enum_name(authData.updateType)},
//        {"idTokenInfo", authData.idTokenInfo},
//        {"idToken", authData.idToken}
//    };
  }

  friend void from_json(const nlohmann::json &j, AuthorizationData &authData) {
    //        j.at("updateType").get_to(authData.updateType);
    //        j.at("idTokenInfo").get_to(authData.idTokenInfo);
    //        j.at("idToken").get_to(authData.idToken);
  }
};
#endif // ECHOOCPP_DATATYPES_HPP
