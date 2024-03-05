//#ifndef ECHOOCPP_UTILIES_HPP
//#define ECHOOCPP_UTILIES_HPP
//
#pragma once
#include "uuid.h"
#include <nlohmann/json.hpp>
#include "openssl/sha.h"

namespace Utility {


template <typename T>
inline std::string toJsonString(const T& data) {
  std::string result;
  try {
    nlohmann::json tmp = data;
    result = tmp.dump();
  } catch (std::exception &e) {
    result = "";
  }
  return result;
}
/**
 * @brief Generates a random message ID using the stduuid library.
 *
 * This function uses a random device and the Mersenne Twister engine (std::mt19937)
 * to create a seed for the UUID generator. The generated UUID is then converted
 * to a string representation and returned.
 *
 * @return A string representing the randomly generated message ID.
 */
static inline std::string generateMessageId()
{
  // Use std::random_device to obtain a random seed
  std::random_device rd;

  // Generate an array of random integers to be used as seed data
  auto seed_data = std::array<int, std::mt19937::state_size> {};
  std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));

  // Use std::seed_seq to create a seed sequence from the generated data
  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));

  // Create an Mersenne Twister engine with the generated seed
  std::mt19937 generator(seq);

  // Use uuids::uuid_random_generator with the Mersenne Twister engine
  uuids::uuid_random_generator gen{generator};

  // Convert the generated UUID to a string and return it
  return uuids::to_string(gen());
}


}
//#endif // ECHOOCPP_UTILIES_HPP
