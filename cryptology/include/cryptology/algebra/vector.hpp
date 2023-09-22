#ifndef CRYPTOLOGY_ALGEBRA_VECTOR_HPP_
#define CRYPTOLOGY_ALGEBRA_VECTOR_HPP_

#include <iostream>
#include <vector>
#include <cryptology/algebra/algorithms.hpp>
#include <string>

using namespace std;

long mod(long i, long n);

template<int modulus>
class Matrix;

template<int modulus>
class Vector final {

private:
    size_t _size;
    vector<int> values;

public:
    Vector<modulus>(size_t size, int default_value = 0);

    Vector<modulus>(const std::vector<int> &values);

    ~Vector<modulus>() = default;

    void print() const;

    Vector<modulus> operator*(const Matrix<modulus> &rhs) const;

    Vector<modulus> operator+(const Vector<modulus> &rhs) const;

    Vector<modulus> operator*(const long &rhs) const;

    Vector<modulus> operator-(const Vector<modulus> &rhs) const;

    int &operator()(size_t idx) { return values[idx]; }

    long operator()(size_t idx) const {
        return mod(values[idx], modulus);
    }

    size_t size() const { return this->_size; }


};


#endif