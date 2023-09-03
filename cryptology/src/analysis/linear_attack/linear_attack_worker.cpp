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

