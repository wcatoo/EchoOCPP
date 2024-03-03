#ifndef ECHOOCPP_Meter_HPP
#define ECHOOCPP_Meter_HPP
#include <optional>

#include <optional>

class Meter {
public:
  Meter() = default;

  void reset() {
    l1_watt_W.reset();
    l2_watt_W.reset();
    l3_watt_W.reset();
    l1_l2_watt_W.reset();
    l2_l3_watt_W.reset();
    l3_l1_watt_W.reset();
    l1_n_watt_W.reset();
    l2_n_watt_W.reset();
    l3_n_watt_W.reset();
    neutral_watt_W.reset();
    l1_ampere_A.reset();
    l2_ampere_A.reset();
    l3_ampere_A.reset();
    l1_l2_ampere_A.reset();
    l2_l3_ampere_A.reset();
    l3_l1_ampere_A.reset();
    l1_n_ampere_A.reset();
    l2_n_ampere_A.reset();
    l3_n_ampere_A.reset();
    neutral_ampere_A.reset();
    energy_Wh.reset();
  }

  std::optional<float> l1_watt_W{std::nullopt};
  std::optional<float> l2_watt_W{std::nullopt};
  std::optional<float> l3_watt_W{std::nullopt};
  std::optional<float> l1_l2_watt_W{std::nullopt};
  std::optional<float> l2_l3_watt_W{std::nullopt};
  std::optional<float> l3_l1_watt_W{std::nullopt};
  std::optional<float> l1_n_watt_W{std::nullopt};
  std::optional<float> l2_n_watt_W{std::nullopt};
  std::optional<float> l3_n_watt_W{std::nullopt};
  std::optional<float> neutral_watt_W{std::nullopt};
  std::optional<float> l1_ampere_A{std::nullopt};
  std::optional<float> l2_ampere_A{std::nullopt};
  std::optional<float> l3_ampere_A{std::nullopt};
  std::optional<float> l1_l2_ampere_A{std::nullopt};
  std::optional<float> l2_l3_ampere_A{std::nullopt};
  std::optional<float> l3_l1_ampere_A{std::nullopt};
  std::optional<float> l1_n_ampere_A{std::nullopt};
  std::optional<float> l2_n_ampere_A{std::nullopt};
  std::optional<float> l3_n_ampere_A{std::nullopt};
  std::optional<float> neutral_ampere_A{std::nullopt};
  std::optional<float> energy_Wh{std::nullopt};
};


#endif