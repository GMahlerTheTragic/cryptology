#include <iostream>
#include <cstdint>
#include "cryptology/ciphers/stream_cipher.hpp"
#include "cryptology/algebra/algorithms.hpp"
#include "cryptology/utils/utils.hpp"

using std::runtime_error;

constexpr uint8_t knumber_of_letters = 26;

StreamCipher::StreamCipher(const string &keyword) : keyword(keyword) {
    if (!word_from_latin_alphabet(keyword)) {
        throw runtime_error("The keyword has to come from the latin alphabet");
    }
}

string StreamCipher::encrypt(string plain_text) {
    string output = plain_text;
    for (int i = 0; i < plain_text.length(); ++i) {
        uint8_t shift = get_next_shift(i, plain_text, output);
        output[i] = pos_to_letter(Mod(letter_to_pos(output[i]) + shift, knumber_of_letters));
    }
    return output;
}

string StreamCipher::decrypt(string cipher_text) {
    string output = cipher_text;
    for (int i = 0; i < cipher_text.length(); ++i) {
        uint8_t shift = get_next_shift(i, output, cipher_text);
        output[i] = pos_to_letter(Mod(letter_to_pos(output[i]) - shift, knumber_of_letters));
    }
    return output;
}

uint8_t VigenereCipher::get_next_shift(size_t round, string &plain_text, string &cipher_text) {
    return letter_to_pos(this->keyword[Mod(round, this->keyword.length())]);
}

string BeaufortCipher::encrypt(string plain_text) {
    string output = plain_text;
    for (int i = 0; i < plain_text.length(); ++i) {
        uint8_t shift = get_next_shift(i, plain_text, output);
        output[i] = pos_to_letter(Mod(shift - letter_to_pos(output[i]), knumber_of_letters));
    }
    return output;
}

string BeaufortCipher::decrypt(string cipher_text) { return this->encrypt(cipher_text); }

uint8_t BeaufortCipher::get_next_shift(size_t round, string &plain_text, string &cipher_text) {
    return letter_to_pos(this->keyword[Mod(round, this->keyword.length())]);
}

uint8_t AutoKeyPlainTextCipher::get_next_shift(size_t round, string &plain_text,
                                               string &cipher_text) {
    if (round < this->keyword.size()) {
        return letter_to_pos(this->keyword[round]);
    }
    return letter_to_pos(plain_text[round - this->keyword.size()]);
}

uint8_t AutoKeyCipherTextCipher::get_next_shift(size_t round, string &plain_text,
                                                string &cipher_text) {
    if (round < this->keyword.size()) {
        return letter_to_pos(this->keyword[round]);
    }
    return letter_to_pos(cipher_text[round - this->keyword.size()]);
}
