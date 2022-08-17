#include <iostream>

#include "cryptology/cpp/modular_arithmetic/residue_class.cpp"

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
}