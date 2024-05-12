#ifndef CRYPTOLOGY_ANALYSIS_STATISTICS_HPP_
#define CRYPTOLOGY_ANALYSIS_STATISTICS_HPP_

#include <map>
#include <queue>
#include <string>

using namespace std;

map<string, int> compute_letter_counts(const string& text);

double index_of_coincidence(const string& text);

double index_of_similarity(const string& text);

priority_queue<pair<int, string>> compute_ngramm_frequencies(const string& text, int n);

double expected_ioc(size_t key_word_period, size_t n);

#endif