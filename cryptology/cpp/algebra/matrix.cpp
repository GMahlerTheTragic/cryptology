#include <iostream>

#include <cryptology/algebra/matrix.hpp>
#include <cryptology/algebra/algorithms.hpp>

using namespace std;

template<int modulus>
Matrix<modulus>::Matrix(size_t ncols, size_t nrows, int default_value)
    : ncols(ncols), nrows(nrows), values(ncols * nrows, mod(default_value, modulus)) {};


template <int modulus>
Matrix<modulus>::Matrix(const std::vector<std::vector<int>> &values)
    : Matrix<modulus>(values.size(), values.empty() ? 0 : values[0].size()) {
    size_t index = 0;
    for (const auto &row : values)
        for (const int val : row)
            this->values[index++] = mod(val, modulus);
}

template<int modulus>
Matrix<modulus> Matrix<modulus>::operator*(const Matrix<modulus> &rhs) const {

    if (rhs.rows() != cols())
         throw std::runtime_error("Sizes do not match");

     Matrix<modulus> result(rows(), rhs.cols());

    auto dot = [&](size_t row, size_t col) -> int {
        int result = 0;
        for (size_t i = 0; i < cols(); ++i)
            result += (*this)(row, i) * rhs(i, col);
        return result;
    };

    for (size_t row = 0; row < result.rows(); ++row)
        for (size_t col = 0; col < result.cols(); ++col)
            result(row, col) = mod(dot(row, col), modulus);

     return result;
}

template<int modulus>
Matrix<modulus> Matrix<modulus>::operator+(const Matrix<modulus> &rhs) const {

    if ((rhs.rows() != rows()) || (rhs.cols() != cols()))
         throw std::runtime_error("Sizes do not match");

     Matrix<modulus> result(rows(), cols());

    for (size_t row = 0; row < result.rows(); ++row)
        for (size_t col = 0; col < result.cols(); ++col)
            result(row, col) = mod(((*this)(row, col) + rhs(row, col)), modulus);

     return result;
}

template<int modulus>
Matrix<modulus> Matrix<modulus>::operator-(const Matrix<modulus> &rhs) const {

    if ((rhs.rows() != rows()) || (rhs.cols() != cols()))
         throw std::runtime_error("Sizes do not match");

     Matrix<modulus> result(rows(), cols());

    for (size_t row = 0; row < result.rows(); ++row)
        for (size_t col = 0; col < result.cols(); ++col)
            result(row, col) = mod(((*this)(row, col) - rhs(row, col)), modulus);

     return result;
}

template<int modulus>
void Matrix<modulus>::print() const {
    cout << "[" << endl;
    for (size_t row = 0; row < rows(); ++row) {
        cout << "[ ";
        for (size_t col = 0; col < cols(); ++col) {
            cout << (*this)(row, col) << ", ";
        }
        cout << "]" << endl;
    }
    cout << "]" << endl;
}
