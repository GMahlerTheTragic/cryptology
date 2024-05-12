#ifndef CRYPTOLOGY_SP_NETWORK_HPP
#define CRYPTOLOGY_SP_NETWORK_HPP

#include <vector>

#include "cryptology/analysis/linear_attack/linear_approximation.hpp"
#include "cryptology/analysis/linear_attack/linear_trace.hpp"
#include "pbox.hpp"
#include "sbox.hpp"



using namespace std;

class SpNetwork {
   private:
    PBox p_box;
    SBox s_box;
    size_t block_size_;
    size_t n_rounds;
    std::vector<DynamicBitset> round_keys;

    DynamicBitset apply_sbox(const DynamicBitset &input);

    DynamicBitset apply_pbox(const DynamicBitset &input) const;

    vector<vector<double>> linear_approximations;

   public:
    SpNetwork(const PBox &p_box, const SBox &s_box, size_t block_size, size_t n_rounds,
              const std::vector<DynamicBitset> &round_keys);

    DynamicBitset apply_sbox_inv(const DynamicBitset &input);

    DynamicBitset apply_pbox_inv(const DynamicBitset &input) const;

    [[nodiscard]] size_t rounds() const;

    [[nodiscard]] size_t block_size() const;

    [[nodiscard]] size_t sbox_size() const;

    [[nodiscard]] size_t n_parallel_sboxes() const;

    DynamicBitset encrypt_block(const DynamicBitset &input);

    DynamicBitset decrypt_block(DynamicBitset input);

    LinearTrace generate_trace(DynamicBitset input_vector) const;

    RoundLinearApproximation compute_best_output_approximation(const DynamicBitset &input_vector,
                                                               size_t round) const;

    LinearApproximation find_best_approximation(uint64_t active_i, size_t sbox_pos) const;
};

#endif
