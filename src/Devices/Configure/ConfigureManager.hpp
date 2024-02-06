#ifndef ECHOOCPP_CONFIGURE_MANAGER_HPP
#define ECHOOCPP_CONFIGURE_MANAGER_HPP
#include "BaseInfo.hpp"
#include "../../System/IO.hpp"

class ConfigureManager
{
private:
    std::filesystem::path tBaseInfoPath{"../bin/BaseInfo.json"};
    BaseInfo mBaseInfo;
public:
    void init() {
        try {
            this->mBaseInfo = nlohmann::json::parse(System_IO::readFromFile(this->tBaseInfoPath).value());
        } catch (std::exception &e) {
            this->mBaseInfo = BaseInfo();
            nlohmann::json tmp = this->mBaseInfo;
            System_IO::writeToFile(tmp.dump(), tBaseInfoPath);
        }
    }
    BaseInfo& getBaseInfo() {
        return this->mBaseInfo;
    }
};

#endif