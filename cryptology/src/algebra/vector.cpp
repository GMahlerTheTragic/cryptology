#include "cryptology/algebra/vector.hpp"

#include <iostream>
#include <cstdint>

#include "cryptology/algebra/algorithms.hpp"
#include "cryptology/algebra/matrix.hpp"

using std::cout;
using std::runtime_error;
using std::vector;

template <int modulus>
Vector<modulus>::Vector(size_t size, int default_value)
    : _size(size), values(size, Mod(default_value, modulus)) {}

template <int modulus>
Vector<modulus>::Vector(const std::vector<int> &values) : Vector<modulus>(values.size()) {
    size_t index = 0;

    for (const int kval : values) {
        this->values[index++] = Mod(kval, modulus);
    }
}

template <int modulus>
Vector<modulus> Vector<modulus>::operator*(const Matrix<modulus> &rhs) const {
    if (rhs.rows() != size()) {
        throw std::runtime_error("Sizes do not match");
    }
    
    Vector<modulus> result(rhs.cols());

    auto dot = [&](size_t col) -> int {
        int result = 0;
        for (size_t i = 0; i < size(); ++i) {
            result += (*this)(i)*rhs(i, col);
        }
        return result;
    };

    for (size_t col = 0; col < result.size(); ++col) {
        result(col) = Mod(dot(col), modulus);
    }

    return result;
}

template <int modulus>
Vector<modulus> Vector<modulus>::operator+(const Vector<modulus> &rhs) const {
    if (rhs.size() != size()) {
        throw std::runtime_error("Sizes do not match");
    }

    Vector<modulus> result(size());

    for (size_t idx = 0; idx < result.size(); ++idx) {
        result(idx) = Mod(((*this)(idx) + rhs(idx)), modulus);
    }

    return result;
}

template <int modulus>
Vector<modulus> Vector<modulus>::operator-(const Vector<modulus> &rhs) const {
    if (rhs.size() != size()) {
        throw std::runtime_error("Sizes do not match");
    }

    Vector<modulus> result(size());

    for (size_t idx = 0; idx < result.size(); ++idx) {
        result(idx) = Mod(((*this)(idx)-rhs(idx)), modulus);
    }

    return result;
}

template <int modulus>
Vector<modulus> Vector<modulus>::operator*(const int64_t &rhs) const {
    Vector<modulus> result(size());

    for (size_t idx = 0; idx < result.size(); ++idx) {
        result(idx) = Mod(((*this)(idx)*rhs), static_cast<int64_t>(modulus));
    }

    return result;
}

template <int modulus>
void Vector<modulus>::print() const {
    cout << "[ ";
    for (size_t idx = 0; idx < size(); ++idx) {
        cout << (*this)(idx) << ", ";
    }
    cout << "]" << endl;
}

template <int modulus>
bool Vector<modulus>::operator==(const Vector<modulus> &rhs) const {
    if (rhs.size() != size()) {
        return false;
    }

    Vector<modulus> result(size());

    for (size_t row = 0; row < this->size(); ++row) {
        if ((*this)(row) != rhs(row)) {
            return false;
        }
    }

    return true;
}

template <int modulus>
int& Vector<modulus>::operator()(size_t idx) {
    if (idx >= size() || idx < 0) {
        throw std::runtime_error("Index out of bounds");
    }
    return values[idx];
}

template <int modulus>
int64_t Vector<modulus>::operator()(size_t idx) const {
    if (idx >= size() || idx < 0) {
        throw std::runtime_error("Index out of bounds");
    }
    return Mod(this->values[idx], modulus);
}

constexpr uint8_t knumber_of_letters_in_alphabet = 26;
template class Vector<knumber_of_letters_in_alphabet>;

constexpr uint8_t kfive = 5;
template class Vector<kfive>;
