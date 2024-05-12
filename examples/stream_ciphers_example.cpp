#include <iostream>
#include <string>

#include "cryptology.hpp"

using namespace std;
using namespace cryptology;

template class Matrix<26>;

template class Vector<26>;

int main() {
    cout << "This is the Stream cipher example..." << endl;
    cout << endl;

    cout << "Defining BeaufortCipher using the key word 'WIE'..." << endl;
    BeaufortCipher beaufort_cipher = BeaufortCipher("WIE");
    cout << "Encrypting the word 'BEAUFORT'..." << endl;
    string cipher_text = beaufort_cipher.encrypt("BEAUFORT");
    cout << "encrypted cipher text " << cipher_text << endl;
    cout << "decrypted plain text " << beaufort_cipher.decrypt(cipher_text) << endl;
    cout << endl;

    cout << "Defining AutoKeyPlainTextCipher using the key word 'WIE'..." << endl;
    AutoKeyPlainTextCipher autokeypt_cipher = AutoKeyPlainTextCipher("WIE");
    cout << "Encrypting the word 'VIGENERE'..." << endl;
    cipher_text = autokeypt_cipher.encrypt("VIGENERE");
    cout << "encrypted cipher text " << cipher_text << endl;
    cout << "decrypted plain text " << autokeypt_cipher.decrypt(cipher_text) << endl;
    cout << endl;

    cout << "Defining AutoKeyCipherTextCipher using the key word 'WIE'..." << endl;
    AutoKeyCipherTextCipher autokeyct_cipher = AutoKeyCipherTextCipher("WIE");
    cout << "Encrypting the word 'VIGENERE'..." << endl;
    cipher_text = autokeyct_cipher.encrypt("VIGENERE");
    cout << "encrypted cipher text " << cipher_text << endl;
    cout << "decrypted plain text " << autokeyct_cipher.decrypt(cipher_text) << endl;
    cout << endl;
}
