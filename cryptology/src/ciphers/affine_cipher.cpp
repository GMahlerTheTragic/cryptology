#include "cryptology/ciphers/affine_cipher.hpp"

#include <iostream>
#include <stdint.h>

#include "cryptology/algebra/algorithms.hpp"
#include "cryptology/utils/utils.hpp"

using std::runtime_error;

constexpr uint8_t k8ones = 0xFF;
constexpr uint8_t kwhite_space = 0x20;
constexpr uint8_t knumber_of_letter = 26;

AffineCipher::AffineCipher(int shift, int slope)
    : shift(shift), slope(slope), slope_inv(Inverse(slope, knumber_of_letter)) {}

char AffineCipher::encrypt(char input) const {
    if ((input & k8ones) == kwhite_space) {
        return input;
    }
    if (!is_letter(input)) {
        throw runtime_error("Character to be encrypted is not part of the latin alphabet");
    }
    int pos = letter_to_pos(input);
    char res = pos_to_letter(Mod(((slope * pos) + shift), knumber_of_letter));
    return res;
}

char AffineCipher::decrypt(char input) const {
    if ((input & k8ones) == kwhite_space) {
        return input;
    }
    if (!is_letter(input)) {
        throw runtime_error("Character to be decrypted is not part of the latin alphabet");
    }
    int pos = letter_to_pos(input);
    char res = pos_to_letter(Mod((slope_inv * (pos - shift)), knumber_of_letter));
    return res;
}

string AffineCipher::encrypt(string plain_text) const {
    string output = plain_text;
    for (int i = 0; i < plain_text.length(); ++i) {
        output[i] = this->encrypt(output[i]);
    }
    return output;
}

string AffineCipher::decrypt(string cipher_text) const {
    string output = cipher_text;
    for (int i = 0; i < cipher_text.length(); ++i) {
        output[i] = this->decrypt(output[i]);
    }
    return output;
}