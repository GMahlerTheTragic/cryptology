#ifndef CRYPTOLOGY_ALGEBRA_RESIDUE_CLASS_HPP_
#define CRYPTOLOGY_ALGEBRA_RESIDUE_CLASS_HPP_

#include <iostream>
#include <string>

namespace RC {
    template<int modulus>
    class ResidueClass final {
    private:
        int residue;
    public:
        ResidueClass<modulus>(int value);
        ~ResidueClass<modulus>() = default;

        ResidueClass<modulus> operator+(const ResidueClass<modulus> &other) const;
        ResidueClass<modulus> operator-(const ResidueClass<modulus> &other) const;
        ResidueClass<modulus> operator*(const ResidueClass<modulus> &other) const;

        friend std::ostream& operator<<(std::ostream& os, const ResidueClass<modulus>& rc) {
            os << rc.residue << "_mod_" << modulus;
            return os;
        }


    };
}

#endif