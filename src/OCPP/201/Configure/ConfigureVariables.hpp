#ifndef ECHOOCPP_CONFIGUREKEYGENERAL_HPP
#define ECHOOCPP_CONFIGUREKEYGENERAL_HPP
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../DataType/PrimitiveDatatypes.hpp"


namespace OCPP201 {

class ComponentVariableConfigure {
public:
  AttributeEnumType attributeType{AttributeEnumType::Actual};
  std::string attributeValue;
  ComponentType component;
  VariableType variable;
  friend void to_json(nlohmann::json& j, const ComponentVariableConfigure& data) {
    j = nlohmann::json {
          {"attributeValue", data.attributeValue},
      {"component", data.component},
      {"variable", data.variable},
      {"attributeType", data.attributeType}
    };
  }

  friend void from_json(const nlohmann::json& j, ComponentVariableConfigure& data) {
    auto tmp = magic_enum::enum_cast<AttributeEnumType>(j.at("attributeType"));
    if (tmp.has_value()) {
      data.attributeType = tmp.value();
    } else {
      data.attributeType = AttributeEnumType::Actual;
    }

    j.at("component").get_to(data.component);
    j.at("variable").get_to(data.variable);
    j.at("attributeValue").get_to(data.attributeValue);
  }
};


class ComponentVariableManager {
public:
  std::vector<ComponentVariableConfigure> componentVariable;

};

}

#endif

