#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <unordered_set>
#include <set>

#include <iostream>
#include <cryptology/algebra/algorithms.hpp>
#include <cryptology/algebra/matrix.hpp>
#include <cryptology/algebra/vector.hpp>
#include <cryptology/ciphers/affine_cipher.hpp>
#include <cryptology/ciphers/hill_cipher.hpp>
#include <cryptology/ciphers/stream_cipher.hpp>
#include <cryptology/analysis/frequencies.hpp>
#include <cryptology/analysis/statistics.hpp>
#include <cryptology/analysis/linear_attack/linear_attack_worker.hpp>
#include "cryptology/utils/utils.hpp"
#include <cryptology/ciphers/sp_network/sp_network.hpp>


using namespace std;
int lineLength = 40;
char fillCharacter = '-';
string line(lineLength, fillCharacter);

void additive_brute_force(string ciphertext) {
    priority_queue<pair<double, string>> result_pq = priority_queue<pair<double, string>>();
    cout << endl;
    cout << "Starting brute force attack against additive cipher" << endl;
    cout << line << endl;
    map<string, double> result = compute_letter_frequencies(ciphertext);
    for (int i = 0; i < 26; ++i) {
        AffineCipher affine_cipher = AffineCipher(i, 1);
        string candidate = affine_cipher.decrypt(ciphertext);
        double ioc = index_of_coincidence(candidate);
        result_pq.push(make_pair(ioc, candidate));
    }
    cout << endl;
    cout << "Listing possible plain text sorted by ioc:" << endl;
    cout << endl;

    for (int i = 0; i < 26; ++i) {
        pair<double, string> candidate_pair = result_pq.top();
        result_pq.pop();
        cout << candidate_pair.second << "    ioc: " << candidate_pair.first
             << endl;
    }

    cout << endl;
}

vector<string> additive_frequency_based(string ciphertext) {
    priority_queue<pair<double, string>> result_pq = priority_queue<pair<double, string>>();
    for (int i = 0; i < 26; i++) {
        AffineCipher affine_cipher = AffineCipher(i, 1);
        string plain_text_candidate = affine_cipher.decrypt(ciphertext);
        double ioc = index_of_coincidence(plain_text_candidate);
        string key = {pos_to_letter(i)};
        result_pq.push(make_pair(ioc, key));
    }
    vector<string> result = vector<string>(2);
    for (int i = 0; i < 1; i++) {
        result[i] = result_pq.top().second;
        result_pq.pop();
    }
    return result;
}

void hill_frequency_attack(string ciphertext, int n) {
    priority_queue<pair<int, string>> ngram_freqs = compute_ngramm_frequencies(
            ciphertext, n);

    vector<vector<int>> Y_vals = vector<vector<int>>(n);

    for (int i = 0; i < n; i++) {
        string ngram = ngram_freqs.top().second;
        Y_vals[i] = word_to_vec(ngram);
        ngram_freqs.pop();
    }
    Matrix<26> Y = Matrix<26>(Y_vals);


    priority_queue<pair<double, string>> ngram_freqs_language;

    for (auto [key, val]: ENGLISH_BIGRAM_FREQUENCIES) {
        ngram_freqs_language.push(make_pair(val, key));
    }

    vector<string> ngram_freqs_language_vec = vector<string>(
            ENGLISH_BIGRAM_FREQUENCIES.size());
    int i = 0;
    while (!ngram_freqs_language.empty()) {
        string ngram = ngram_freqs_language.top().second;
        ngram_freqs_language.pop();
        ngram_freqs_language_vec[i] = ngram;
        i++;
    }
    priority_queue<pair<double, string>> result = priority_queue<pair<double, string>>();
    vector<vector<int>> X_vals = vector<vector<int>>(n);
    for (int j = 0; j < 3; j++) {
        X_vals[0] = word_to_vec(ngram_freqs_language_vec[j]);
        for (int l = 0; l < 3; l++) {
            X_vals[1] = word_to_vec(ngram_freqs_language_vec[l]);
            Matrix<26> X = Matrix<26>(X_vals);
            try {
                Matrix<26> X_inv = inverse(X);
                Matrix<26> K = X_inv * Y;
                HillCipher hill_cipher = HillCipher(K);
                string plain_text_candidate = hill_cipher.decrypt(ciphertext);
                result.push(
                        make_pair(index_of_coincidence(plain_text_candidate),
                                  plain_text_candidate));
                cout << j << l << "plain text candidate: "
                     << plain_text_candidate
                     << endl;
            }
            catch (const runtime_error &e) {
                continue;
            }
        }
    }

    while (!result.empty()) {
        pair<double, string> result_pair = result.top();
        cout << result_pair.second << " " << result_pair.first << endl;
        result.pop();
    }
}

