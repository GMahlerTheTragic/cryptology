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

map<string, int> compute_letter_counts(string text) {
  map<string, int> result;

  for (const auto &letter : letters) {
    result[letter] = 0;
  }

  for (char &i : text) {
    result[{i}] += 1;
  }

  return result;
}

priority_queue<pair<int, string>>
compute_ngramm_frequencies(string text, int n) {
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
  for (auto [key, val] : result) {
    // cout << key << ", " << val << endl;
    ngram_prio_queue.push(make_pair(val, key));
  }

  return ngram_prio_queue;
}

double index_of_coincidence(string text) {
  size_t n = text.length();
  map<string, int> letter_counts = compute_letter_counts(text);
  double result = 0.;
  for (const auto &letter : letters) {
    int count = letter_counts.at(letter);
    result += count * (count - 1);
  }
  return result / (double) (n * (n - 1));
}

double index_of_similarity(string text) {
  size_t n = text.length();
  map<string, int> letter_counts = compute_letter_counts(text);
  double result = 0.;
  for (const auto &letter : letters) {
    int count = letter_counts.at(letter);
    double letter_probability = (double) count / n;
    result += letter_probability * ENGLISH_FREQUENCIES.at(letter);
  }
  return result;
}

double expected_ioc(int d, int n) {
  double divisor = (double) (d * (n - 1));
  double m_inv = 1. / 26;
  double expected_ioc = ((n - d) / divisor) * ENGLISH_INDEX_OF_COINCIDENCE +
      (n * (d - 1) * m_inv) / divisor;
  return expected_ioc;
}