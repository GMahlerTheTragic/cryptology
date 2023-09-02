#ifndef CRYPTOLOGY_PBOX_HPP
#define CRYPTOLOGY_PBOX_HPP


#include <vector>
#include <bitset>
#include "cryptology/utils/dynamic_bitset.hpp"

class PBox {
private:
    std::vector<unsigned int> permutation;
    std::vector<unsigned int> inverse_permutation;

    static bool is_permutation(std::vector<unsigned int> permutation);

public:
    PBox(std::vector<unsigned int> permutation);

    size_t size();

    DynamicBitset forward(DynamicBitset);

    DynamicBitset backward(DynamicBitset);

};

#endif