void vigenere_kasiki_attack(string ciphertext) {
    int n = ciphertext.length();
    priority_queue<pair<int, string>> ngram_freqs = compute_ngramm_frequencies(
            ciphertext, 1);
    double ioc = 0;
    while (!ngram_freqs.empty()) {
        pair<int, string> next = ngram_freqs.top();
        cout << next.second << ": " << next.first << endl;
        ioc += next.first * (next.first - 1);
        ngram_freqs.pop();
    }
    ioc = ioc / (ciphertext.length() * (ciphertext.length() - 1));
    cout << "ioc is: " << ioc << endl;
    cout << expected_ioc(10, ciphertext.length()) << endl;
    priority_queue<pair<double, int>> possible_periods = priority_queue<pair<double, int>>();
    for (int d = 1; d <= n; d++) {
        double delta = -abs(expected_ioc(d, n) - ioc);
        possible_periods.push(make_pair(delta, d));
    }
    priority_queue<pair<double, string>> result = priority_queue<pair<double, string>>();
    for (int i = 0; i < 8; i++) {
        double delta = possible_periods.top().first;
        int d = possible_periods.top().second;
        possible_periods.pop();
        cout << d << ": " << delta << endl;
        vector<string> columns = vector<string>(d);
        for (int l = 0; l < d; l++) {
            columns[l] = "";
        }
        for (int l = 0; l < n; l++) {
            columns[l % d] += {ciphertext[l]};
        }
        vector<vector<string>> letter_combinations = vector<vector<string>>(d);
        for (int l = 0; l < d; l++) {
            vector<string> additive_candidates = additive_frequency_based(
                    columns[l]);
            letter_combinations[l] = additive_candidates;
        }

        vector<vector<int>> idx_combs = tuples(2, d);

        for (int j = 0; j < idx_combs.size(); j++) {
            string key_candidate = "";
            for (int l = 0; l < d; l++) {

                key_candidate += letter_combinations[l][idx_combs[j][l]];
            }
            VigenereCipher vigenere_cipher = VigenereCipher(key_candidate);
            string plain_text_candidate = vigenere_cipher.decrypt(ciphertext);
            result.push(
                    make_pair(-abs(index_of_coincidence(plain_text_candidate) -
                                   ENGLISH_INDEX_OF_COINCIDENCE),
                              plain_text_candidate + key_candidate));
        }
    }
// while(!result.empty()) {
//         pair<double, string> result_pair= result.top();
//         cout<<result_pair.second <<" " << result_pair.first << endl;
//         result.pop();
//     }
    for (int q = 0; q < 100; q++) {
        pair<double, string> result_pair = result.top();
        cout << result_pair.second << " " << result_pair.first << endl;
        result.pop();
    }
//     // for (int d = 1; d <= n; d++) {


}

