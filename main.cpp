#include <iostream>

#include "cryptology/cpp/algebra/residue_class.cpp"
#include "cryptology/cpp/algebra/matrix.cpp"
#include "cryptology/cpp/algebra/algorithms.cpp"
#include "cryptology/cpp/ciphers/affine_cipher.cpp"

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
    n(0,0) = 8;
    (n * m).print();

    long left = 513;
    long right = 29;
    struct gcd_decomposition res = extended_euklid(left, right);
    cout << res.gcd << " " << res.factor_left << " " <<   res.factor_right  << endl;

    AffineCipher cipher = AffineCipher(8, 5);
    string cipher_text = cipher.encrypt("Hallo Welt");
    cout << "cipher text " << cipher_text << endl;
    cout << "plain text " << cipher.decrypt(cipher_text) << endl;
}