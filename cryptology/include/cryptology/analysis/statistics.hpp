#ifndef CRYPTOLOGY_ANALYSIS_STATISTICS_HPP_
#define CRYPTOLOGY_ANALYSIS_STATISTICS_HPP_

#include <map>
#include <queue>
#include <string>

using namespace std;

map<string, int> compute_letter_counts(string text);

double index_of_coincidence(string test);

double index_of_similarity(string text);

priority_queue<pair<int, string>>
compute_ngramm_frequencies(string text, int n);

double expected_ioc(int d, int n);

#endif