#include <iostream>

#include <cryptology/ciphers/affine_cipher.hpp>
#include <cryptology/algebra/algorithms.hpp>

using namespace std;

AffineCipher::AffineCipher(int a, int b) : a(a), b(b), b_inv(inverse(b, 26)) {};

char AffineCipher::encrypt(char input) {
    if ((input & 0xFF) == 0x20) {
        return input;
    }
    if (input < 0x41 || (input >= 0x5B && input < 0x61) || input > 0x7A) {
        throw runtime_error("Character to be encrypted is not part of the latin alphabet");
    }
    int prefix = input & 0xE0; 
    int pos = (input & 0x1F) - 1;
    char res = (prefix |  mod(((b * pos) + a), 26) + 1);
    return res;
}

char AffineCipher::decrypt(char input) {
    if ((input & 0xFF) == 0x20) {
        return input;
    }
    if (input < 0x41 || (input >= 0x5B && input < 0x61) || input > 0x7A) {
        throw runtime_error("Character to be decrypted is not part of the latin alphabet");
    }
    int prefix = input & 0xE0; 
    int pos = (input & 0x1F) - 1;
    char res = (prefix |  mod((b_inv * (pos - a)),26) + 1);
    return res;
}

string AffineCipher::encrypt(string plain_text) {
    string output = plain_text;
    for (int i = 0; i < plain_text.length(); ++i) {
        output[i] = this->encrypt(output[i]);
    }
    return output;
}

string AffineCipher::decrypt(string cipher_text) {
    string output = cipher_text;
    for (int i = 0; i < cipher_text.length(); ++i) {
        output[i] = this->decrypt(output[i]);
    }
    return output;
}