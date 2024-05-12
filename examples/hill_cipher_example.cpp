#include <iostream>
#include <string>

#include "cryptology.hpp"

using namespace std;
using namespace cryptology;

template class Matrix<26>;

template class Vector<26>;

int main() {
    cout << "This is the Hill cipher example..." << endl;
    cout << endl;
    cout << "Defining Hill cipher using the following key matrix modulu 26..." << endl;
    Matrix<26> h = Matrix<26>({{11, 13, 8, 21}, {24, 17, 3, 25}, {18, 12, 23, 17}, {6, 15, 2, 15}});
    HillCipher hill_cipher = HillCipher(h);
    h.print();
    cout << endl;
    cout << "Encrypting the word HELLOYOU..." << endl;
    string cipher_text = hill_cipher.encrypt("HELLOYOU");
    cout << endl;
    cout << "encrypted cipher text " << cipher_text << endl;
    cout << "decrypted plain text " << hill_cipher.decrypt(cipher_text) << endl;
    cout << endl;
}
