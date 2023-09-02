#include <iostream>
#include <cryptology.hpp>
#include <string>

using namespace std;
using namespace cryptology;

template
class Matrix<26>;

template
class Vector<26>;

int main() {
    std::cout << "Hello World" << std::endl;

//  ResidueClass<5> a = ResidueClass<5>(3);
//  ResidueClass<5> b = ResidueClass<5>(4);
//  cout << "a = " << a << endl;
//  cout << "b = " << b << endl;
//  cout << "a + b = " << a + b << endl;
//  cout << "a - b = " << a - b << endl;
//  cout << "a * b = " << a * b << endl;

    Matrix<5> m = Matrix<5>({{1, 2, 2, 3},
                             {1, 2, 2, 3},
                             {1, 2, 2, 3},
                             {1, 2, 2, 3}});

    Matrix<5> n = Matrix<5>({{1, 2, 2, 3},
                             {1, 2, 2, 3},
                             {1, 2, 2, 3},
                             {1, 2, 2, 3}});

    Matrix<26> H = Matrix<26>({{11, 13, 8,  21},
                               {24, 17, 3,  25},
                               {18, 12, 23, 17},
                               {6,  15, 2,  15}});
    n(0, 0) = 8;
    (n * m).print();


    Vector<26> hill = Vector<26>({7, 8, 11, 11});
    Vector<26> hillH = hill * H;

    hillH.print();

    Matrix<26> H_inv = inverse(H);
    H_inv.print();

    long left = 513;
    long right = 29;
    struct gcd_decomposition res = extended_euklid(left, right);
    cout << res.gcd << " " << res.factor_left << " " << res.factor_right
         << endl;

    AffineCipher affine_cipher = AffineCipher(8, 5);
    string cipher_text = affine_cipher.encrypt("Hallo Welt");
    cout << "cipher text " << cipher_text << endl;
    cout << "plain text " << affine_cipher.decrypt(cipher_text) << endl;

    VigenereCipher vigenere_cipher = VigenereCipher("WIE");
    cipher_text = vigenere_cipher.encrypt("VIGENERE");
    cout << "cipher text " << cipher_text << endl;
    cout << "plain text " << vigenere_cipher.decrypt(cipher_text) << endl;

    BeaufortCipher beaufort_cipher = BeaufortCipher("WIE");
    cipher_text = beaufort_cipher.encrypt("BEAUFORT");
    cout << "cipher text " << cipher_text << endl;
    cout << "plain text " << beaufort_cipher.decrypt(cipher_text) << endl;

    AutoKeyPlainTextCipher autokeypt_cipher = AutoKeyPlainTextCipher("WIE");
    cipher_text = autokeypt_cipher.encrypt("VIGENERE");
    cout << "cipher text " << cipher_text << endl;
    cout << "plain text " << autokeypt_cipher.decrypt(cipher_text) << endl;

    AutoKeyCipherTextCipher autokeyct_cipher = AutoKeyCipherTextCipher("WIE");
    cipher_text = autokeyct_cipher.encrypt("VIGENERE");
    cout << "cipher text " << cipher_text << endl;
    cout << "plain text " << autokeyct_cipher.decrypt(cipher_text) << endl;

    HillCipher hill_cipher = HillCipher(H);
    cipher_text = hill_cipher.encrypt("XIAOMEIW");
    cout << "cipher text " << cipher_text << endl;
    cout << "plain text " << hill_cipher.decrypt(cipher_text) << endl;

    AffineCipher additive_cipher = AffineCipher(8, 1);
    cipher_text = additive_cipher.encrypt("xygrobo");
    additive_brute_force(cipher_text);
    additive_frequency_based(cipher_text);

    cipher_text = "lmqetxyeagtxctuiewnctxlzewuaispzyvapewlmgqwyaxftcjmsqcadagtxlmdxnxsnpjqsyvapriqsmhnocvaxfv";
    hill_frequency_attack(cipher_text, 3);

    cipher_text = "hudskuaezgxravtfpgwswgwszhtppbillrtzpzhwloijvficvbthlugilgprkhwmyhtiuaxrbhtwucgxospwaochimcsyhwqhwcfyocgogtzlbilswbflohxzwsizvdsatgsthwissuxlmtsmhwikspxogwihrpflsamusuvvaillhgilhwvvivlavtwocijpticmstxvii";
    cipher_text = "nejorkdemxddotrdenork";
    vigenere_kasiki_attack(cipher_text);

    DynamicBitset bs = DynamicBitset(0xB, 4);
    DynamicBitset bs1 = DynamicBitset("1011");
    SBox sbox = SBox(4, 4,
                     {
                             0xE, 0x4, 0xD, 0x1,
                             0x2, 0xF, 0xB, 0x8,
                             0x3, 0xA, 0x6, 0xC,
                             0x5, 0x9, 0x0, 0x7});
    PBox pbox = PBox({
                             0, 4, 8, 12,
                             1, 5, 9, 13,
                             2, 6, 10, 14,
                             3, 7, 11, 15});
    vector<DynamicBitset> round_keys = {
            DynamicBitset("0011101010010100"),
            DynamicBitset("1010100101001101"),
            DynamicBitset("1001010011010110"),
            DynamicBitset("0100110101100011"),
            DynamicBitset("1101011000111111"),
    };
    SpNetwork spn = SpNetwork(pbox, sbox, 16, 5, round_keys);
    DynamicBitset input = DynamicBitset("0010011010110111");
    spn.encrypt_block(input).print();
}