#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <cstdint>
#include <stdexcept>

#include "cryptology/algebra/algorithms.hpp"
#include "cryptology/algebra/matrix.hpp"
#include "cryptology/analysis/frequencies.hpp"
#include "cryptology/analysis/linear_attack/linear_attack_worker.hpp"
#include "cryptology/analysis/statistics.hpp"
#include "cryptology/ciphers/affine_cipher.hpp"
#include "cryptology/ciphers/hill_cipher.hpp"
#include "cryptology/ciphers/sp_network/sp_network.hpp"
#include "cryptology/ciphers/stream_cipher.hpp"
#include "cryptology/utils/utils.hpp"

using std::cout;
using std::pow;
using std::vector;

constexpr int kline_length = 40;
constexpr uint8_t knumber_of_letters = 26;
constexpr uint8_t ktop_results_to_disply = 100;
constexpr char kfill_character = '-';
const string kline(kline_length, kfill_character);

void AdditiveBruteForce(const string &ciphertext) {
    priority_queue<pair<double, string>> result_pq = priority_queue<pair<double, string>>();
    cout << endl;
    cout << "Starting brute force attack against additive cipher..." << endl;
    map<string, int> result = compute_letter_counts(ciphertext);
    for (int i = 0; i < knumber_of_letters; ++i) {
        AffineCipher affine_cipher = AffineCipher(i, 1);
        string candidate = affine_cipher.decrypt(ciphertext);
        double ios = index_of_similarity(candidate);
        result_pq.emplace(ios, candidate);
    }
    cout << endl;
    cout << "Listing possible plain text sorted by ioc:" << endl;
    cout << endl;

    for (int i = 0; i < knumber_of_letters; ++i) {
        pair<double, string> candidate_pair = result_pq.top();
        result_pq.pop();
        cout << candidate_pair.second << "    ioc: " << candidate_pair.first << endl;
    }

    cout << endl;
}

vector<string> AdditiveFrequencyBased(const string &ciphertext) {
    priority_queue<pair<double, string>> result_pq = priority_queue<pair<double, string>>();
    for (int i = 0; i < knumber_of_letters; i++) {
        AffineCipher affine_cipher = AffineCipher(i, 1);
        string plain_text_candidate = affine_cipher.decrypt(ciphertext);
        double ios = index_of_similarity(plain_text_candidate);
        string key = {pos_to_letter(i)};
        result_pq.emplace(ios, key);
    }
    vector<string> result = vector<string>(2);
    for (int i = 0; i < 2; i++) {
        result[i] = result_pq.top().second;
        result_pq.pop();
    }
    return result;
}

void VigenereAttack(string ciphertext) {
    cout << "Starting Index of Coincidence based attack on Vigenere cipher..." << endl;
    const size_t ct_len = ciphertext.length();
    double ioc = index_of_coincidence(ciphertext);
    cout << endl;
    cout << "ioc of cipher text is: " << ioc << endl;
    priority_queue<pair<double, int>> possible_periods = priority_queue<pair<double, int>>();
    for (int assumed_period_length = 1; assumed_period_length <= ct_len; assumed_period_length++) {
        double delta = -abs(expected_ioc(assumed_period_length, ct_len) - ioc);
        possible_periods.emplace(delta, assumed_period_length);
    }
    priority_queue<pair<double, string>> result = priority_queue<pair<double, string>>();
    for (int i = 0; i < 3; i++) {
        double delta = possible_periods.top().first;
        int assumed_key_period = possible_periods.top().second;
        possible_periods.pop();
        cout << "Guess for period (key word length): " << assumed_key_period << " Delta to expected ioc: " << delta << endl;
        vector<string> columns = vector<string>(assumed_key_period);
        for (int idx = 0; idx < assumed_key_period; idx++) {
            columns[idx] = "";
        }
        for (int idx = 0; idx < ct_len; idx++) {
            columns[idx % assumed_key_period] += {ciphertext[idx]};
        }
        vector<vector<string>> letter_combinations = vector<vector<string>>(assumed_key_period);
        for (int idx = 0; idx < assumed_key_period; idx++) {
            vector<string> additive_candidates = AdditiveFrequencyBased(columns[idx]);
            letter_combinations[idx] = additive_candidates;
        }

        vector<vector<int>> idx_combs = tuples(2, assumed_key_period);

        for (auto & idx_comb : idx_combs) {
            string key_candidate;
            for (int idx = 0; idx < assumed_key_period; idx++) {
                key_candidate += letter_combinations[idx][idx_comb[idx]];
            }
            VigenereCipher vigenere_cipher = VigenereCipher(key_candidate);
            string plain_text_candidate = vigenere_cipher.decrypt(ciphertext);
            result.emplace(index_of_similarity(plain_text_candidate),
                                  plain_text_candidate + " key: " + key_candidate);
        }
    }
    cout << endl;
    cout << "Listing plain text guesses and key word in order of ioc: " << endl;
    for (size_t result_counter = 0; result_counter < ktop_results_to_disply; result_counter++) {
        if (result.empty()) {
            break;
        }
        pair<double, string> result_pair = result.top();
        cout << result_pair.second << " " << result_pair.first << endl;
        result.pop();
    }
}

