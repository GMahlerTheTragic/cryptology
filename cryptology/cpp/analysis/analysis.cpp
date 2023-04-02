#include <iostream>
#include <map>
#include <queue>

#include <iostream>
#include <cryptology/algebra/algorithms.hpp>
#include <cryptology/algebra/matrix.hpp>
#include <cryptology/algebra/vector.hpp>
#include <cryptology/ciphers/affine_cipher.hpp>
#include <cryptology/ciphers/hill_cipher.hpp>
#include <cryptology/ciphers/stream_cipher.hpp>
#include <cryptology/analysis/frequencies.hpp>
#include <cryptology/analysis/statistics.hpp>
#include <cryptology/algebra/matrix.hpp>
#include <cryptology/algebra/vector.hpp>
#include <cryptology/utils.hpp>
#include <cryptology/algebra/algorithms.hpp>

using namespace std;

void additive_brute_force(string ciphertext) {
    cout << "Starting brute force attack against additive cipher" << endl;
    map<string, double> result = compute_letter_frequencies(ciphertext);
    for (int i = 0; i < 26; ++i) {
        AffineCipher affine_cipher = AffineCipher(i, 1);
        string candidate = affine_cipher.decrypt(ciphertext);
        double ioc = index_of_coincidence(candidate);
        cout << "possible plain text: " << candidate << ioc << endl;
    }
    
}

vector<string> additive_frequency_based(string ciphertext) {
    priority_queue<pair<double, string>> result_pq = priority_queue<pair<double, string>>();
    for (int i = 0; i < 26; i++) {
        AffineCipher affine_cipher = AffineCipher(i, 1);
        string plain_text_candidate = affine_cipher.decrypt(ciphertext);
        double ioc = index_of_coincidence(plain_text_candidate);
        string key = {pos_to_letter(i)};
        result_pq.push(make_pair(ioc,key));
    }
    vector<string> result = vector<string>(2);
    for (int i = 0; i < 1; i++) {
        result[i] = result_pq.top().second;
        result_pq.pop();
    }
    return result;
}

void hill_frequency_attack(string ciphertext, int n) {
    priority_queue<pair<int, string>> ngram_freqs = compute_ngramm_frequencies(ciphertext, n);
    vector<vector<int>> Y_vals = vector<vector<int>>(n);
    for (int i = 0; i < n; i++) {
        string ngram = ngram_freqs.top().second;
        Y_vals[i] = word_to_vec(ngram);
        ngram_freqs.pop();
    }
    Matrix<26> Y = Matrix<26>(Y_vals);

    priority_queue<pair<double, string>> ngram_freqs_language;

    for (auto [key, val]: ENGLISH_BIGRAM_FREQUENCIES) {
        cout << key << ", " << val << endl;
        ngram_freqs_language.push(make_pair(val, key));
    }

    vector<string> ngram_freqs_language_vec = vector<string>(ENGLISH_BIGRAM_FREQUENCIES.size());
    int i = 0;
    while (!ngram_freqs_language.empty())
    {
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
                result.push(make_pair(index_of_coincidence(plain_text_candidate), plain_text_candidate));
                cout << j << l << "plain text candidate: " << plain_text_candidate << endl;
            }
            catch(const runtime_error& e) {
                continue;
            } 
        }
    }

    while(!result.empty()) {
        pair<double, string> result_pair= result.top();
        cout<<result_pair.second <<" " << result_pair.first << endl;
        result.pop();
    }
}

void vigenere_kasiki_attack(string ciphertext) {
    int n = ciphertext.length();
    priority_queue<pair<int, string>> ngram_freqs = compute_ngramm_frequencies(ciphertext,1);
    double ioc = 0;
    while(!ngram_freqs.empty()) {
        pair<int, string> next = ngram_freqs.top();
        cout << next.second << ": " << next.first <<endl;
        ioc+= next.first * (next.first -1);
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
            vector<string> additive_candidates = additive_frequency_based(columns[l]);
            letter_combinations[l] = additive_candidates;
        }
        
        vector<vector<int>> idx_combs = tuples(2, d);
        
        for (int j = 0; j < idx_combs.size(); j++) {
            string key_candidate = "";
            for (int l = 0; l < d; l ++) {

                key_candidate += letter_combinations[l][idx_combs[j][l]];
            }
            VigenereCipher vigenere_cipher = VigenereCipher(key_candidate);
            string plain_text_candidate = vigenere_cipher.decrypt(ciphertext);
            result.push(make_pair(-abs(index_of_coincidence(plain_text_candidate) - ENGLISH_INDEX_OF_COINCIDENCE), plain_text_candidate+key_candidate));
        }
    }
// while(!result.empty()) {
//         pair<double, string> result_pair= result.top();
//         cout<<result_pair.second <<" " << result_pair.first << endl;
//         result.pop();
//     }
    for (int q = 0; q < 100; q++) {
        pair<double, string> result_pair= result.top();
        cout<<result_pair.second <<" " << result_pair.first << endl;
        result.pop();
    }
//     // for (int d = 1; d <= n; d++) {
    
        
}

