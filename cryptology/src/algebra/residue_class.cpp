#include <cryptology/algebra/residue_class.hpp>
#include <cryptology/algebra/algorithms.hpp>

using namespace std;
using namespace RC;

template<int modulus>
ResidueClass<modulus>::ResidueClass(int value) {
  this->residue = mod(value, modulus);
}

template<int modulus>
ResidueClass<modulus>
ResidueClass<modulus>::operator+(const ResidueClass<modulus> &other) const {
  return ResidueClass<modulus>(mod((other.residue + this->residue), modulus));
}

template<int modulus>
ResidueClass<modulus>
ResidueClass<modulus>::operator-(const ResidueClass<modulus> &other) const {
  return ResidueClass<modulus>(mod((other.residue - this->residue), modulus));
}

template<int modulus>
ResidueClass<modulus>
ResidueClass<modulus>::operator*(const ResidueClass<modulus> &other) const {
  return ResidueClass<modulus>(mod((other.residue * this->residue), modulus));
}
