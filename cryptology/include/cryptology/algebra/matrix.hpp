#ifndef CRYPTOLOGY_ALGEBRA_MATRIX_HPP_
#define CRYPTOLOGY_ALGEBRA_MATRIX_HPP_

#include <iostream>
#include <vector>
#include <cryptology/algebra/algorithms.hpp>
#include <cryptology/algebra/vector.hpp>
#include <string>

using namespace std;

long mod(long i, long n);


template<int modulus>
class Vector;

template<int modulus>
class Matrix final {

private:
    size_t ncols;
    size_t nrows;

    vector<int> values;

public:
    Matrix<modulus>(size_t nrows, size_t ncols, int default_value = 0);

    Matrix<modulus>(const std::vector<std::vector<int>> &values);

    ~Matrix<modulus>() = default;

    void print() const;

    Matrix<modulus> operator*(const Matrix<modulus> &rhs) const;

    Vector<modulus> operator*(const Vector<modulus> &rhs) const;

    Matrix<modulus> operator*(const long rhs) const;

    Matrix<modulus> operator+(const Matrix<modulus> &rhs) const;

    Matrix<modulus> operator-(const Matrix<modulus> &rhs) const;

    int &operator()(size_t row, size_t col) {
        return values[cols() * row + col];
    }

    long operator()(size_t row, size_t col) const {
        return mod(values[cols() * row + col], modulus);
    }
    
    Vector<modulus> get_col(const size_t col) const;

    Vector<modulus> get_row(const size_t row) const;

    void set_col(const size_t col, Vector<modulus> col_values);

    void set_row(const size_t row, Vector<modulus> row_values);

    size_t rows() const { return this->nrows; }

    size_t cols() const { return this->ncols; }

    static Matrix<modulus>
    concat(const Matrix<modulus> A, const Matrix<modulus> B, int axis = 0);

    static Matrix<modulus> eye(size_t dim);

};

#endif