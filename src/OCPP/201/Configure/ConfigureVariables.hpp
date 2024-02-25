//#ifndef ECHOOCPP_CONFIGUREKEYGENERAL_HPP
//#define ECHOOCPP_CONFIGUREKEYGENERAL_HPP
#pragma once
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "201/DataType/PrimitiveDatatypes.hpp"
#include "201/DataType/Datatypes.hpp"
namespace OCPP201 {

class ComponentVariableConfigure {
public:
  std::vector<VariableAttributeType> variableAttribute;
  VariableCharacteristicsType variableCharacteristics;
  ComponentType component;
  VariableType variable;
  friend void to_json(nlohmann::json& j, const ComponentVariableConfigure& data) {
    j = nlohmann::json {
      {"component", data.component},
      {"variable", data.variable},
      {"variableAttribute", data.variableAttribute},
      {"variableCharacteristics", data.variableCharacteristics}
    };
  }

  friend void from_json(const nlohmann::json& j, ComponentVariableConfigure& data) {
    j.at("component").get_to(data.component);
    j.at("variable").get_to(data.variable);
    if (j.contains("variableAttribute") && j.at("variableAttribute").is_array()) {
      data.variableAttribute = j.at("variableAttribute").get<std::vector<VariableAttributeType>>();
    } else {
      data.variableAttribute = std::vector<VariableAttributeType>();
    }
    if (j.contains("variableCharacteristics") && j.at("variableCharacteristics").is_array()) {
      j.at("variableCharacteristics").get_to(data.variableCharacteristics);
    } else {
      data.variableCharacteristics = VariableCharacteristicsType();
    }
  }
};


class ComponentVariableManager {
public:
  std::vector<ComponentVariableConfigure> componentVariable;

  friend void to_json(nlohmann::json& j, const ComponentVariableManager& data) {
    j = nlohmann::json {
        {"componentVariable", data.componentVariable}
    };
  }
  friend void from_json(const nlohmann::json& j, ComponentVariableManager& data) {
    j.at("componentVariable").get_to(data.componentVariable);
  }
};

}

//#endif

