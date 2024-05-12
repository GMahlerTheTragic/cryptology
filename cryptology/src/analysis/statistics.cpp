#include <iostream>
#include <map>
#include <queue>
#include <cstdint>
#include "cryptology/analysis/statistics.hpp"
#include "cryptology/analysis/frequencies.hpp"

using std::cout;
using std::string;

constexpr auto kletters = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
                       "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

constexpr uint8_t knumber_of_letters = 26;

map<string, int> compute_letter_counts(const string& text) {
    map<string, int> result;

    for (const auto &letter : kletters) {
        result[letter] = 0;
    }

    for (const char &letter : text) {
        result[{letter}] += 1;
    }

    return result;
}

priority_queue<pair<int, string>> compute_ngramm_frequencies(const string &text, int n) {
    map<string, int> result;
    for (int i = 0; i <= text.length() - n; i++) {
        string ngram = text.substr(i, n);
        // cout << i <<  ngram << endl;
        if (result.contains(ngram)) {
            result[ngram] += 1;
        } else {
            result[ngram] = 1;
        }
    }
    priority_queue<pair<int, string>> ngram_prio_queue;
    for (const auto& [key, val] : result) {
        // cout << key << ", " << val << endl;
        ngram_prio_queue.emplace(val, key);
    }

    return ngram_prio_queue;
}

double index_of_coincidence(const string &text) {
    size_t text_lenght = text.length();
    map<string, int> letter_counts = compute_letter_counts(text);
    double result = 0.;
    for (const auto &letter : kletters) {
        int count = letter_counts.at(letter);
        result += count * (count - 1);
    }
    return result / static_cast<double>(text_lenght * (text_lenght - 1));
}

double index_of_similarity(const string &text) {
    auto text_lenght = static_cast<double>(text.length());
    map<string, int> letter_counts = compute_letter_counts(text);
    double result = 0.;
    for (const auto &letter : kletters) {
        int count = letter_counts.at(letter);
        double letter_probability = static_cast<double>(count) / text_lenght;
        result += letter_probability * ENGLISH_FREQUENCIES.at(letter);
    }
    return result;
}

double expected_ioc(size_t key_word_period, size_t n) {
    auto text_lenght = static_cast<double>(n);
    auto key_word_period_double = static_cast<double>(key_word_period);
    auto divisor = static_cast<double>(key_word_period * (n - 1));
    double m_inv = 1. / knumber_of_letters;
    double expected_ioc =
        ((text_lenght - key_word_period_double) / divisor) * ENGLISH_INDEX_OF_COINCIDENCE +
        (text_lenght * (key_word_period_double - 1) * m_inv) / divisor;
    return expected_ioc;
}
