#include "cryptology/algebra/matrix.hpp"

#include <iostream>
#include <cstdint>

#include "cryptology/algebra/vector.hpp"
#include "cryptology/algebra/algorithms.hpp"

using std::cout;
using std::runtime_error;
using std::vector;

template <int modulus>
Matrix<modulus>::Matrix(size_t nrows, size_t ncols, int default_value)
    : ncols(ncols), nrows(nrows), values(ncols * nrows, Mod(default_value, modulus)) {}

template <int modulus>
Matrix<modulus>::Matrix(const std::vector<std::vector<int>> &values)
    : Matrix<modulus>(values.size(), values.empty() ? 0 : values[0].size()) {
    size_t index = 0;
    for (const auto &row : values) {
        for (const int kval : row) {
            this->values[index++] = Mod(kval, modulus);
        }
    }
}

template <int modulus>
Matrix<modulus> Matrix<modulus>::operator*(const Matrix<modulus> &rhs) const {
    if (rhs.rows() != cols()) {
        throw std::runtime_error("Sizes do not match");
    }

    Matrix<modulus> result(rows(), rhs.cols());

    auto dot = [&](size_t row, size_t col) -> int {
        int result = 0;
        for (size_t i = 0; i < cols(); ++i) {
            result += (*this)(row, i) * rhs(i, col);
        }
        return result;
    };

    for (size_t row = 0; row < result.rows(); ++row) {
        for (size_t col = 0; col < result.cols(); ++col) {
            result(row, col) = Mod(dot(row, col), modulus);
        }
    }

    return result;
}

template <int modulus>
Matrix<modulus> Matrix<modulus>::operator*(const int64_t krhs) const {
    Matrix<modulus> result(rows(), cols());

    for (size_t row = 0; row < result.rows(); ++row) {
        for (size_t col = 0; col < result.cols(); ++col) {
            result(row, col) = Mod((*this)(row, col) * krhs, modulus);
        }
    }

    return result;
}

template <int modulus>
Vector<modulus> Matrix<modulus>::operator*(const Vector<modulus> &rhs) const {
    if (rhs.size() != cols()) {
        throw std::runtime_error("Sizes do not match");
    }

    Vector<modulus> result(rows());

    auto dot = [&](size_t row) -> int {
        int result = 0;
        for (size_t i = 0; i < cols(); ++i) {
            result += (*this)(row, i) * rhs(i);
        }
        return result;
    };

    for (size_t row = 0; row < result.size(); ++row) {
        result(row) = Mod(dot(row), modulus);
    }

    return result;
}

template <int modulus>
Matrix<modulus> Matrix<modulus>::operator+(const Matrix<modulus> &rhs) const {
    if ((rhs.rows() != rows()) || (rhs.cols() != cols())) {
        throw std::runtime_error("Sizes do not match");
    }

    Matrix<modulus> result(rows(), cols());

    for (size_t row = 0; row < result.rows(); ++row) {
        for (size_t col = 0; col < result.cols(); ++col) {
            result(row, col) = Mod(((*this)(row, col) + rhs(row, col)), modulus);
        }
    }

    return result;
}

template <int modulus>
Matrix<modulus> Matrix<modulus>::operator-(const Matrix<modulus> &rhs) const {
    if ((rhs.rows() != rows()) || (rhs.cols() != cols())) {
        throw std::runtime_error("Sizes do not match");
    }

    Matrix<modulus> result(rows(), cols());

    for (size_t row = 0; row < result.rows(); ++row) {
        for (size_t col = 0; col < result.cols(); ++col) {
            result(row, col) = Mod(((*this)(row, col) - rhs(row, col)), modulus);
        }
    }

    return result;
}

template <int modulus>
bool Matrix<modulus>::operator==(const Matrix<modulus> &rhs) const {
    if ((rhs.rows() != rows()) || (rhs.cols() != cols())) {
        return false;
    }

    Matrix<modulus> result(rows(), cols());

    for (size_t row = 0; row < this->rows(); ++row) {
        for (size_t col = 0; col < this->cols(); ++col) {
            if ((*this)(row, col) != rhs(row, col)) {
                return false;
            }
        }
    }

    return true;
}

template <int modulus>
Vector<modulus> Matrix<modulus>::get_col(const size_t kcol) const {
    Vector<modulus> result = Vector<modulus>(rows());
    for (int i = 0; i < rows(); ++i) {
        result(i) = (*this)(i, kcol);
    }
    return result;
}

template <int modulus>
Vector<modulus> Matrix<modulus>::get_row(const size_t krow) const {
    Vector<modulus> result = Vector<modulus>(cols());
    for (int i = 0; i < cols(); ++i) {
        result(i) = (*this)(krow, i);
    }
    return result;
}

template <int modulus>
void Matrix<modulus>::set_col(const size_t kcol, Vector<modulus> col_values) {
    if (col_values.size() != rows()) {
        throw std::runtime_error("Sizes do not match");
    }
    for (int i = 0; i < rows(); ++i) {
        (*this)(i, kcol) = col_values(i);
    }
}

template <int modulus>
void Matrix<modulus>::set_row(const size_t krow, Vector<modulus> row_values) {
    if (row_values.size() != cols()) {
        throw std::runtime_error("Sizes do not match");
    }
    for (int i = 0; i < cols(); ++i) {
        (*this)(krow, i) = row_values(i);
    }
}

template <int modulus>
Matrix<modulus> Matrix<modulus>::concat(const Matrix<modulus> left, const Matrix<modulus> right,
                                        int axis) {
    if (axis == 0) {
        if (left.cols() != right.cols()) {
            throw std::runtime_error("Column lengthts do not match");
        }
        Matrix<modulus> result = Matrix<modulus>(left.rows() + right.rows(), left.cols());
        for (int i = 0; i < left.rows(); ++i) {
            result.set_row(i, left.get_row(i));
        }
        for (int i = 0; i < right.rows(); ++i) {
            result.set_row(left.rows() + i, right.get_row(i));
        }

        return result;
    }
    if (axis == 1) {
        if (left.rows() != right.rows()) {
            throw std::runtime_error("Row lengthts do not match");
        }
        Matrix<modulus> result = Matrix<modulus>(left.rows(), left.cols() + right.cols());
        for (int i = 0; i < left.cols(); ++i) {
            result.set_col(i, left.get_col(i));
        }
        for (int i = 0; i < right.cols(); ++i) {
            result.set_col(left.cols() + i, right.get_col(i));
        }
        return result;
    }
    throw runtime_error("Axis must be 0 or 1");
}

template <int modulus>
Matrix<modulus> Matrix<modulus>::eye(size_t dim) {
    Matrix<modulus> result = Matrix<modulus>(dim, dim);
    for (size_t i = 0; i < dim; ++i) {
        result(i, i) = 1;
    }
    return result;
}

template <int modulus>
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

template <int modulus>
int& Matrix<modulus>::operator()(size_t row, size_t col) {
    if (row >= rows() || col >= cols() || row < 0 || col < 0) {
        throw std::runtime_error("Index out of bounds");
    }
    return values[cols() * row + col];
}

template <int modulus>
int64_t Matrix<modulus>::operator()(size_t row, size_t col) const {
    if (row >= rows() || col >= cols() || row < 0 || col < 0) {
        throw std::runtime_error("Index out of bounds");
    }
    return Mod(values[cols() * row + col], modulus);
}

constexpr uint8_t knumber_of_letters_in_alphabet = 26;
template class Matrix<knumber_of_letters_in_alphabet>;

constexpr uint8_t kfive = 5;
template class Matrix<kfive>;
