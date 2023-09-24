#include <cmath>
#include <cryptology/analysis/linear_attack/linear_attack_worker.hpp>
#include <cryptology/utils/utils.hpp>
#include <random>
#include <set>
#include <unordered_set>
#include <vector>

using std::cout;
using std::vector;

LinearAttackWorker::LinearAttackWorker(SpNetwork sp_network) : sp_network(sp_network) {}

vector<DynamicBitset> LinearAttackWorker::generate_single_sbox_inputs_for_traces() {
    vector<DynamicBitset> inputs_for_trace_generation;
    for (size_t i = 0; i < static_cast<size_t>(std::pow(2, this->sp_network.block_size())); i++) {
        inputs_for_trace_generation.push_back(DynamicBitset(i, this->sp_network.block_size()));
    }
    return inputs_for_trace_generation;
}

multiset<LinearTrace> LinearAttackWorker::generate_linear_traces_from_inputs(
    vector<DynamicBitset> inputs_for_trace_generation) {
    multiset<LinearTrace> linear_traces;
    for (auto input : inputs_for_trace_generation) {
        LinearTrace trace = sp_network.generate_trace(input);
        linear_traces.insert(trace);
    }
    return linear_traces;
}

vector<pair<DynamicBitset, DynamicBitset>> LinearAttackWorker::generate_random_plain_cipher_pairs(
    size_t count) {
    random_device random_device;
    mt19937_64 gen(random_device());
    uniform_int_distribution<uint64_t> distribution(
        0, static_cast<uint64_t>(std::pow(2, this->sp_network.block_size()) - 1));

    unordered_set<uint64_t> random_numbers;
    vector<pair<DynamicBitset, DynamicBitset>> pairs;

    while (pairs.size() < count) {
        uint64_t random_number = distribution(gen);
        if (random_numbers.contains(random_number)) {
            continue;
        }

        // Check if the generated number is already in the set
        random_numbers.insert(random_number);
        DynamicBitset plain_bits = DynamicBitset(random_number, this->sp_network.block_size());
        DynamicBitset cipher_bits = sp_network.encrypt_block(plain_bits);
        pair<DynamicBitset, DynamicBitset> pair = make_pair(plain_bits, cipher_bits);
        pairs.push_back(pair);
    }
    return pairs;
}

vector<pair<DynamicBitset, DynamicBitset>> LinearAttackWorker::partial_decrypt_plain_cipher_pairs(
    vector<DynamicBitset> &round_keys, vector<pair<DynamicBitset, DynamicBitset>> pairs) {
    if (round_keys.empty()) {
        return pairs;
    }
    for (auto &element : pairs) {
        for (size_t k = 0; k < round_keys.size(); k++) {
            element.second = element.second + round_keys[k];
            if (k > 1) {
                element.second = sp_network.apply_pbox_inv(element.second);
            }
            element.second = sp_network.apply_sbox_inv(element.second);
        }
    }
    return pairs;
}

DynamicBitset LinearAttackWorker::estimate_best_round_key_candidate(
    vector<pair<DynamicBitset, DynamicBitset>> &pairs, vector<DynamicBitset> &key_candidates,
    bool is_last_round, DynamicBitset active_inputs, DynamicBitset active_outputs) {
    double max = -1;
    DynamicBitset max_key = DynamicBitset(0, this->sp_network.block_size());

    int64_t counter = 0;
    for (const auto &comb : key_candidates) {
        counter++;
        double alpha = 0;
        for (const auto &pair : pairs) {
            DynamicBitset plain_bits = pair.first;
            DynamicBitset cipher_bits = pair.second;
            DynamicBitset v_bits = comb + cipher_bits;
            if (!is_last_round) {
                v_bits = sp_network.apply_pbox_inv(v_bits);
            }

            DynamicBitset u_bits = this->sp_network.apply_sbox_inv(v_bits);
            if (((plain_bits * active_inputs) ^ (u_bits * active_outputs)) == 0) {
                alpha++;
            }
        }

        const double half_set = static_cast<double>(pairs.size()) / 2.;
        alpha = abs(alpha - half_set);

        if (alpha > max) {
            max = alpha;
            max_key = comb;
        }
        cout << "\rfinished [" << counter << "/ " << key_candidates.size() << ']';
        cout.flush();
    }
    cout << endl;
    return max_key;
}
