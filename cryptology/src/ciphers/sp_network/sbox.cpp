#include <cryptology/ciphers/sp_network/sbox.hpp>
#include <numeric>

using namespace std;


bool SBox::has_duplicates(std::vector<uint64_t> permutation) {
    std::unordered_map<uint64_t, size_t> m;
    for (const auto &e: permutation) {
        ++m[e];
        if (m[e] > 1)
            return true;
    }
    return false;
}

SBox::SBox(size_t input_size, size_t output_size,
           std::vector<uint64_t> permutation) {
    if (permutation.size() != std::pow(2, input_size)) {
        throw runtime_error("The size of the mapping must be 2 to the power "
                            "of the input_size_.");
    }
    if (output_size > 64) {
        throw runtime_error("Output size greater than 64 bit is not supported"
                            ".");
    }
    if (input_size > output_size) {
        throw runtime_error("input_size_ must be smaller or equal to "
                            "output_size_.");
    }
    if (has_duplicates(permutation)) {
        throw runtime_error("SBox map is not invertible.");
    }
    this->input_size_ = input_size;
    this->output_size_ = output_size;
    this->mapping = permutation;
    for (size_t i = 0; i < this->mapping.size(); ++i) {
        this->inverse_mapping[this->mapping[i]] = i;
    }
}

DynamicBitset SBox::forward(DynamicBitset input) {
    if (input.size() != this->input_size_) {
        throw runtime_error("the input size to the SBox does not match the "
                            "size of its mapping inputs.");
    }
    return {this->mapping[input.to_uint64()], output_size_};
}

DynamicBitset SBox::backward(DynamicBitset input) {
    if (input.size() != this->output_size_) {
        throw runtime_error("the input size to the inverse SBox does not match "
                            "the output_size_ of its mapping inputs.");
    }
    return {this->inverse_mapping[input.to_uint64()], input_size_};
}

size_t SBox::input_size() {
    return this->input_size_;
}

size_t SBox::ouput_size() {
    return this->output_size_;
}
