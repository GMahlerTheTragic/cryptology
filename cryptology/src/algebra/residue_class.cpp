#include "cryptology/algebra/residue_class.hpp"

#include "cryptology/algebra/algorithms.hpp"

using RC::ResidueClass;

template <int modulus>
ResidueClass<modulus>::ResidueClass(int value) {
    this->residue = Mod(value, modulus);
}

template <int modulus>
ResidueClass<modulus> ResidueClass<modulus>::operator+(const ResidueClass<modulus> &other) const {
    return ResidueClass<modulus>(Mod((other.residue + this->residue), modulus));
}

template <int modulus>
ResidueClass<modulus> ResidueClass<modulus>::operator-(const ResidueClass<modulus> &other) const {
    return ResidueClass<modulus>(Mod((other.residue - this->residue), modulus));
}

template <int modulus>
ResidueClass<modulus> ResidueClass<modulus>::operator*(const ResidueClass<modulus> &other) const {
    return ResidueClass<modulus>(Mod((other.residue * this->residue), modulus));
}
