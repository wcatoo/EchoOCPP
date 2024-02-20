#ifndef ECHOOCPP_VARIABLEMANAGER_HPP
#define ECHOOCPP_VARIABLEMANAGER_HPP
#include "../Configure/ConfigureVariables.hpp"
#include "../System/IO.hpp"
#include "../DataType/Datatypes.hpp"

namespace OCPP201 {
class VariableManager {
private:
  std::filesystem::path mConfigurePath;
  OCPP201::ComponentManager mComponentManager;
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
    for (SetVariableDataType dataRequest : tRequest.setVariableData) {
      SetVariableResultType setVariableResultType;
      setVariableResultType.setComponent(dataRequest.getComponent());
      setVariableResultType.setVariable(dataRequest.getVariable());
      setVariableResultType.setAttributeType(dataRequest.getAttributeType());
      auto hasComponent = std::find_if(this->mComponentManager.components.begin(),
                             this->mComponentManager.components.end(),
                             [&dataRequest](const Component& component) {
                               return component.componentName == dataRequest.getComponent().name;
                             });
      if (hasComponent != this->mComponentManager.components.end()) {
        auto hasComponentInstance = std::find_if(hasComponent->component.begin(), hasComponent->component.end(),
                                        [&dataRequest](ComponentInstance &componentInstance) {
                                                   if (componentInstance.variableName == dataRequest.getVariable().name
                                                       && componentInstance.componentInstance == dataRequest.getComponent().instance) {
                                                     if (componentInstance.evse.has_value() && dataRequest.getComponent().evse.has_value()) {
                                                       if (componentInstance.evse.value().id == dataRequest.getComponent().evse->id) {
                                                         if (componentInstance.evse.value().connectorId.has_value() && dataRequest.getComponent().evse->connectorId.has_value()) {
                                                           return componentInstance.evse.value().connectorId.value() == dataRequest.getComponent().evse->connectorId.value();
                                                         }
                                                       }
                                                     }
                                                   }
                                                   return false;
                                        });
        if (hasComponentInstance != hasComponent->component.end()) {

        } else {
          setVariableResultType.setAttributeStatus(SetVariableStatusEnumType::UnknownVariable);
        }
      } else {
        setVariableResultType.setAttributeStatus(SetVariableStatusEnumType::UnknownComponent);
      }
      response.setVariableResult.emplace_back(setVariableResultType);
    }

    return response;
  }
};

}

#endif // ECHOOCPP_VARIABLEMANAGER_HPP
