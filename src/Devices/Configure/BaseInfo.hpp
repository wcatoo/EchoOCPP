#ifndef ECHOOCPP_CONFIGURE_BASE_INFO_HPP
#define ECHOOCPP_CONFIGURE_BASE_INFO_HPP
#include <string>
#include <nlohmann/json.hpp>
#include "../../System/IO.hpp"


enum class BaseInfoType {
    SerialNumber,
    Model,
    VendorName,
    FirmwareVersion
};

class BaseInfo
{
private:
    std::filesystem::path mConfigurePath{};
public:
    BaseInfo() = default;
    std::string serialNumber;
    std::string model;
    std::string vendorName;
    std::string firmwareVersion;
    
  friend void to_json(nlohmann::json &json, const BaseInfo &tConfigure) {
    json = nlohmann::json{
        {"serialNumber", tConfigure.serialNumber},
        {"model", tConfigure.model},
        {"vendorName", tConfigure.vendorName},
        {"firmwareVersion", tConfigure.firmwareVersion}
    };
  }
  friend void from_json(const nlohmann::json& j, BaseInfo &tConfigure) {
    if (j.contains("model")) {
        j.at("model").get_to(tConfigure.model);
    }
    if (j.contains("serialNumber")) {
        j.at("serialNumber").get_to(tConfigure.serialNumber);
    }
    if (j.contains("vendorName")) {
        j.at("vendorName").get_to(tConfigure.vendorName);
    }
    if (j.contains("firmwareVersion")) {
        j.at("firmwareVersion").get_to(tConfigure.firmwareVersion);
    }
  }
};

#endif