#ifndef CRYPTOLOGY_ANALYSIS_STATISTICS_HPP_
#define CRYPTOLOGY_ANALYSIS_STATISTICS_HPP_

#include <map>
#include <queue>
#include <string>

using namespace std;


map<string, double> compute_letter_frequencies(string text);

double index_of_coincidence(string test);

priority_queue<pair<int, string>> compute_ngramm_frequencies(string text, int n);

double expected_ioc(int d, int n);

#endif