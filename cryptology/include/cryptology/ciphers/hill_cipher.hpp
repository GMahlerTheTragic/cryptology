#ifndef CRYPTOLOGY_CIPHERS_HILL_CIPHER_HPP_
#define CRYPTOLOGY_CIPHERS_HILL_CIPHER_HPP_

#include <iostream>
#include <string>
#include <cryptology/algebra/matrix.hpp>
#include <cryptology/algebra/vector.hpp>

using namespace std;

class HillCipher {
    private:
        const Matrix<26> key_matrix;
        Matrix<26> key_matrix_inv;
        size_t block_size;
        string encrypt_block(string plain_text);
        string decrypt_block(string cipher_text);

    public:
        HillCipher(Matrix<26> key_matrix);
        string encrypt(string plain_text);
        string decrypt(string cipher_text);
};
#endif