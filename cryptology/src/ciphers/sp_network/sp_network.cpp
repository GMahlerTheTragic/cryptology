#include <cryptology/ciphers/sp_network/sp_network.hpp>
#include <cmath>
#include "cryptology/analysis/linear_attack/linear_approximation.hpp"
#include "cryptology/analysis/linear_attack/linear_trace.hpp"

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
  this->block_size_ = block_size;
  this->n_rounds = n_rounds;
  this->round_keys = round_keys;
  this->linear_approximations =
      this->s_box.compute_linear_approximation_table();
}

size_t SpNetwork::sbox_size() {
  return this->s_box.input_size();
}

size_t SpNetwork::block_size() {
  return this->block_size_;
}

size_t SpNetwork::rounds() {
  return this->n_rounds;
}

size_t SpNetwork::n_parallel_sboxes() {
  return this->block_size_ / this->sbox_size();
}

DynamicBitset SpNetwork::encrypt_block(DynamicBitset input) {
  if (input.size() != this->block_size_) {
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
  if (input.size() % this->sbox_size() != 0) {
    throw std::runtime_error("input block length must be a multiple of "
                             "the SBox input_size");
  }
  DynamicBitset result = DynamicBitset(0);
  for (size_t i = 0; i < this->n_parallel_sboxes(); i++) {
    size_t offset = i * this->sbox_size();
    DynamicBitset block_result = this->s_box.forward(
        input.slice(offset, offset + this->sbox_size()));
    result = result.concat(block_result);
  }
  return result;
}

DynamicBitset SpNetwork::apply_sbox_inv(DynamicBitset input) {
  if (input.size() % this->sbox_size() != 0) {
    throw std::runtime_error("input block length must be a multiple of "
                             "the SBox input_size");
  }
  DynamicBitset result = DynamicBitset(0);
  for (size_t i = 0; i < this->n_parallel_sboxes(); i++) {
    size_t offset = i * this->sbox_size();
    DynamicBitset block_result = this->s_box.backward(
        input.slice(offset, offset + this->sbox_size()));
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

DynamicBitset SpNetwork::apply_pbox_inv(DynamicBitset input) {
  if (input.size() != this->p_box.size()) {
    throw std::runtime_error("input block length must be equal to the "
                             "PBox size");
  }
  return this->p_box.backward(input);
}

LinearTrace SpNetwork::generate_trace(DynamicBitset input_vector) {
  LinearTrace linear_trace = LinearTrace(input_vector);
  for (size_t round = 0; round < this->n_rounds - 2; round++) {
    RoundLinearApproximation round_linear_approximation
        = this->compute_best_output_approximation(input_vector, round);
    input_vector = round_linear_approximation.active_outputs;
    linear_trace.add(round_linear_approximation);
  }
  return linear_trace;
}

RoundLinearApproximation
SpNetwork::compute_best_output_approximation(DynamicBitset
                                             input_vector, size_t round) {
  DynamicBitset active_outputs = DynamicBitset(0);
  std::vector<LinearApproximation> round_approximations;
  for (size_t i = 0; i < this->n_parallel_sboxes(); i++) {
    size_t begin = i * this->sbox_size();
    size_t end = begin + this->sbox_size();
    DynamicBitset slice = input_vector.slice(begin, end);
    if (!slice.is_zero()) {
      LinearApproximation best_approx = this->find_best_approximation(
          slice.to_uint64(), i);
      round_approximations.push_back(best_approx);
      active_outputs = active_outputs.concat(DynamicBitset(best_approx
                                                               .active_outputs,
                                                           this->sbox_size()));
    } else {
      active_outputs = active_outputs.concat(
          DynamicBitset(this->sbox_size()));
    }

  }
  return {round_approximations, round, this->apply_pbox(active_outputs)};
}

LinearApproximation SpNetwork::find_best_approximation(uint64_t active_i,
                                                       size_t sbox_pos) {
  double best_bias = 0;
  uint64_t best_active_o = 0;
  for (uint64_t active_o = 0; active_o < std::pow(2, this->s_box.ouput_size
      ());
       active_o++) {
    double bias = this->linear_approximations[active_i][active_o];
    if (std::abs(bias) > std::abs(best_bias)) {
      best_bias = bias;
      best_active_o = active_o;
    }
  }
  return {
      best_bias,
      best_active_o
  };
}
