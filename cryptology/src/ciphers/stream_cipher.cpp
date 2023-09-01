#include <iostream>

#include <cryptology/ciphers/stream_cipher.hpp>
#include <cryptology/algebra/algorithms.hpp>
#include <cryptology/utils.hpp>

using namespace std;

StreamCipher::StreamCipher(string keyword) : keyword(keyword) {
    if(!word_from_latin_alphabet(keyword)) {
        throw runtime_error("The keyword has to come from the latin alphabet");
    }
};

string StreamCipher::encrypt(string plain_text) {
    int l = this->keyword.length();
    int shift;
    string output = plain_text;
    for (int i = 0; i < plain_text.length(); ++i) {
        shift = get_next_shift(i, plain_text, output);
        output[i] = pos_to_letter(mod(letter_to_pos(output[i]) + shift, 26));
    }
    return output;
}

string StreamCipher::decrypt(string cipher_text) {
    int l = this->keyword.length();
    int shift;
    string output = cipher_text;
    for (int i = 0; i < cipher_text.length(); ++i) {
        shift = get_next_shift(i, output, cipher_text);
        output[i] = pos_to_letter(mod(letter_to_pos(output[i]) - shift, 26));
    }
    return output;
}

int VigenereCipher::get_next_shift(size_t round, string &plain_text, string &cipher_text) {
    int l = this->keyword.length();
    return letter_to_pos(this->keyword[mod(round, l)]);
}

string BeaufortCipher::encrypt(string plain_text) {
    int l = this->keyword.length();
    int shift;
    string output = plain_text;
    for (int i = 0; i < plain_text.length(); ++i) {
        shift = get_next_shift(i, plain_text, output);
        output[i] = pos_to_letter(mod(letter_to_pos(shift - output[i]), 26));
    }
    return output;
}

string BeaufortCipher::decrypt(string plain_text) {
    return this->encrypt(plain_text);
}

int BeaufortCipher::get_next_shift(size_t round, string &plain_text, string &cipher_text) {
    int l = this->keyword.length();
    return letter_to_pos(this->keyword[mod(round, l)]);
}

int AutoKeyPlainTextCipher::get_next_shift(size_t round, string &plain_text, string &cipher_text) {
    if (round < this->keyword.size()) {
        return letter_to_pos(this->keyword[round]);
    }
    return letter_to_pos(plain_text[round - this->keyword.size()]);
}

int AutoKeyCipherTextCipher::get_next_shift(size_t round, string &plain_text, string &cipher_text) {
    if (round < this->keyword.size()) {
        return letter_to_pos(this->keyword[round]);
    }
    return letter_to_pos(cipher_text[round - this->keyword.size()]);
}