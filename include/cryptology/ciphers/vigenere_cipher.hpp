#ifndef CRYPTOLOGY_CIPHERS_VIGENERE_CIPHER_HPP_
#define CRYPTOLOGY_CIPHERS_VIGENERE_CIPHER_HPP_

#include <iostream>

using namespace std;

class VigenereCipher {
    private:
        const string keyword;
    public:
        VigenereCipher(string keyword);
        string encrypt(string plain_text);
        string decrypt(string cipher_text);
};
#endif