#include <numeric>
#include <stdexcept>
#include "cryptology/ciphers/sp_network/pbox.hpp"

using std::runtime_error;

bool PBox::is_permutation(std::vector<unsigned int> permutation) {
    std::vector<unsigned int> identity_permutation(permutation.size());
    std::iota(identity_permutation.begin(), identity_permutation.end(), 0);
    return std::is_permutation(identity_permutation.begin(), identity_permutation.end(),
                               permutation.begin());
}

PBox::PBox(const std::vector<unsigned int> &permutation) {
    if (!is_permutation(permutation)) {
        throw runtime_error("The passed vector is not a permutation");
    }
    this->permutation = permutation;
    std::vector<unsigned int> inverse_permutation_values(permutation.size(), 0);
    for (size_t i = 0; i < permutation.size(); i++) {
        inverse_permutation_values[permutation[i]] = i;
    }
    this->inverse_permutation = inverse_permutation_values;
}

DynamicBitset PBox::forward(const DynamicBitset &input) const {
    if (input.size() != this->permutation.size()) {
        throw runtime_error(
            "the input size to the PBox does not match the "
            "size of its permutation.");
    }
    DynamicBitset result = DynamicBitset(input.size());

    for (size_t i = 0; i < input.size(); i++) {
        if (input.test(i)) {
            result.set(this->permutation[i]);
        }
    }
    return result;
}

DynamicBitset PBox::backward(const DynamicBitset &input) const {
    DynamicBitset result = DynamicBitset(input.size());
    for (size_t i = 0; i < input.size(); i++) {
        if (input.test(i)) {
            result.set(this->inverse_permutation[i]);
        }
    }
    return result;
}

size_t PBox::size() const { return this->permutation.size(); }
