#ifndef CRYPTOLOGY_UTILS_HPP_
#define CRYPTOLOGY_UTILS_HPP_

#include <cryptology/utils/dynamic_bitset.hpp>
#include <iostream>

#include "cryptology/algebra/algorithms.hpp"

using namespace std;

bool is_letter(char);

uint8_t letter_to_pos(char input);

char pos_to_letter(uint8_t pos);

bool word_from_latin_alphabet(const string &input);

vector<int> word_to_vec(const string &input);

vector<vector<int>> tuples(int range, int tuple_size);

vector<DynamicBitset> generateCombinations(const vector<vector<DynamicBitset>> &lists);

#endif
