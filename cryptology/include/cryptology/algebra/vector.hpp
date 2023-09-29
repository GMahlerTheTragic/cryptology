#ifndef CRYPTOLOGY_ALGEBRA_VECTOR_HPP_
#define CRYPTOLOGY_ALGEBRA_VECTOR_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "cryptology/algebra/algorithms.hpp"

using namespace std;

int64_t Mod(int64_t i, int64_t modulus);

template <int modulus>
class Matrix;

template <int modulus>
class Vector final {
   private:
    size_t _size{};
    vector<int> values;

   public:
    Vector<modulus>(size_t size, int default_value = 0);

    Vector<modulus>(const std::vector<int> &values);

    ~Vector<modulus>() = default;

    void print() const;

    Vector<modulus> operator*(const Matrix<modulus> &rhs) const;

    Vector<modulus> operator+(const Vector<modulus> &rhs) const;

    Vector<modulus> operator*(const int64_t &rhs) const;

    Vector<modulus> operator-(const Vector<modulus> &rhs) const;

    int &operator()(size_t idx) {
        if (idx >= size() || idx < 0) {
            throw std::runtime_error("Index out of bounds");
        }
        return values[idx];
    }

    int64_t operator()(size_t idx) const {
        if (idx >= size() || idx < 0) {
            throw std::runtime_error("Index out of bounds");
        }
        return Mod(values[idx], modulus);
    }

    size_t size() const { return this->_size; }

    bool operator==(const Vector<modulus> &rhs) const;
};

#endif