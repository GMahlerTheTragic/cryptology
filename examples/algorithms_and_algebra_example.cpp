#include <iostream>
#include <string>

#include "cryptology.hpp"

using namespace std;
using namespace cryptology;

template class Matrix<26>;

template class Vector<26>;

int main() {
    cout << "This is an example for modular matrix algebra and modular GCD algorithms..." << endl;
    cout << endl;

    cout << "Matrix m: " << endl;
    Matrix<5> m = Matrix<5>({{1, 2, 2, 3}, {1, 2, 2, 3}, {1, 2, 2, 3}, {1, 2, 2, 3}});
    m.print();

    cout << "Matrix n: " << endl;
    Matrix<5> n = Matrix<5>({{1, 2, 2, 3}, {1, 2, 2, 3}, {1, 2, 2, 3}, {1, 2, 2, 3}});
    n.print();

    cout << "Matrix n x m: " << endl;
    (n * m).print();

    cout << "Matrix h: " << endl;
    Matrix<26> h = Matrix<26>({{11, 13, 8, 21}, {24, 17, 3, 25}, {18, 12, 23, 17}, {6, 15, 2, 15}});
    h.print();

    cout << "Vector hill: " << endl;
    Vector<26> hill = Vector<26>({7, 8, 11, 11});
    hill.print();

    cout << "hill x h: " << endl;
    Vector<26> hill_h = hill * h;
    hill_h.print();

    cout << "h{-1}: " << endl;
    Matrix<26> h_inv = Inverse(h);
    h_inv.print();

    int64_t left = 513;
    int64_t right = 29;
    struct GcdDecomposition res = ExtendedEuclid(left, right);
    cout << "Computing GCD(513, 29) and decomposition using Bezout's lemma" << endl;
    cout << "GCD(513, 29): " << res.gcd << " factor left: " << res.factor_left << " factor right: " << res.factor_right << endl;
}
