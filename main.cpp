#include <iostream>

#include "cryptology/cpp/algebra/residue_class.cpp"
#include "cryptology/cpp/algebra/matrix.cpp"

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
}