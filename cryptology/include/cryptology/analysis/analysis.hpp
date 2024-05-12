#ifndef CRYPTOLOGY_ANALYSIS_HPP
#define CRYPTOLOGY_ANALYSIS_HPP

#include <cryptology/ciphers/sp_network/sp_network.hpp>
#include <string>

void AdditiveBruteForce(const std::string &ciphertext);

std::vector<std::string> AdditiveFrequencyBased(const std::string &ciphertext);

void HillFrequencyAttack(const std::string& ciphertext, int n);

void VigenereAttack(std::string ciphertext);

void LinearAttack(const SpNetwork& sp_network);

#endif
