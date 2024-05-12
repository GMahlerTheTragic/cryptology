#include <iostream>
#include <string>

#include "cryptology.hpp"

using namespace std;
using namespace cryptology;

template class Matrix<26>;

template class Vector<26>;

int main() {
    cout << "This is the Vigenere cipher example..." << endl;
    cout << endl;
    cout << "Defining Vigenere cipher using the key word 'WIE'..." << endl;
    VigenereCipher vigenere_cipher = VigenereCipher("WIE");

    cout << "Encrypting the word VIGENERE...";
    string cipher_text = vigenere_cipher.encrypt("VIGENERE");
    cout << "cipher text " << cipher_text << endl;
    cout << "plain text " << vigenere_cipher.decrypt(cipher_text) << endl;
    cout << endl;

    cout << "Defining Vigenere cipher using the key word 'HOPE'..." << endl;
    string plain_text = "AGOODGLASSINTHEBISHOPSHOSTELINTHEDEVILSSEATFORTYONEDEGREESANDTHIRTEENMINUTESNORTHEASTANDBYNORTHMAINBRANCHSEVENTHLIMBEASTSIDESHOOTFROMTHELEFTEYEOFTHEDEATHSHEADABEELINEFROMTHETREETHROUGHTHESHOTFIFTYFEETOUT";
    cout << "Encrypting the phrase: " << plain_text << endl;
    VigenereCipher vigenere_cipher_for_attack = VigenereCipher("HOPE");
    cipher_text = vigenere_cipher_for_attack.encrypt(plain_text);
    cout << "Cipher text is: " << cipher_text << endl;
    cout << endl;
    VigenereAttack(cipher_text);
}
