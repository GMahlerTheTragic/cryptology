#include <iostream>
#include <string>

#include "cryptology.hpp"

using namespace std;
using namespace cryptology;

template class Matrix<26>;

template class Vector<26>;

int main() {
    cout << "This is the Affine and additive cipher example..." << endl;
    cout << endl;
    cout << "Defining affine cipher with shift 8 and slope 5..." << endl;
    const auto affine_cipher = AffineCipher(8, 5);

    cout << "Encrypting plain text Hallo Welt" << endl;
    cout << endl;
    string cipher_text = affine_cipher.encrypt("Hallo Welt");

    cout << "Encrypted cipher text: " << cipher_text << endl;
    cout << "Decrypted plain text: " << affine_cipher.decrypt(cipher_text) << endl;
    cout << endl;

    cout << "Defining additive cipher with shift 8..." << endl;
    const auto additive_cipher = AffineCipher(8, 1);

    cipher_text = additive_cipher.encrypt("xygrobo");
    AdditiveBruteForce(cipher_text);
}
