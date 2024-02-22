#ifndef ECHOOCPP_VARIABLEMANAGER_HPP
#define ECHOOCPP_VARIABLEMANAGER_HPP
#include "../Configure/ConfigureVariables.hpp"
#include "../System/IO.hpp"
#include "../DataType/Datatypes.hpp"

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
        auto hasAttribute = std::find_if(hasComponentVariable->attribute.begin(), hasComponentVariable->attribute.end(),
                                         [&dataReq, &result] (AttributeInstance &instance) {
                                           return dataReq.attributeType == instance.variableAttribute.getType();
                                         });
        if (hasAttribute != hasComponentVariable->attribute.end()) {
          switch (hasAttribute->variableCharacteristics.getDataType()) {
          case DataEnumType::StringType:
            hasAttribute->variableAttribute.setValue(dataReq.attributeValue);
            result.setAttributeStatus(SetVariableStatusEnumType::Accepted);
            break;
          case DataEnumType::DateTimeType:
              if (RFC3339DateTime::fromString(dataReq.attributeValue) == std::nullopt) {
                result.setAttributeStatus(SetVariableStatusEnumType::Rejected);
                StatusInfoType statusInfoType;
                statusInfoType.reasonCode = "String format to RFC3339 time failed";
                result.setAttributeStatusInfo(statusInfoType);
              } else {
                hasAttribute->variableAttribute.setValue(dataReq.attributeValue);
                result.setAttributeStatus(SetVariableStatusEnumType::Accepted);
              }
          case DataEnumType::BooleanType:
            if (std::tolower(dataReq.attributeValue == "true") || std::tolower(dataReq.attributeValue == "false"))
            {
              hasAttribute->variableAttribute.setValue(dataReq.attributeValue);
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
              hasAttribute->variableAttribute.setValue(dataReq.attributeValue);

              if ((hasAttribute->variableCharacteristics.getMaxLimit().has_value() &&  tmp > hasAttribute->variableCharacteristics.getMaxLimit())
                  || (hasAttribute->variableCharacteristics.getMinLimit().has_value() && tmp < hasAttribute->variableCharacteristics.getMinLimit())) {
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
              auto t = std::stof(dataReq.attributeValue);
              hasAttribute->variableAttribute.setValue(dataReq.attributeValue);
              if ((hasAttribute->variableCharacteristics.getMaxLimit().has_value() &&  tmp > hasAttribute->variableCharacteristics.getMaxLimit())
                  || (hasAttribute->variableCharacteristics.getMinLimit().has_value() && tmp < hasAttribute->variableCharacteristics.getMinLimit())) {
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
            hasAttribute->variableCharacteristics.setValuesList(dataReq.attributeValue);
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
//        result.setAttributeStatus(SetVariableStatusEnumType::Accepted);
      }
      response.setVariableResult.emplace_back(result);
    }
    return response;
  }
};

}

#endif // ECHOOCPP_VARIABLEMANAGER_HPP
