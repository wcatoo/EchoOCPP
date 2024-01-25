#ifndef ECHOOCPP_Meter_HPP
#define ECHOOCPP_Meter_HPP
#include "../OCPP201/DataType/Enumerations.hpp"
#include <optional>

class Meter
{
public:
    void setMeasuredL1(double value) { measured_L1 = value; }
    void setMeasuredL2(double value) { measured_L2 = value; }
    void setMeasuredL3(double value) { measured_L3 = value; }
    void setMeasuredN(double value) { measured_N = value; }
    void setMeasuredL1N(double value) { measured_L1_N = value; }
    void setMeasuredL2N(double value) { measured_L2_N = value; }
    void setMeasuredL3N(double value) { measured_L3_N = value; }
    void setMeasuredL1L2(double value) { measured_L1_L2 = value; }
    void setMeasuredL2L3(double value) { measured_L2_L3 = value; }
    void setMeasuredL3L1(double value) { measured_L3_L1 = value; }

    std::optional<double> getMeasuredL1() const { return measured_L1; }
    std::optional<double> getMeasuredL2() const { return measured_L2; }
    std::optional<double> getMeasuredL3() const { return measured_L3; }
    std::optional<double> getMeasuredN() const { return measured_N; }
    std::optional<double> getMeasuredL1N() const { return measured_L1_N; }
    std::optional<double> getMeasuredL2N() const { return measured_L2_N; }
    std::optional<double> getMeasuredL3N() const { return measured_L3_N; }
    std::optional<double> getMeasuredL1L2() const { return measured_L1_L2; }
    std::optional<double> getMeasuredL2L3() const { return measured_L2_L3; }
    std::optional<double> getMeasuredL3L1() const { return measured_L3_L1; }

private:
    std::optional<double> measured_L1{std::nullopt};
    std::optional<double> measured_L2{std::nullopt};
    std::optional<double> measured_L3{std::nullopt};
    std::optional<double> measured_N{std::nullopt};
    std::optional<double> measured_L1_N{std::nullopt};
    std::optional<double> measured_L2_N{std::nullopt};
    std::optional<double> measured_L3_N{std::nullopt};
    std::optional<double> measured_L1_L2{std::nullopt};
    std::optional<double> measured_L2_L3{std::nullopt};
    std::optional<double> measured_L3_L1{std::nullopt};
    OCPP201::PhaseEnumType mPhaseType{};
    
};

#endif