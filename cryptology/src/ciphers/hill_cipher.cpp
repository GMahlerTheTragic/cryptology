#include "cryptology/ciphers/hill_cipher.hpp"

#include <iostream>

#include "cryptology/algebra/algorithms.hpp"
#include "cryptology/algebra/matrix.hpp"
#include "cryptology/algebra/vector.hpp"
#include "cryptology/utils/utils.hpp"

constexpr uint8_t knumber_of_letters = 26;
;
template class Matrix<knumber_of_letters>;

template class Vector<knumber_of_letters>;

using std::runtime_error;

HillCipher::HillCipher(Matrix<knumber_of_letters> key_matrix)
    : key_matrix(key_matrix),
      key_matrix_inv(Matrix<knumber_of_letters>(key_matrix.rows(), key_matrix.cols())) {
    if (key_matrix.cols() != key_matrix.rows()) {
        throw runtime_error("The key matrix has to be quadratic");
    }
    this->block_size = key_matrix.rows();
    this->key_matrix_inv = Inverse(key_matrix);
}

string HillCipher::encrypt_block(string plain_text) {
    Vector<knumber_of_letters> block = Vector<knumber_of_letters>(this->block_size);
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
    Vector<knumber_of_letters> block = Vector<knumber_of_letters>(this->block_size);
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
    string output;
    if (plain_text.size() % this->block_size != 0) {
        throw runtime_error(
            "Currently the plain text length has to be a multiple of the block size");
    }
    for (size_t i = 0; i < plain_text.length(); i += this->block_size) {
        cout << plain_text.substr(i, i + block_size) << endl;
        output += this->encrypt_block(plain_text.substr(i, block_size));
    }
    return output;
}

string HillCipher::decrypt(string cipher_text) {
    string output;
    if (cipher_text.size() % this->block_size != 0) {
        throw runtime_error(
            "Currently the plain text length has to be a multiple of the block size");
    }
    for (size_t i = 0; i < cipher_text.length(); i += this->block_size) {
        output += this->decrypt_block(cipher_text.substr(i, block_size));
    }
    return output;
}
