//#ifndef ECHOOCPP_VARIABLEMANAGER_HPP
//#define ECHOOCPP_VARIABLEMANAGER_HPP
#pragma once
#include "201/Configure/ConfigureVariables.hpp"
#include "201/Message/MessageRequest.hpp"
#include "201/Message/MessageRespone.hpp"

namespace OCPP201 {
class VariableManager {
private:
  std::filesystem::path mConfigurePath;
  OCPP201::ComponentVariableManager mComponentManager;
public:
  inline void setFilePath(const std::string &tPath) {
    this->mConfigurePath = tPath;
  }

  void init() {
      try {
        this->mComponentManager = nlohmann::json::parse(System_IO::readFromFile(mConfigurePath).value());
      } catch (std::exception &e) {
        nlohmann::json tmp = this->mComponentManager;
        System_IO::writeToFile(tmp.dump(),this->mConfigurePath);
      }
  }
  void save() {
    nlohmann::json tmp = this->mComponentManager;
    System_IO::writeToFile(tmp.dump(), mConfigurePath);
  }

  NotifyReportRequest getNotifyRequestConfigurationInventory(int tRequestId) {
    NotifyReportRequest request;
    request.requestId = tRequestId;
    request.seqNo = 0;
    request.tbc = false;
    request.generatedAt = RFC3339DateTime().nowString();

    ReportDataType reportDataType;
    for (auto component : this->mComponentManager.componentVariable) {

    }


    return request;
  }


  [[nodiscard]] const std::string getVariableAttributeValue(const ComponentType &tComponentType, const VariableType &tVariableType, AttributeEnumType tType) const {
      auto tmp = getVariableAttribute(tComponentType, tVariableType, tType);
      if (tmp.has_value() && tmp.value().getValue().has_value()) {
        return tmp.value().getValue().value();
      }
      return "";
  }

  std::optional<VariableAttributeType> getVariableAttribute(const ComponentType &tComponentType, const VariableType &tVariableType, AttributeEnumType tType) const {
    auto hasComponentVariable = std::find_if(this->mComponentManager.componentVariable.begin(),
                              this->mComponentManager.componentVariable.end(),
                              [&](const ComponentVariableConfigure &config){
                                return config.component == tComponentType && config.variable == tVariableType;
                              });
    if (hasComponentVariable != this->mComponentManager.componentVariable.end()) {
      auto hasAttributeType = std::find_if(hasComponentVariable->variableAttribute.begin(), hasComponentVariable->variableAttribute.end(),
                                           [tType](const VariableAttributeType &config){
                                             return config.getType() == tType;
                                           });
      if (hasAttributeType != hasComponentVariable->variableAttribute.end()) {
        return *hasAttributeType;
      } else {
        return std::nullopt;
      }
    }
    return std::nullopt;
  }

  bool setVariableAttributeValue (ComponentType &tComponentType, const VariableType &tVariableType, AttributeEnumType tType, const std::string &tValue) {
    auto hasComponentVariable =
        std::find_if(this->mComponentManager.componentVariable.begin(),
                     this->mComponentManager.componentVariable.end(),
                     [&](const ComponentVariableConfigure &config) {
                       return config.component == tComponentType &&
                              config.variable == tVariableType;
                     });
    if (hasComponentVariable !=
        this->mComponentManager.componentVariable.end()) {
      auto hasAttributeType =
          std::find_if(hasComponentVariable->variableAttribute.begin(),
                       hasComponentVariable->variableAttribute.end(),
                       [tType](const VariableAttributeType &config) {
                         return config.getType() == tType;
                       });
      if (hasAttributeType != hasComponentVariable->variableAttribute.end()) {
        hasAttributeType->setValue(tValue);
        return true;
      }
    }
    return false;
  }

  GetVariablesResponse getVariableRequestHandler(const GetVariablesRequest &tRequest) {
    GetVariablesResponse response;
    // B06.FR.01
    for (const auto &dataReq : tRequest.getVariableData) {
      GetVariableResultType  result;
      // B06.FR.02
      result.setComponent(dataReq.component);
      result.setVariable(dataReq.variable);
      // B06.FR.03
      result.setAttributeType(dataReq.attributeType);
      auto hasComponentVariable = std::find_if(this->mComponentManager.componentVariable.begin(), this->mComponentManager.componentVariable.end(),
                                               [&](ComponentVariableConfigure &config){
                                                 if (dataReq.component == config.component) {
                                                   if (dataReq.variable == config.variable) {
                                                     return true;
                                                   }else {
                                                     // B06.FR.07
                                                     result.setAttributeStatus(GetVariableStatusEnumType::UnknownVariable);
                                                   }
                                                 } else {
                                                   // B06.FR.06
                                                   result.setAttributeStatus(GetVariableStatusEnumType::UnknownComponent);
                                                 }
                                                 return false;
                                               });
      if (hasComponentVariable != this->mComponentManager.componentVariable.end()) {
        auto hasAttribute =
            std::find_if(hasComponentVariable->variableAttribute.begin(),
                         hasComponentVariable->variableAttribute.end(),
                         [&dataReq, &result](VariableAttributeType &instance) {
                           return dataReq.attributeType ==
                                  instance.getType();
                         });
        if (hasAttribute != hasComponentVariable->variableAttribute.end()) {
          if (hasAttribute->getMutability() == MutabilityEnumType::WriteOnly) {
            // B06.RF.09
            result.setAttributeStatus(GetVariableStatusEnumType::Rejected);
          }
        }
      }
      response.getVariableResult.emplace_back(result);
    }
    return response;
  }

  SetVariablesResponse setVariableRequestHandler(const SetVariablesRequest &tRequest) {
    SetVariablesResponse response;
    for (const auto &dataReq : tRequest.setVariableData) {
      SetVariableResultType result;
      result.setComponent(dataReq.component);
      result.setVariable(dataReq.variable);
      result.setAttributeType(dataReq.attributeType);
      auto hasComponentVariable = std::find_if(this->mComponentManager.componentVariable.begin(), this->mComponentManager.componentVariable.end(),
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
      if (hasComponentVariable != this->mComponentManager.componentVariable.end()) {
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
    return response;
  }
};

}

//#endif // ECHOOCPP_VARIABLEMANAGER_HPP