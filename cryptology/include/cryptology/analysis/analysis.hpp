#ifndef CRYPTOLOGY_ANALYSIS_HPP
#define CRYPTOLOGY_ANALYSIS_HPP

#include <cryptology/ciphers/sp_network/sp_network.hpp>
#include <string>

void AdditiveBruteForce(std::string ciphertext);

std::vector<std::string> AdditiveFrequencyBased(std::string ciphertext);

void HillFrequencyAttack(std::string ciphertext, int n);

void VigenereAttack(std::string ciphertext);

void LinearAttack(SpNetwork sp_network);

#endif  // CRYPTOLOGY_ANALYSIS_HPP