void linear_attack(SpNetwork sp_network) {
    LinearAttackWorker attack_worker = LinearAttackWorker(sp_network);
    vector<DynamicBitset> inputs_for_trace_generation
            = attack_worker.generate_single_sbox_inputs_for_traces();
    multiset<LinearTrace> linear_traces = attack_worker
            .generate_linear_traces_from_inputs(inputs_for_trace_generation);
    vector<DynamicBitset> round_keys;
    size_t sbox_size = sp_network.sbox_size();

    for (size_t round = 0; round < sp_network.rounds(); round++) {
        auto it = linear_traces.rbegin();
        cout << "Starting round " << sp_network.rounds() - round << endl;
        DynamicBitset round_key = DynamicBitset(sp_network.block_size());

        DynamicBitset numberSet = DynamicBitset(
                pow(2, sp_network.sbox_size()) - 1,
                sp_network.sbox_size()
        );
        numberSet.print();
        while (it != linear_traces.rend() && !numberSet.is_zero()) {
            cout << "number set: ";
            numberSet.print();
            LinearTrace best_trace = *it;
            it++;
            bool contains_more = false;
            size_t n_act = 0;
            for (size_t i = 0; i < sp_network.n_parallel_sboxes(); i++) {

                DynamicBitset slice = best_trace
                        .get_active_output(2 - round)
                        .slice(i * sbox_size, (i + 1) * sbox_size);
                if (!slice.is_zero()) {
                    n_act += 1;
                }
                if (numberSet.test(i) && !slice.is_zero()) {
                    contains_more = true;
                }
            }
            if (n_act > 2) {
                continue;
            }
            if (!contains_more) {
                continue;
            }
            best_trace.print();
            size_t count = std::pow(best_trace.get_bias(), -3);
            count = 65536;
            cout << "Generating " << count << " random pairs..." << endl;
            vector<pair<DynamicBitset, DynamicBitset>> pairs = attack_worker
                    .generate_random_plain_cipher_pairs(count);
            cout << "Done." << endl;

            pairs = attack_worker.partial_decrypt_plain_cipher_pairs
                    (round_keys, pairs);

            vector<vector<DynamicBitset>> prefixes_list;
            DynamicBitset active_inputs = best_trace.get_input();
            DynamicBitset active_outputs = best_trace.get_active_output(
                    2 - round);
            cout << "input: ";
            active_inputs.print();
            cout << "outputs: ";
            active_outputs.print();
            for (size_t i = 0; i < sp_network.n_parallel_sboxes(); i++) {
                vector<DynamicBitset> prefixes;
                DynamicBitset slice = active_outputs.slice(i * sbox_size,
                                                           (i + 1) * sbox_size);
                if (slice.is_zero()) {
                    prefixes.push_back(
                            DynamicBitset(0, sp_network.sbox_size()));
                } else {
                    for (uint64_t j = 0;
                         j < pow(2, sp_network.sbox_size()); j++) {
                        prefixes.push_back(
                                DynamicBitset(j, sp_network.sbox_size()));
                    }
                }
                prefixes_list.push_back(prefixes);
            }

            vector<DynamicBitset> possible_keys = generateCombinations(
                    prefixes_list);

            cout << "evaluating " << possible_keys.size()
                 << " key candidates...";
            bool is_last_round = (round == 0);
            cout << "is last round:" << is_last_round << endl;
            DynamicBitset max_key = attack_worker
                    .estimate_best_round_key_candidate(pairs, possible_keys,
                                                       is_last_round,
                                                       active_inputs,
                                                       active_outputs);
            max_key.print();
            for (size_t i = 0; i < sp_network.n_parallel_sboxes(); i++) {
                size_t begin = i * sp_network.sbox_size();
                size_t end = begin + sp_network.sbox_size();

                if (numberSet.test(i) && !active_outputs.slice(begin, end).
                        is_zero()) {
                    numberSet.clear(i);
                    DynamicBitset key_slice = max_key.slice(begin, end);
                    for (size_t j = begin; j < end; j++) {
                        if (key_slice.test(j - begin)) {
                            round_key.set(j);
                        }
                    }
                }
            }
            cout << "current round key: ";
            round_key.print();
            cout << "map stil includes" << numberSet.size() << endl;
        }
        round_keys.push_back(round_key);
    }
}