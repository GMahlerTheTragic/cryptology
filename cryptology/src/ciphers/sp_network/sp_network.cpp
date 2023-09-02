#include <cryptology/ciphers/sp_network/sp_network.hpp>
#include <iostream>

SpNetwork::SpNetwork(PBox &p_box, SBox &s_box, size_t block_size,
                     size_t n_rounds,
                     std::vector<DynamicBitset> &round_keys) : p_box(p_box),
                                                               s_box(s_box),
                                                               round_keys(
                                                                       round_keys) {
    if (n_rounds <= 0) {
        throw std::runtime_error("SP Networks have to have a "
                                 "positive number of rounds.");
    }
    if (block_size != p_box.size()) {
        throw std::runtime_error("Block size must be equal to the PBox size");
    }
    if (block_size % s_box.input_size() != 0) {
        throw std::runtime_error("Block Size has to be a multiple of SBox "
                                 "size");
    }
    if (s_box.input_size() != s_box.ouput_size()) {
        throw std::runtime_error("Currently SBoxes have to have equal input "
                                 "and output sizes");
    }
    this->s_box = s_box;
    this->p_box = p_box;
    this->block_size = block_size;
    this->n_rounds = n_rounds;
    this->round_keys = round_keys;
}

DynamicBitset SpNetwork::encrypt_block(DynamicBitset input) {
    if (input.size() != this->block_size) {
        throw std::runtime_error("input lenght has to be the same as the "
                                 "block size of the SPN");
    }
    DynamicBitset result = input;
    for (size_t i = 0; i < this->round_keys.size() - 2; ++i) {
        result = result + this->round_keys[i % n_rounds];
        result = this->apply_sbox(result);
        result = this->apply_pbox(result);
    }
    result = result + this->round_keys[this->round_keys.size() - 2];
    result = this->apply_sbox(result);
    result = result + this->round_keys[this->round_keys.size() - 1];
    return result;
}

DynamicBitset SpNetwork::apply_sbox(DynamicBitset input) {
    size_t s_box_in_size = this->s_box.input_size();
    if (input.size() % s_box_in_size != 0) {
        throw std::runtime_error("input block length must be a multiple of "
                                 "the SBox input_size");
    }
    size_t n_sbox_blocks = input.size() / s_box_in_size;
    DynamicBitset result = DynamicBitset(0);
    for (size_t i = 0; i < n_sbox_blocks; i++) {
        size_t offset = i * s_box_in_size;
        DynamicBitset block_result = this->s_box.forward(
                input.slice(offset, offset + s_box_in_size));
        result = result.concat(block_result);
    }
    return result;
}

DynamicBitset SpNetwork::apply_pbox(DynamicBitset input) {
    if (input.size() != this->p_box.size()) {
        throw std::runtime_error("input block length must be equal to the "
                                 "PBox size");
    }
    return this->p_box.forward(input);
}
