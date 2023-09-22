#include <iostream>

#include <cryptology/algebra/matrix.hpp>
#include <cryptology/algebra/vector.hpp>
#include <cryptology/algebra/algorithms.hpp>

using namespace std;

template<int modulus>
Vector<modulus>::Vector(size_t size, int default_value)
        : _size(size), values(size, mod(default_value, modulus)) {}


template<int modulus>
Vector<modulus>::Vector(const std::vector<int> &values)
        : Vector<modulus>(values.size()) {
    size_t index = 0;

    for (const int val: values)
        this->values[index++] = mod(val, modulus);
}

template<int modulus>
Vector<modulus> Vector<modulus>::operator*(const Matrix<modulus> &rhs) const {

    if (rhs.rows() != size())
        throw std::runtime_error("Sizes do not match");

    Vector<modulus> result(rhs.cols());

    auto dot = [&](size_t col) -> int {
      int result = 0;
      for (size_t i = 0; i < size(); ++i)
          result += (*this)(i) * rhs(i, col);
      return result;
    };

    for (size_t col = 0; col < result.size(); ++col)
        result(col) = mod(dot(col), modulus);

    return result;
}

template<int modulus>
Vector<modulus> Vector<modulus>::operator+(const Vector<modulus> &rhs) const {

    if (rhs.size() != size())
        throw std::runtime_error("Sizes do not match");

    Vector<modulus> result(size());

    for (size_t idx = 0; idx < result.size(); ++idx)
        result(idx) = mod(((*this)(idx) + rhs(idx)), modulus);

    return result;
}

template<int modulus>
Vector<modulus> Vector<modulus>::operator-(const Vector<modulus> &rhs) const {

    if (rhs.size() != size())
        throw std::runtime_error("Sizes do not match");

    Vector<modulus> result(size());

    for (size_t idx = 0; idx < result.size(); ++idx)
        result(idx) = mod(((*this)(idx) - rhs(idx)), modulus);

    return result;
}

template<int modulus>
Vector<modulus> Vector<modulus>::operator*(const long &rhs) const {

    Vector<modulus> result(size());

    for (size_t idx = 0; idx < result.size(); ++idx)
        result(idx) = mod(((*this)(idx) * rhs), (long) modulus);

    return result;
}

template<int modulus>
void Vector<modulus>::print() const {
    cout << "[ ";
    for (size_t idx = 0; idx < size(); ++idx) {
        cout << (*this)(idx) << ", ";
    }
    cout << "]" << endl;
}


template
class Vector<26>;

template
class Vector<5>;
