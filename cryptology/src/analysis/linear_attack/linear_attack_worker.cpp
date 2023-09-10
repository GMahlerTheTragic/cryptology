#include <vector>
#include <cryptology/utils/utils.hpp>
#include <cryptology/analysis/linear_attack/linear_attack_worker.hpp>
#include <random>
#include <unordered_set>
#include <set>

using namespace std;

LinearAttackWorker::LinearAttackWorker(SpNetwork sp_network) : sp_network(
        sp_network) {
    this->sp_network = sp_network;
}

vector<DynamicBitset>
LinearAttackWorker::generate_single_sbox_inputs_for_traces() {
    vector<DynamicBitset> inputs_for_trace_generation;
    for (size_t i = 0; i < this->sp_network.n_parallel_sboxes(); i++) {
        for (uint64_t sbox_input = 1;
             sbox_input < pow(2, this->sp_network.sbox_size());
             sbox_input++) {
            DynamicBitset input_vector =
                    DynamicBitset(
                            sbox_input << (i * this->sp_network.sbox_size()),
                            16);
            inputs_for_trace_generation.push_back(input_vector);
        }
    }
    return inputs_for_trace_generation;
}

multiset<LinearTrace>
LinearAttackWorker::generate_linear_traces_from_inputs
        (vector<DynamicBitset> inputs_for_trace_generation) {
    multiset<LinearTrace> linear_traces;
    for (auto input: inputs_for_trace_generation) {
        LinearTrace trace = sp_network.generate_trace(input);
        trace.print();
        linear_traces.insert(trace);
    }
    return linear_traces;
}

vector<pair<DynamicBitset, DynamicBitset>>
LinearAttackWorker::generate_random_plain_cipher_pairs(size_t count) {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> distribution(
            0,
            std::pow(2, this->sp_network.block_size()) - 1);

    unordered_set<uint64_t> random_numbers;
    vector<pair<DynamicBitset, DynamicBitset>> pairs;

    while (pairs.size() < count) {
        uint64_t randomNumber = distribution(gen);
        if (random_numbers.contains(randomNumber)) {
            continue;
        }
        // Check if the generated number is already in the set
        random_numbers.insert(randomNumber);
        DynamicBitset x = DynamicBitset(randomNumber,
                                        this->sp_network.block_size());
        DynamicBitset y = sp_network.encrypt_block(x);
        pair<DynamicBitset, DynamicBitset> pair = make_pair(x, y);
        pairs.push_back(pair);
    }
    return pairs;
}

vector<pair<DynamicBitset, DynamicBitset>>
LinearAttackWorker::partial_decrypt_plain_cipher_pairs(
        vector<DynamicBitset> &round_keys,
        vector<pair<DynamicBitset, DynamicBitset>> pairs) {
    if (round_keys.size() <= 0) {
        return pairs;
    }
    for (auto &e: pairs) {
        for (size_t k = 0; k < round_keys.size(); k++) {
            e.second = e.second + round_keys[k];
            if (k > 1) {
                e.second = sp_network.apply_pbox_inv(e.second);
            }
            e.second = sp_network.apply_sbox_inv(e.second);
        }
    }
    return pairs;
}

DynamicBitset LinearAttackWorker::estimate_best_round_key_candidate(
        vector<pair<DynamicBitset, DynamicBitset>> &pairs,
        vector<DynamicBitset> &key_candidates, bool is_last_round,
        DynamicBitset active_inputs, DynamicBitset active_outputs) {
    double max = -1;
    DynamicBitset max_key = DynamicBitset(0, 16);

    long counter = 0;
    for (const auto &comb: key_candidates) {
        counter++;
        double alpha = 0;
        for (const auto &pair: pairs) {
            DynamicBitset x = pair.first;
            DynamicBitset y = pair.second;
            DynamicBitset v = comb + y;
            if (!is_last_round) {
                v = sp_network.apply_pbox_inv(v);
            }
            DynamicBitset u = sp_network.apply_sbox_inv(v);
            if (!((x * active_inputs) ^ (u * active_outputs))) {
                alpha++;
            }
        }


        double halfSet = (double) pairs.size() / 2.;
        alpha = abs(alpha - halfSet);


        if (alpha >= max) {
            max = alpha;
            max_key = comb;
            cout << alpha << endl;
            max_key.print();
        }
        if (counter % 100 == 0) {
            cout << "finished " << counter << endl;
        }
    }
    return max_key;
}

