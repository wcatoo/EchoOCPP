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
    return response;
  }
};

}

#endif // ECHOOCPP_VARIABLEMANAGER_HPP
