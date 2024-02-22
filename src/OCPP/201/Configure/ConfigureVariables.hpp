#ifndef ECHOOCPP_CONFIGUREKEYGENERAL_HPP
#define ECHOOCPP_CONFIGUREKEYGENERAL_HPP
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../DataType/PrimitiveDatatypes.hpp"


namespace OCPP201 {

class AttributeInstance {
public:
  VariableAttributeType variableAttribute;
  VariableCharacteristicsType variableCharacteristics;
  friend void to_json(nlohmann::json& j, const AttributeInstance& data) {
    j = nlohmann::json {
        {"variableAttribute", data.variableAttribute},
        {"variableCharacteristics", data.variableCharacteristics}
    };
  }
  friend void from_json(const nlohmann::json& j, AttributeInstance& data) {
    j.at("variableAttribute").get_to(data.variableAttribute);
    j.at("variableCharacteristics").get_to(data.variableCharacteristics);
  }

};

class ComponentVariableConfigure {
public:
  std::vector<AttributeInstance> attribute;
  ComponentType component;
  VariableType variable;
  friend void to_json(nlohmann::json& j, const ComponentVariableConfigure& data) {
    j = nlohmann::json {
      {"component", data.component},
      {"variable", data.variable},
        {"attribute", data.attribute}
    };
  }

  friend void from_json(const nlohmann::json& j, ComponentVariableConfigure& data) {
    j.at("component").get_to(data.component);
    j.at("variable").get_to(data.variable);
    j.at("attribute").get_to(data.attribute);
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

#endif

