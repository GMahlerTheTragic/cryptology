#include <iostream>

#include <cryptology/ciphers/vigenere_cipher.hpp>
#include <cryptology/algebra/algorithms.hpp>
#include <cryptology/utils.hpp>

using namespace std;

VigenereCipher::VigenereCipher(string keyword) : keyword(keyword) {
    if(!word_from_latin_alphabet(keyword)) {
        throw runtime_error("The keyword has to come from the latin alphabet");
    }
};

string VigenereCipher::encrypt(string plain_text) {
    int l = this->keyword.length();
    int shift;
    string output = plain_text;
    for (int i = 0; i < plain_text.length(); ++i) {
        shift = letter_to_pos(this->keyword[mod(i, l)]);
        output[i] = pos_to_letter(mod(letter_to_pos(output[i]) + shift, 26));
    }
    return output;
}

string VigenereCipher::decrypt(string cipher_text) {
    int l = this->keyword.length();
    int shift;
    string output = cipher_text;
    for (int i = 0; i < cipher_text.length(); ++i) {
        shift = letter_to_pos(this->keyword[mod(i, l)]);
        output[i] = pos_to_letter(mod(letter_to_pos(output[i]) - shift, 26));
    }
    return output;
}