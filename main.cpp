#include <iostream>

#include "cryptology/cpp/algebra/residue_class.cpp"
#include "cryptology/cpp/algebra/matrix.cpp"
#include "cryptology/cpp/algebra/vector.cpp"
#include "cryptology/cpp/algebra/algorithms.cpp"
#include "cryptology/cpp/utils.cpp"
#include "cryptology/cpp/ciphers/affine_cipher.cpp"
#include "cryptology/cpp/ciphers/stream_cipher.cpp"
#include "cryptology/cpp/ciphers/hill_cipher.cpp"

using namespace std;
using namespace RC;

int main() {
    ResidueClass<5> a = ResidueClass<5>(3);
    ResidueClass<5> b = ResidueClass<5>(4);
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;

    Matrix<5> m = Matrix<5>({{1, 2, 2, 3},
                             {1, 2, 2, 3},
                             {1, 2, 2, 3},
                             {1, 2, 2, 3}});

    Matrix<5> n = Matrix<5>({{1, 2, 2, 3},
                             {1, 2, 2, 3},
                             {1, 2, 2, 3},
                             {1, 2, 2, 3}});

    Matrix<26> H = Matrix<26>({{11, 13, 8, 21},
                             {24, 17, 3, 25},
                             {18, 12, 23, 17},
                             {6, 15, 2, 15}});
    n(0,0) = 8;
    (n * m).print();


    Vector<26> hill = Vector<26>({7, 8, 11, 11});
    Vector<26> hillH = hill * H;
    Vector<26> Hhill = H * hill;

    hillH.print();
    Hhill.print();

    Matrix<26> H_inv = inverse(H);
    H_inv.print();

    long left = 513;
    long right = 29;
    struct gcd_decomposition res = extended_euklid(left, right);
    cout << res.gcd << " " << res.factor_left << " " <<   res.factor_right  << endl;

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
}