#include <cryptology/ciphers/sp_network/pbox.hpp>
#include <numeric>

using namespace std;

bool PBox::is_permutation(std::vector<unsigned int> permutation) {
    std::vector<unsigned int> a(permutation.size());
    std::iota(a.begin(), a.end(), 0);
    return std::is_permutation(a.begin(), a.end(),
                               permutation.begin());
}

PBox::PBox(std::vector<unsigned int> permutation) {
    if (!is_permutation(permutation)) {
        throw runtime_error("The passed vector is not a permutation");
    }
    this->permutation = permutation;
    std::vector<unsigned int> inverse_permutation(permutation.size(), 0);
    for (size_t i = 0; i < permutation.size(); i++) {
        inverse_permutation[permutation[i]] = i;
    }
    this->inverse_permutation = inverse_permutation;
}

DynamicBitset PBox::forward(DynamicBitset input) {
    if (input.size() != this->permutation.size()) {
        throw runtime_error("the input size to the PBox does not match the "
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

DynamicBitset PBox::backward(DynamicBitset input) {
    DynamicBitset result = DynamicBitset(input.size());
    for (size_t i = 0; i < input.size(); i++) {
        if (input.test(i)) {
            result.set(this->inverse_permutation[i]);
        }
    }
    return result;
}

size_t PBox::size() {
    return this->permutation.size();
}