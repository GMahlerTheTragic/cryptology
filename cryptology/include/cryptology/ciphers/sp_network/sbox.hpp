#ifndef CRYPTOLOGY_SBOX_HPP
#define CRYPTOLOGY_SBOX_HPP

#include <cstddef>
#include <vector>
#include "cryptology/utils/dynamic_bitset.hpp"
#include <map>

class SBox {
private:
    static bool has_duplicates(std::vector<uint64_t> permutation);

    size_t input_size_;
    size_t output_size_;
    std::vector<uint64_t> mapping;
    std::map<uint64_t, uint64_t> inverse_mapping;

public:
    SBox(size_t input_size, size_t output_size,
         std::vector<uint64_t> permutation);

    size_t ouput_size();

    size_t input_size();

    DynamicBitset forward(DynamicBitset);

    DynamicBitset backward(DynamicBitset);

};

#endif
