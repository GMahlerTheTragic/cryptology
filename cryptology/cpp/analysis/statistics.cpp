#include <iostream>
#include <cryptology/analysis/frequencies.hpp>
#include <cryptology/analysis/statistics.hpp>

#include <queue>

#include <map>

using namespace std;

string letters[26] = {
    "A", "B", "C", "D", "E", "F", "G",
    "H", "I", "J", "K", "L", "M", "N",
    "O", "P", "Q", "R", "S", "T", "U",
    "V", "W", "X", "Y", "Z"
};

map<string, double> compute_letter_frequencies(string text) {
    map<string, double> result;

    for (int i = 0; i < 26; ++i) {
        result[letters[i]] = 0;
    }

    for (int i = 0; i < text.length(); ++i) {
        result[{text[i]}] += 1.;
    }

    for (int i = 0; i < 26; ++i) {
        result[letters[i]] = result[letters[i]] / text.length();
    }

    return result;
}

priority_queue<pair<int, string>> compute_ngramm_frequencies(string text, int n) {
    map<string, int> result;
    // cout << text << endl;
    for (int i = 0; i < text.length() - n; i++) {
        string ngram = text.substr(i, n);
        // cout << i <<  ngram << endl;
        if (result.contains(ngram)) {
            result[ngram] += 1;
        }
        else {
            result[ngram] = 1;
        }
    }
    priority_queue<pair<int, string>> ngram_prio_queue;
    for (auto [key, val]: result) {
        // cout << key << ", " << val << endl;
        ngram_prio_queue.push(make_pair(val, key));
    }

    return ngram_prio_queue;
}

double index_of_coincidence(string text) {
    map<string, double> freqs = compute_letter_frequencies(text);
    double result = 0.;
    for (int i = 0; i < 26; ++i) {
        double f = freqs[letters[i]];
        double p = ENGLISH_FREQUENCIES.at(letters[i]);
        result += p * f;
    }
    return result;
}

double expected_ioc(int d, int n) {
    double divisor = (double) (d * (n -1));
    double m_inv = 1. / 26;
    double expected_ioc = ((n - d) / divisor) * ENGLISH_INDEX_OF_COINCIDENCE + (n * (d -1) * m_inv) / divisor;
    return expected_ioc;
}