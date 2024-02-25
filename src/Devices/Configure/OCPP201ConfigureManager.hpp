//#ifndef ECHOOCPP_CONFIGURE_MANAGER_HPP
//#define ECHOOCPP_CONFIGURE_MANAGER_HPP
#pragma once
#include "BaseInfo.hpp"
#include "../../OCPP/201/Configure/VariableManager.hpp"

class OCPP201ConfigureManager
{
private:
    std::filesystem::path mBaseInfoPath{"../bin/BaseInfo.json"};
    std::filesystem::path mVariableJsonPath{"../config/Variables.json"};
    BaseInfo mBaseInfo;
    OCPP201::VariableManager mVariableManager;

public:
    void init() {
        try {
            this->mBaseInfo = nlohmann::json::parse(System_IO::readFromFile(this->mBaseInfoPath).value());
            this->mVariableManager.setFilePath(this->mVariableJsonPath);
            this->mVariableManager.init();
        } catch (std::exception &e) {
            this->mBaseInfo = BaseInfo();
            nlohmann::json tmp = this->mBaseInfo;
            System_IO::writeToFile(tmp.dump(), mBaseInfoPath);
        }
    }
    inline BaseInfo& getBaseInfo() {
        return this->mBaseInfo;
    }

    inline OCPP201::VariableManager& getVariableManager() {
      return this->mVariableManager;
    }

    void save() {
        nlohmann::json tmp = this->mBaseInfo;
        System_IO::writeToFile(tmp.dump(), mBaseInfoPath);
    }
};

//#endif