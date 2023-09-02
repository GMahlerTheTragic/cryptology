#include <iostream>

#include <cryptology/ciphers/hill_cipher.hpp>
#include <cryptology/algebra/algorithms.hpp>
#include <cryptology/algebra/matrix.hpp>
#include <cryptology/algebra/vector.hpp>
#include "cryptology/utils/utils.hpp"

template
class Matrix<26>;

template
class Vector<26>;

using namespace std;

HillCipher::HillCipher(Matrix<26> key_matrix) : key_matrix(key_matrix),
                                                key_matrix_inv(Matrix<26>(
                                                        key_matrix.rows(),
                                                        key_matrix.cols())) {
    if (key_matrix.cols() != key_matrix.rows()) {
        throw runtime_error("The key matrix has to be quadratic");
    }
    this->block_size = key_matrix.rows();
    this->key_matrix_inv = inverse(key_matrix);
}

string HillCipher::encrypt_block(string plain_text) {
    Vector<26> block = Vector<26>(this->block_size);
    string output = plain_text;
    for (int i = 0; i < plain_text.length(); ++i) {
        block(i) = letter_to_pos(plain_text[i]);
    }
    block = block * this->key_matrix;
    for (int i = 0; i < plain_text.length(); ++i) {
        output[i] = pos_to_letter(block(i));
    }
    return output;
}

string HillCipher::decrypt_block(string cipher_text) {
    Vector<26> block = Vector<26>(this->block_size);
    string output = cipher_text;
    for (int i = 0; i < cipher_text.length(); ++i) {
        block(i) = letter_to_pos(cipher_text[i]);
    }
    block = block * this->key_matrix_inv;
    for (int i = 0; i < cipher_text.length(); ++i) {
        output[i] = pos_to_letter(block(i));
    }
    return output;
}

string HillCipher::encrypt(string plain_text) {
    string output = "";
    if (plain_text.size() % this->block_size != 0)
        throw runtime_error(
                "Currently the plain text length has to be a multiple of the block size");
    for (int i = 0; i < plain_text.length(); i += this->block_size) {
        cout << plain_text.substr(i, i + block_size) << endl;
        output += this->encrypt_block(plain_text.substr(i, block_size));
    }
    return output;
}

string HillCipher::decrypt(string cipher_text) {
    string output = "";
    if (cipher_text.size() % this->block_size != 0)
        throw runtime_error(
                "Currently the plain text length has to be a multiple of the block size");
    for (int i = 0; i < cipher_text.length(); i += this->block_size) {
        output += this->decrypt_block(cipher_text.substr(i, block_size));
    }
    return output;
}
