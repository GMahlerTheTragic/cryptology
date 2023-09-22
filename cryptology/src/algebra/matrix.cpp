#include <iostream>

#include <cryptology/algebra/matrix.hpp>
#include <cryptology/algebra/vector.hpp>

using namespace std;

template<int modulus>
Matrix<modulus>::Matrix(size_t nrows, size_t ncols, int default_value)
    : ncols(ncols), nrows(nrows),
      values(ncols * nrows, mod(default_value, modulus)) {}

template<int modulus>
Matrix<modulus>::Matrix(const std::vector<std::vector<int>> &values)
    : Matrix<modulus>(values.size(),
                      values.empty() ? 0 : values[0].size()) {
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
Matrix<modulus> Matrix<modulus>::operator*(const long rhs) const {

  Matrix<modulus> result(rows(), cols());

  for (size_t row = 0; row < result.rows(); ++row)
    for (size_t col = 0; col < result.cols(); ++col)
      result(row, col) = mod((*this)(row, col) * rhs, modulus);

  return result;
}

template<int modulus>
Vector<modulus> Matrix<modulus>::operator*(const Vector<modulus> &rhs) const {

  if (rhs.size() != cols())
    throw std::runtime_error("Sizes do not match");

  Vector<modulus> result(rows());

  auto dot = [&](size_t row) -> int {
    int result = 0;
    for (size_t i = 0; i < cols(); ++i)
      result += (*this)(row, i) * rhs(i);
    return result;
  };

  for (size_t row = 0; row < result.size(); ++row)
    result(row) = mod(dot(row), modulus);

  return result;
}

template<int modulus>
Matrix<modulus> Matrix<modulus>::operator+(const Matrix<modulus> &rhs) const {

  if ((rhs.rows() != rows()) || (rhs.cols() != cols()))
    throw std::runtime_error("Sizes do not match");

  Matrix<modulus> result(rows(), cols());

  for (size_t row = 0; row < result.rows(); ++row)
    for (size_t col = 0; col < result.cols(); ++col)
      result(row, col) = mod(((*this)(row, col) + rhs(row, col)),
                             modulus);

  return result;
}

template<int modulus>
Matrix<modulus> Matrix<modulus>::operator-(const Matrix<modulus> &rhs) const {

  if ((rhs.rows() != rows()) || (rhs.cols() != cols()))
    throw std::runtime_error("Sizes do not match");

  Matrix<modulus> result(rows(), cols());

  for (size_t row = 0; row < result.rows(); ++row)
    for (size_t col = 0; col < result.cols(); ++col)
      result(row, col) = mod(((*this)(row, col) - rhs(row, col)),
                             modulus);

  return result;
}

template<int modulus>
Vector<modulus> Matrix<modulus>::get_col(const size_t col) const {
  Vector<modulus> result = Vector<modulus>(rows());
  for (int i = 0; i < rows(); ++i)
    result(i) = (*this)(i, col);
  return result;
}

template<int modulus>
Vector<modulus> Matrix<modulus>::get_row(const size_t row) const {
  Vector<modulus> result = Vector<modulus>(cols());
  for (int i = 0; i < cols(); ++i)
    result(i) = (*this)(row, i);
  return result;
}

template<int modulus>
void Matrix<modulus>::set_col(const size_t col, Vector<modulus> col_values) {
  if (col_values.size() != rows()) {
    throw std::runtime_error("Sizes do not match");
  }
  for (int i = 0; i < rows(); ++i)
    (*this)(i, col) = col_values(i);
}

template<int modulus>
void Matrix<modulus>::set_row(const size_t row, Vector<modulus> row_values) {
  if (row_values.size() != cols())
    throw std::runtime_error("Sizes do not match");
  for (int i = 0; i < cols(); ++i)
    (*this)(row, i) = row_values(i);
}

template<int modulus>
Matrix<modulus>
Matrix<modulus>::concat(const Matrix<modulus> A, const Matrix<modulus> B,
                        int axis) {
  if (axis == 0) {
    if (A.cols() != B.cols()) {
      throw std::runtime_error("Column lengthts do not match");
    }
    Matrix<modulus> result = Matrix<modulus>(A.rows() + B.rows(), A.cols());
    for (int i = 0; i < A.rows(); ++i)
      result.set_row(i, A.get_row(i));
    for (int i = A.rows(); i < A.rows() + B.rows(); ++i)
      result.set_row(i, B.get_row(i));
    return result;
  } else if (axis == 1) {
    if (A.rows() != B.rows()) {
      throw std::runtime_error("Row lengthts do not match");
    }
    Matrix<modulus> result = Matrix<modulus>(A.rows(), A.cols() + B.cols());
    for (int i = 0; i < A.cols(); ++i)
      result.set_col(i, A.get_col(i));
    for (int i = 0; i < B.cols(); ++i)
      result.set_col(A.cols() + i, B.get_col(i));
    return result;
  } else {
    throw std::runtime_error("Axis must be 0 or 1");
  }
}

template<int modulus>
Matrix<modulus> Matrix<modulus>::eye(size_t dim) {
  Matrix<modulus> result = Matrix<modulus>(dim, dim);
  for (size_t i = 0; i < dim; ++i) {
    result(i, i) = 1;
  }
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

template
class Matrix<26>;

template
class Matrix<5>;

