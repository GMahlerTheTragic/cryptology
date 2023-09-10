#include <cryptology/ciphers/sp_network/sp_network.hpp>
#include <vector>
#include <set>

#ifndef CRYPTOLOGY_LINEAR_ATTACK_WORKED_HPP
#define CRYPTOLOGY_LINEAR_ATTACK_WORKED_HPP

using namespace std;

class LinearAttackWorker {

private:
    SpNetwork sp_network;

public:
    LinearAttackWorker(SpNetwork sp_network);

    vector<DynamicBitset> generate_single_sbox_inputs_for_traces();

    multiset<LinearTrace> generate_linear_traces_from_inputs(
            vector<DynamicBitset> inputs_for_trace_generation);

    vector<pair<DynamicBitset, DynamicBitset>>
    generate_random_plain_cipher_pairs(size_t count);

    vector<pair<DynamicBitset, DynamicBitset>>
    partial_decrypt_plain_cipher_pairs(vector<DynamicBitset> &round_keys,
                                       vector<pair<DynamicBitset,
                                               DynamicBitset>> pairs);

    DynamicBitset estimate_best_round_key_candidate(vector<pair<DynamicBitset,
            DynamicBitset>> &pairs, vector<DynamicBitset> &key_candidates,
                                                    bool is_last_round,
                                                    DynamicBitset active_inputs,
                                                    DynamicBitset active_outputs);
};


#endif //CRYPTOLOGY_LINEAR_ATTACK_WORKED_HPP
