#ifndef CRYPTOLOGY_LINEAR_ATTACK_WORKER_HPP
#define CRYPTOLOGY_LINEAR_ATTACK_WORKER_HPP

#include <cryptology/ciphers/sp_network/sp_network.hpp>
#include <set>
#include <vector>



using namespace std;

class LinearAttackWorker {
   private:
    SpNetwork sp_network;

   public:
    explicit LinearAttackWorker(SpNetwork sp_network);

    vector<DynamicBitset> generate_single_sbox_inputs_for_traces() const;

    multiset<LinearTrace> generate_linear_traces_from_inputs(
        const vector<DynamicBitset> &inputs_for_trace_generation);

    vector<pair<DynamicBitset, DynamicBitset>> generate_random_plain_cipher_pairs(size_t count);

    vector<pair<DynamicBitset, DynamicBitset>> partial_decrypt_plain_cipher_pairs(
        const vector<DynamicBitset> &round_keys, vector<pair<DynamicBitset, DynamicBitset>> pairs);

    DynamicBitset estimate_best_round_key_candidate(
        const vector<pair<DynamicBitset, DynamicBitset>> &pairs,
        const vector<DynamicBitset> &key_candidates,
        bool is_last_round, const DynamicBitset &active_inputs, const DynamicBitset &active_outputs);
};

#endif