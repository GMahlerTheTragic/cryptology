#ifndef CRYPTOLOGY_CIPHERS_HILL_CIPHER_HPP_
#define CRYPTOLOGY_CIPHERS_HILL_CIPHER_HPP_

#include <iostream>
#include <string>
#include <cryptology/algebra/matrix.hpp>

using namespace std;

class HillCipher {
 private:
  const Matrix<26> key_matrix;
  Matrix<26> key_matrix_inv;
  size_t block_size;
  string encrypt_block(const string &plain_text) const;
  string decrypt_block(const string &cipher_text) const;

 public:
  explicit HillCipher(const Matrix<26> &key_matrix);
  string encrypt(const string &plain_text) const;
  string decrypt(const string &cipher_text) const;
};
#endif