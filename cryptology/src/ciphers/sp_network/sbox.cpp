#include <cmath>

#include <iostream>
#include <map>
#include <unordered_map>
#include <stdint.h>
#include <cryptology/ciphers/sp_network/sbox.hpp>
using std::runtime_error;

constexpr uint8_t kmax_uint_size = 64;

bool SBox::has_duplicates(std::vector<uint64_t> permutation) {
    std::unordered_map<uint64_t, size_t> map;
    for (const auto &entry : permutation) {
        ++map[entry];
        if (map[entry] > 1) {
            return true;
        };
    }
    return false;
}

SBox::SBox(size_t input_size, size_t output_size, std::vector<uint64_t> permutation) {
    if (permutation.size() != static_cast<size_t>(std::pow(2, input_size))) {
        throw runtime_error(
            "The size of the mapping must be 2 to the power "
            "of the input_size_.");
    }
    if (output_size > kmax_uint_size) {
        throw runtime_error(
            "Output size greater than 64 bit is not supported"
            ".");
    }
    if (input_size > output_size) {
        throw runtime_error(
            "input_size_ must be smaller or equal to "
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
        throw runtime_error(
            "the input size to the SBox does not match the "
            "size of its mapping inputs.");
    }
    return {this->mapping[input.to_uint64()], output_size_};
}

DynamicBitset SBox::backward(DynamicBitset input) {
    if (input.size() != this->output_size_) {
        throw runtime_error(
            "the input size to the Inverse SBox does not match "
            "the output_size_ of its mapping inputs.");
    }
    return {this->inverse_mapping[input.to_uint64()], input_size_};
}

std::vector<std::vector<double>> SBox::compute_linear_approximation_table() {
    std::vector<std::vector<double>> result_matrix;
    for (uint64_t i = 0; i < std::pow(2, this->input_size_); i++) {
        std::vector<double> temp = std::vector<double>(0.);
        for (uint64_t j = 0; j < std::pow(2, this->output_size_); j++) {
            DynamicBitset active_inputs = DynamicBitset(i, this->input_size_);
            DynamicBitset active_outputs = DynamicBitset(j, this->output_size_);
            double total_ones = 0.0;
            for (uint64_t k = 0; k < this->mapping.size(); k++) {
                DynamicBitset s_box_input = DynamicBitset(k, this->input_size_);
                DynamicBitset s_box_output = DynamicBitset(this->mapping[k], this->output_size_);
                total_ones += (s_box_input * active_inputs) ^ (s_box_output * active_outputs);
            }
            double bias = std::abs(((16 - total_ones) / (std::pow(2, this->input_size_))) - 0.5);
            temp.push_back(bias);
        }
        result_matrix.push_back(temp);
    }
    return result_matrix;
}

size_t SBox::input_size() const { return this->input_size_; }

size_t SBox::ouput_size() const { return this->output_size_; }
