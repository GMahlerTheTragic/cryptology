#ifndef CRYPTOLOGY_CIPHERS_AFFINE_CIPHER_HPP_
#define CRYPTOLOGY_CIPHERS_AFFINE_CIPHER_HPP_

#include <iostream>
#include <string>

using namespace std;

class AffineCipher {
   private:
    const uint8_t shift;
    const uint8_t slope;
    const uint8_t slope_inv;

    [[nodiscard]] char encrypt(char input) const;

    [[nodiscard]] char decrypt(char input) const;

   public:
    AffineCipher(int shift, int slope);

    [[nodiscard]] string encrypt(const string &plain_text) const;

    [[nodiscard]] string decrypt(const string &cipher_text) const;
};

#endif