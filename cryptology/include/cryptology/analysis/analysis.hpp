//
// Created by asf12fd3 on 01.09.23.
//

#ifndef CRYPTOLOGY_ANALYSIS_HPP
#define CRYPTOLOGY_ANALYSIS_HPP

#include <string>

void additive_brute_force(std::string ciphertext);
std::vector<std::string> additive_frequency_based(std::string ciphertext);
void hill_frequency_attack(std::string ciphertext, int n);
void vigenere_kasiki_attack(std::string ciphertext);

#endif //CRYPTOLOGY_ANALYSIS_HPP
