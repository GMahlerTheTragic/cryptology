#ifndef CRYPTOLOGY_CIPHERS_AFFINE_CIPHER_HPP_
#define CRYPTOLOGY_CIPHERS_AFFINE_CIPHER_HPP_

#include <iostream>

using namespace std;

class AffineCipher {
    private:
        const int a;
        const int b;
        const int b_inv;
        char encrypt(char input);
        char decrypt(char input);
    public:
        AffineCipher(int a, int b);
        string encrypt(string plain_text);
        string decrypt(string cipher_text);
};
#endif