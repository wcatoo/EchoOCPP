#ifndef ECHOOCPP_PRIMITIVEDATATYPES_HPP
#define ECHOOCPP_PRIMITIVEDATATYPES_HPP

#include <regex>
#include <string>
#include <chrono>
#include <sstream>

#include <nlohmann/json.hpp>

class IdentifierString {
private:
  std::string value;

  static const std::regex& getPasswordPattern() {
    static const std::regex pattern("^[a-zA-Z0-9*\\-_=:+|@.]+$");
    return pattern;
  }
public:
  IdentifierString() = default;

  explicit IdentifierString(const std::string& newValue) {
    setValue(newValue);
  }

  const std::string& getValue() const {
    return value;
  }

  bool setValue(const std::string& newValue) {
    if (!isValidIdentifier(newValue)) {
      std::cerr << "Error: Invalid identifier string. It must be case-insensitive and contain specific characters.\n";
      value = "";
      return false;
    }
    value = newValue;
    return true;
  }

  friend void to_json(nlohmann::json& j, const IdentifierString& identifier) {
    j = identifier.value;
  }

  friend void from_json(const nlohmann::json& j, IdentifierString& identifier) {
    if (j.is_string()) {
      identifier.setValue(j.get<std::string>());
    }
  }


private:
  static bool isValidIdentifier(const std::string& str) {
    return std::regex_match(str, getPasswordPattern());
  }
};


class PasswordString {
private:
  std::string value;

  static const std::regex& getPasswordPattern() {
    static const std::regex pattern("^[a-zA-Z0-9*\\-_=:+|@.]+$");
    return pattern;
  }

public:
  // Constructors
  PasswordString() = default;

  explicit PasswordString(const std::string& newValue) {
    setValue(newValue);
  }

  // Getter and setter functions
  const std::string& getValue() const {
    return value;
  }

  bool setValue(const std::string& newValue) {
    if (!isValidPassword(newValue)) {
      std::cerr << "Error: Invalid password string. It must be UTF-8 encoded, case-sensitive, and have specific characters.\n";
      value = "";
      return false;
    }
    value = newValue;
    return true;
  }

  friend void to_json(nlohmann::json& j, const PasswordString& data) {
    j = data.value;
  }

  friend void from_json(const nlohmann::json& j, PasswordString& data) {
    if (j.is_string()) {
      data.setValue(j.get<std::string>());
    }
  }



private:
  // Function to validate the password string using the static member function
  bool isValidPassword(const std::string& str) const {
    return std::regex_match(str, getPasswordPattern());
  }
};

class RFC3339DateTime {
private:
  std::chrono::system_clock::time_point dateTime;

public:
  RFC3339DateTime() = default;

  std::string nowString() {
    this->dateTime = std::chrono::system_clock::now();
    return toString();
  }

  explicit RFC3339DateTime(std::time_t dateTimeParam){
    this->setDateTime(dateTimeParam);
  }
  explicit RFC3339DateTime(const std::chrono::system_clock::time_point& dateTimeParam)
      : dateTime(dateTimeParam) {}

  [[nodiscard]] std::chrono::system_clock::time_point getDateTime() const {
    return dateTime;
  }

  [[nodiscard]] std::time_t getDateTimeUnixType() const {
    auto tmp =  static_cast<std::time_t >(std::chrono::duration_cast<std::chrono::seconds>(this->dateTime.time_since_epoch()).count());
    return tmp;
  }

  void setDateTime(const std::chrono::system_clock::time_point& newDateTime) {
    dateTime = newDateTime;
  }

  void setDateTime(const std::time_t newDateTime) {
    this->dateTime = std::chrono::system_clock::from_time_t(newDateTime);
  }

  // Convert to RFC3339 string
  [[nodiscard]] std::string toString() const {
    auto time = std::chrono::system_clock::to_time_t(dateTime);
    struct tm tm{};
    gmtime_r(&time, &tm);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
    return oss.str();
  }

  // Parse RFC3339 string
  static std::optional<RFC3339DateTime> fromString(const std::string& str) {
    //    std::chrono::system_clock::time_point timePoint;
    std::tm tm{};
    std::istringstream ss(str);
    ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
    if (ss.fail()) {
      return std::nullopt;
    }
    return RFC3339DateTime(std::mktime(&tm));
  }

  friend void to_json(nlohmann::json& j, const RFC3339DateTime& dateTimeObj) {
    j = dateTimeObj.toString();
  }

  friend void from_json(const nlohmann::json& j, RFC3339DateTime& dateTimeObj) {
    auto tmp =  RFC3339DateTime::fromString(j.get<std::string>());
    if (tmp.has_value()) {
      dateTimeObj = tmp.value();
    } else {
      dateTimeObj = RFC3339DateTime(0);
    }
  }
};
#endif // ECHOOCPP_PRIMITIVEDATATYPES_HPP
