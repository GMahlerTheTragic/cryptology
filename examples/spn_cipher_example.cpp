#include <iostream>
#include <string>

#include "cryptology.hpp"

using namespace std;
using namespace cryptology;

template class Matrix<26>;

template class Vector<26>;

int main() {
    cout << "This is the Substitution Permutation Network (SPN) example..." << endl;
    cout << endl;
    cout << "Defining SPN operating on 16 bit inputs..." << endl;
    cout << "Using 4 4x4 SBoxes and a 16 bit Permutation PBox." << endl;
    cout << "Using 5 hardcoded roundkeys" << endl;
    cout << "RK 1: 0011101010010100" << endl;
    cout << "RK 2: 1010100101001101" << endl;
    cout << "RK 3: 1001010011010110" << endl;
    cout << "RK 4: 1101011000111111" << endl;
    cout << "RK 5: 0100110101100011" << endl;
    SBox sbox = SBox(
            4, 4, {0xE, 0x4, 0xD, 0x1, 0x2, 0xF, 0xB, 0x8, 0x3, 0xA, 0x6, 0xC, 0x5, 0x9, 0x0, 0x7});
    PBox pbox = PBox({0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15});
    vector<DynamicBitset> round_keys = {
        DynamicBitset("0011101010010100"), DynamicBitset("1010100101001101"),
        DynamicBitset("1001010011010110"), DynamicBitset("1101011000111111"),
        DynamicBitset("0100110101100011"),
    };
    SpNetwork spn = SpNetwork(pbox, sbox, 16, 5, round_keys);
    DynamicBitset input = DynamicBitset("0010011010110111");
    cout << "Encrypting the following input: " << endl;
    input.print();
    cout << "Encrypted value is: " << endl;
    spn.encrypt_block(input).print();
    cout << endl;

    LinearAttack(spn);
    cout << "The last round key is: ";
    round_keys[4].print();
}
