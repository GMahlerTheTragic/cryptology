#ifndef CRYPTOLOGY_UTILS_HPP_
#define CRYPTOLOGY_UTILS_HPP_

#include <iostream>
#include <cryptology/algebra/algorithms.hpp>
#include <cryptology/algebra/vector.hpp>

using namespace std;

bool is_letter(char);

int letter_to_pos(char input);

char pos_to_letter(int pos);

bool word_from_latin_alphabet(string input);

vector<int> word_to_vec(string input);



#endif
