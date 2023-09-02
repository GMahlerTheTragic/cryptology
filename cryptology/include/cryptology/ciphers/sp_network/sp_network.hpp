#include "pbox.hpp"
#include "sbox.hpp"
#include <bitset>

#ifndef CRYPTOLOGY_SP_NETWORK_HPP
#define CRYPTOLOGY_SP_NETWORK_HPP

#endif

class SpNetwork {
private:
    PBox p_box;
    SBox s_box;
    size_t block_size;
    size_t n_rounds;
    std::vector<DynamicBitset> round_keys;

    DynamicBitset apply_sbox(DynamicBitset input);

    DynamicBitset apply_pbox(DynamicBitset input);

public:
    SpNetwork(PBox &p_box, SBox &s_box, size_t block_size,
              size_t n_rounds, std::vector<DynamicBitset> &round_keys);

    DynamicBitset encrypt_block(DynamicBitset input);

    DynamicBitset decrypt_block(DynamicBitset input);
};
