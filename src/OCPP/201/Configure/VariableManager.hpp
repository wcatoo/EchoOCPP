//#ifndef ECHOOCPP_VARIABLEMANAGER_HPP
//#define ECHOOCPP_VARIABLEMANAGER_HPP
#pragma once
#include "201/Configure/ConfigureVariables.hpp"
#include "201/Message/MessageRequest.hpp"
#include "201/Message/MessageRespone.hpp"
#include "../System/IO.hpp"
#include <ranges>

namespace OCPP201 {
class VariableManager {
private:
  std::filesystem::path mConfigurePath;
public:
  OCPP201::ComponentVariableManager mComponentManager;
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

  NotifyReportRequest getNotifyRequestInventory(int tRequestId, int tSeqNo, bool tbc, ReportBaseEnumType tType) {
    NotifyReportRequest request;
    request.requestId = tRequestId;
    request.seqNo = tSeqNo;
    request.tbc = tbc;
    request.generatedAt = RFC3339DateTime().nowString();
    auto seqEndNo = (tSeqNo+4) >= this->mComponentManager.componentVariable.size()? this->mComponentManager.componentVariable.size()-1 : tSeqNo+4;
    ReportDataType reportDataType;
    for (auto i = tSeqNo; i < seqEndNo; i++) {
      try {
        ComponentVariableConfigure config = this->mComponentManager.componentVariable.at(i);
        reportDataType.setComponent(config.component);
        reportDataType.setVariable(config.variable);
        reportDataType.setVariableCharacteristics(config.variableCharacteristics);
        if (tType == ReportBaseEnumType::ConfigurationInventory) {
          std::vector<VariableAttributeType> tmp;
          for (const auto& attribute : config.variableAttribute) {
            if (attribute.getMutability().has_value()
                && (attribute.getMutability().value() == MutabilityEnumType::ReadWrite
                    || attribute.getMutability().value() == MutabilityEnumType::WriteOnly))
            {
              tmp.emplace_back(attribute);
            }
          }
        } else if (tType == ReportBaseEnumType::FullInventory) {
          reportDataType.variableAttributes = config.variableAttribute;
        }
        request.reportData.emplace_back(reportDataType);
      } catch (std::exception &e) {
        return request;
      }
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
    auto hasComponentVariable = std::ranges::find_if(mComponentManager.componentVariable,
                                                     [&](const ComponentVariableConfigure &config) {
                                                       return config.component == tComponentType && config.variable == tVariableType;
                                                     });

    if (hasComponentVariable == mComponentManager.componentVariable.end()) {
      return std::nullopt;
    }

    auto& variableAttribute = hasComponentVariable->variableAttribute;
    auto hasAttributeType = std::ranges::find_if(variableAttribute,
                                                 [tType](const VariableAttributeType &config) {
                                                   return config.getType() == tType;
                                                 });

    return hasAttributeType != variableAttribute.end() ? std::make_optional(*hasAttributeType) : std::nullopt;
  }

  bool setVariableAttributeValue (ComponentType &tComponentType, const VariableType &tVariableType, AttributeEnumType tType, const std::string &tValue) {
    auto hasComponentVariable = std::ranges::find_if(mComponentManager.componentVariable,
                                                     [&](const ComponentVariableConfigure &config) {
                                                       return config.component == tComponentType && config.variable == tVariableType;
                                                     });

    if (hasComponentVariable != mComponentManager.componentVariable.end()) {
      auto& variableAttribute = hasComponentVariable->variableAttribute;
      auto hasAttributeType = std::ranges::find_if(variableAttribute,
                                                   [tType](const VariableAttributeType &config) {
                                                     return config.getType() == tType;
                                                   });

      if (hasAttributeType != variableAttribute.end()) {
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
