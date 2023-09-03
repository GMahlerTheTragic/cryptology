#include "pbox.hpp"
#include "sbox.hpp"
#include "cryptology/analysis/linear_attack/linear_trace.hpp"
#include "cryptology/analysis/linear_attack/linear_approximation.hpp"
#include <bitset>
#include <map>
#include <vector>

#ifndef CRYPTOLOGY_SP_NETWORK_HPP
#define CRYPTOLOGY_SP_NETWORK_HPP


using namespace std;

class SpNetwork {
private:
    PBox p_box;
    SBox s_box;
    size_t block_size_;
    size_t n_rounds;
    std::vector<DynamicBitset> round_keys;

    DynamicBitset apply_sbox(DynamicBitset input);

    DynamicBitset apply_pbox(DynamicBitset input);

    vector<vector<double>> linear_approximations;

public:
    SpNetwork(PBox &p_box, SBox &s_box, size_t block_size,
              size_t n_rounds, std::vector<DynamicBitset> &round_keys);

    DynamicBitset apply_sbox_inv(DynamicBitset input);

    DynamicBitset apply_pbox_inv(DynamicBitset input);

    size_t rounds();

    size_t block_size();

    size_t sbox_size();

    size_t n_parallel_sboxes();

    DynamicBitset encrypt_block(DynamicBitset input);

    DynamicBitset decrypt_block(DynamicBitset input);

    LinearTrace generate_trace(DynamicBitset input_vector);

    RoundLinearApproximation compute_best_output_approximation(DynamicBitset
                                                               input_vector,
                                                               size_t round);

    LinearApproximation find_best_approximation(uint64_t active_i,
                                                size_t sbox_pos);

};

#endif
