#ifndef CRYPTOLOGY_ALGEBRA_MATRIX_HPP_
#define CRYPTOLOGY_ALGEBRA_MATRIX_HPP_

#include <vector>

#include "cryptology/algebra/vector.hpp"

using namespace std;

template <int modulus>
class Vector;

template <int modulus>
class Matrix final {
   private:
    size_t ncols{};
    size_t nrows{};

    vector<int> values;

   public:
    Matrix(size_t nrows, size_t ncols, int default_value = 0);

    explicit Matrix(const std::vector<std::vector<int>> &values);

    ~Matrix() = default;

    void print() const;

    Matrix operator*(const Matrix &rhs) const;

    Vector<modulus> operator*(const Vector<modulus> &rhs) const;

    Matrix operator*(int64_t rhs) const;

    Matrix operator+(const Matrix &rhs) const;

    Matrix operator-(const Matrix &rhs) const;

    int &operator()(size_t row, size_t col);

    int64_t operator()(size_t row, size_t col) const;

    bool operator==(const Matrix &rhs) const;

    Vector<modulus> get_col(size_t col) const;

    Vector<modulus> get_row(size_t row) const;

    void set_col(size_t col, Vector<modulus> col_values);

    void set_row(size_t row, Vector<modulus> row_values);

    [[nodiscard]] size_t rows() const { return this->nrows; }

    [[nodiscard]] size_t cols() const { return this->ncols; }

    static Matrix concat(Matrix left, Matrix right,
                                  int axis = 0);

    static Matrix eye(size_t dim);
};

#endif
