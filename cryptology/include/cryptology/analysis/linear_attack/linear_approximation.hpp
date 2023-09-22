#ifndef CRYPTOLOGY_LINEAR_APPROXIMATION_HPP
#define CRYPTOLOGY_LINEAR_APPROXIMATION_HPP

#include <cstddef>
#include <cstdint>
#include "cryptology/utils/dynamic_bitset.hpp"

struct LinearApproximation {
  double bias;
  uint64_t active_outputs;
};

struct RoundLinearApproximation {
  std::vector<LinearApproximation> linear_approximations;
  size_t round;
  DynamicBitset active_outputs;
};

#endif //CRYPTOLOGY_LINEAR_APPROXIMATION_HPP
