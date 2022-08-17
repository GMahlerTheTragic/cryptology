#ifndef CRYPTOLOGY_ALGEBRA_MATRIX_HPP_
#define CRYPTOLOGY_ALGEBRA_MATRIX_HPP_

#include <iostream>
#include <vector>

using namespace std;

template<int modulus>
class Matrix final {

private:
    int residue = modulus;
    size_t ncols;
    size_t nrows;

    vector<int> values;
    
public:
    Matrix<modulus>(size_t ncols, size_t nrows, int default_value = 0);
    Matrix<modulus>(const std::vector<std::vector<int>> &values);
    ~Matrix<modulus>() = default;

    void print() const;

    Matrix<modulus> operator*(const Matrix<modulus> &rhs) const;
    Matrix<modulus> operator+(const Matrix<modulus> &rhs) const;
    Matrix<modulus> operator-(const Matrix<modulus> &rhs) const;

    int &operator()(size_t row, size_t col) { return values[cols() * row + col]; }
    const int &operator()(size_t row, size_t col) const { return values[cols() * row + col] % modulus; }

    
    size_t rows() const { return this->nrows; }
    size_t cols() const { return this->ncols; }

};


#endif