void LinearAttack(const SpNetwork& sp_network) {
    LinearAttackWorker attack_worker = LinearAttackWorker(sp_network);
    vector<DynamicBitset> inputs_for_trace_generation =
        attack_worker.generate_single_sbox_inputs_for_traces();
    multiset<LinearTrace> linear_traces =
        attack_worker.generate_linear_traces_from_inputs(inputs_for_trace_generation);

    size_t sbox_size = sp_network.sbox_size();

    auto traces_iterator = linear_traces.rbegin();
    cout << endl;
    cout << "Starting linear attack on last round key..." << endl;
    cout << "===========================================" << endl;

    DynamicBitset round_key = DynamicBitset(sp_network.block_size());

    DynamicBitset number_set = DynamicBitset(
        static_cast<uint64_t>(pow(2, sp_network.sbox_size()) - 1), sp_network.sbox_size());

    cout << "Trying to find linear trace with either one or two active SBoxes." << endl;
    while (traces_iterator != linear_traces.rend() && !number_set.is_zero()) {
        LinearTrace best_trace = *traces_iterator;
        ++traces_iterator;
        bool contains_more = false;
        size_t n_act = 0;
        cout << " Active Sboxes: [";
        for (size_t i = 0; i < sp_network.n_parallel_sboxes(); i++) {
            DynamicBitset slice = best_trace.GetActiveOuput(sp_network.rounds() - 3)
                                      .slice(i * sbox_size, (i + 1) * sbox_size);

            if (!slice.is_zero()) {
                n_act += 1;
            }
            if (number_set.test(i) && !slice.is_zero()) {
                contains_more = true;
                cout << "_" << i << "_ ";
            } else {
                cout << "___ ";
            }
        }
        cout << "]" << endl;
        if (n_act > 2) {
            continue;
        }
        if (!contains_more) {
            continue;
        }

        auto count = static_cast<size_t>(5 * pow(best_trace.GetBias(), -2));
        cout << "Success." << endl;
        cout << "Bias of linear trace is: " << best_trace.GetBias() <<  endl;
        cout << "Generating " << count << " random pairs according to linear trace bias..." << endl;
        cout << "number of samples has to be approx. c * bias^{-2}. We choose c = 5" << endl;

        vector<pair<DynamicBitset, DynamicBitset>> pairs =
            attack_worker.generate_random_plain_cipher_pairs(count);

        cout << "Done." << endl;

        vector<vector<DynamicBitset>> prefixes_list;
        DynamicBitset active_inputs = best_trace.GetInput();
        DynamicBitset active_outputs = best_trace.GetActiveOuput(sp_network.rounds() - 3);

        for (size_t i = 0; i < sp_network.n_parallel_sboxes(); i++) {
            vector<DynamicBitset> prefixes;
            DynamicBitset slice = active_outputs.slice(i * sbox_size, (i + 1) * sbox_size);
            if (slice.is_zero()) {
                prefixes.emplace_back(0, sp_network.sbox_size());
            } else {
                for (uint64_t j = 0; j < static_cast<uint64_t>(pow(2, sp_network.sbox_size()));
                     j++) {
                    prefixes.emplace_back(j, sp_network.sbox_size());
                }
            }
            prefixes_list.push_back(prefixes);
        }

        vector<DynamicBitset> possible_keys = generateCombinations(prefixes_list);

        cout << "evaluating " << possible_keys.size() << " key candidates..." << endl;

        DynamicBitset max_key = attack_worker.estimate_best_round_key_candidate(
            pairs, possible_keys, true, active_inputs, active_outputs);
        for (size_t i = 0; i < sp_network.n_parallel_sboxes(); i++) {
            size_t begin = i * sp_network.sbox_size();
            size_t end = begin + sp_network.sbox_size();

            if (number_set.test(i) && !active_outputs.slice(begin, end).is_zero()) {
                number_set.clear(i);
                DynamicBitset key_slice = max_key.slice(begin, end);
                for (size_t j = begin; j < end; j++) {
                    if (key_slice.test(j - begin)) {
                        round_key.set(j);
                    }
                }
            }
        }
    }
    cout << "Finished." << endl;
    cout << "Found the following guess for the last round key: ";
    round_key.print();
}