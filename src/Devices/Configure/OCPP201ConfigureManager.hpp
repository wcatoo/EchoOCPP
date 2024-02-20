#ifndef ECHOOCPP_CONFIGURE_MANAGER_HPP
#define ECHOOCPP_CONFIGURE_MANAGER_HPP
#include "BaseInfo.hpp"
#include "../../System/IO.hpp"
#include "../../OCPP/201/Configure/ConfigureVariables.hpp"

class OCPP201ConfigureManager
{
private:
    std::filesystem::path mBaseInfoPath{"../bin/BaseInfo.json"};
    std::filesystem::path mVariableJsonPath{"../config/Variables.json"};
    BaseInfo mBaseInfo;
//    ConfigureVariables mVariables;

public:
    void init() {
        try {
            this->mBaseInfo = nlohmann::json::parse(System_IO::readFromFile(this->mBaseInfoPath).value());
        } catch (std::exception &e) {
            this->mBaseInfo = BaseInfo();
            nlohmann::json tmp = this->mBaseInfo;
            System_IO::writeToFile(tmp.dump(), mBaseInfoPath);
        }
//        try {
//            this->mVariables = nlohmann::json::parse(System_IO::readFromFile(this->mVariableJsonPath).value());
//        } catch (std::exception &e) {
//            this->mVariables = ConfigureVariables();
//            nlohmann::json tmp = this->mVariables;
//            System_IO::writeToFile(tmp.dump(), mVariableJsonPath);
//        }
    }
    inline BaseInfo& getBaseInfo() {
        return this->mBaseInfo;
    }

//    inline ConfigureVariables& getVariables() {
//        return this->mVariables;
//    }
    void save() {
        nlohmann::json tmp = this->mBaseInfo;
        System_IO::writeToFile(tmp.dump(), mBaseInfoPath);
//        tmp = this->mVariables;
//        System_IO::writeToFile(tmp.dump(), mVariableJsonPath);

    }
};

#endif