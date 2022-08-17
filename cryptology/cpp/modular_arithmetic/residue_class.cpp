#include <iostream>

#include <cryptology/modular_arithmetic/residue_class.hpp>

using namespace std;
using namespace RC;

template<int modulus>
ResidueClass<modulus>::ResidueClass(int value) {
    this->residue = value % modulus;
}

template<int modulus>
ResidueClass<modulus> ResidueClass<modulus>::operator+(const ResidueClass<modulus> &other) const {
    return ResidueClass<modulus>((other.residue + this->residue) % modulus);
}

template<int modulus>
ResidueClass<modulus> ResidueClass<modulus>::operator-(const ResidueClass<modulus> &other) const {
    return ResidueClass<modulus>((other.residue - this->residue) % modulus);
}

template<int modulus>
ResidueClass<modulus> ResidueClass<modulus>::operator*(const ResidueClass<modulus> &other) const {
    return ResidueClass<modulus>((other.residue * this->residue) % modulus);
}
