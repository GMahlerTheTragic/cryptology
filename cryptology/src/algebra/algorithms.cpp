#include "cryptology/algebra/algorithms.hpp"

#include <iostream>

#include "cryptology/algebra/matrix.hpp"
#include "cryptology/algebra/vector.hpp"

using std::cout;
using std::runtime_error;
using std::string;

int64_t Mod(int64_t input, int64_t modulus) { return (input % modulus + modulus) % modulus; }

bool IsInvertible(int64_t input, int64_t modulus) { return Euclid(input, modulus) == 1; }

int64_t Inverse(int64_t input, int64_t modulus) {
    if (!IsInvertible(input, modulus)) {
        throw runtime_error("left side is not invertible modulo right side");
    }
    return Mod(ExtendedEuclid(input, modulus).factor_left, modulus);
}

int64_t Euclid(int64_t first, int64_t second) {
    if (first < second) {
        int64_t temp = first;
        first = second;
        second = temp;
    }

    int64_t rest = -1;

    while (rest != 0) {
        rest = Mod(first, second);
        first = second;
        second = rest;
    }

    return first;
}

struct GcdDecomposition ExtendedEuclid(int64_t first, int64_t second) {
    struct GcdDecomposition result {};
    int64_t *smaller_p = nullptr;
    int64_t *larger_p = nullptr;
    if (first < second) {
        int64_t temp = first;
        first = second;
        second = temp;
        smaller_p = &result.factor_left;
        larger_p = &result.factor_right;
    } else {
        smaller_p = &result.factor_right;
        larger_p = &result.factor_left;
    }
    int64_t rest = -1;
    int64_t rest_factor = -1;
    int64_t p_temp = 0;
    int64_t q_temp = 0;
    int64_t p_zero = 1;
    int64_t p_one = 0;
    int64_t q_zero = 0;
    int64_t q_one = 1;
    int64_t interations_counter = 0;
    while (rest != 0) {
        if (interations_counter++ != 0) {
            p_temp = p_one;
            q_temp = q_one;
            p_one = p_zero - rest_factor * p_one;
            q_one = q_zero - rest_factor * q_one;
            p_zero = p_temp;
            q_zero = q_temp;
        }
        rest_factor = first / second;
        rest = Mod(first, second);
        first = second;
        second = rest;
    }

    result.gcd = first;
    *larger_p = p_one;
    *smaller_p = q_one;
    return result;
}

template <int modulus>
void Elim(Matrix<modulus> &input, size_t row, size_t row_prime, size_t col, bool verbose = false) {
    if (input(row, col) > input(row_prime, col)) {
        size_t temp = row;
        row = row_prime;
        row_prime = temp;
    }
    int rest_factor = 0;
    while (input(row, col) != 0) {
        rest_factor = input(row_prime, col) / input(row, col);
        if (verbose) {
            cout << "rest_factor = " << input(row_prime, col) << " div " << input(row, col) << " = "
                 << rest_factor << endl;
        }
        input.set_row(row_prime, input.get_row(row_prime) - (input.get_row(row) * rest_factor));
        size_t temp = row;
        row = row_prime;
        row_prime = temp;
        if (verbose) {
            input.print();
        }
    }
}

template <int modulus>
int64_t Determinant(Matrix<modulus> input) {
    if (input.cols() != input.rows()) {
        throw std::runtime_error("Only implemented for square matrices");
    }
    size_t n_cols = input.cols();

    for (size_t j = 0; j < n_cols; ++j) {
        for (size_t i = n_cols - 1; i > j; --i) {
            if ((input(j, j) = true) && (input(i, j) = true)) {
                Elim(input, j, i, j);
            }
            if (input(i, j) > 0) {
                Vector<modulus> temp = input.get_row(i);
                input.set_row(i, input.get_row(j));
                input.set_row(j, temp * (-1));
            }
        }
    }

    int det = 1;
    for (size_t j = 0; j < n_cols; ++j) {
        det = Mod(det * input(j, j), modulus);
    }
    return det;
}

template <int modulus>
Matrix<modulus> Inverse(Matrix<modulus> input, bool verbose) {
    if (input.cols() != input.rows()) {
        throw std::runtime_error("Not invertible - not a square matrix");
    }
    size_t n_cols = input.cols();

    input = Matrix<modulus>::concat(input, Matrix<modulus>::eye(n_cols), 1);
    for (size_t j = 0; j < n_cols; ++j) {
        for (size_t i = n_cols - 1; i > j; --i) {
            if ((input(j, j) != 0) && (input(i, j) != 0)) {
                if (verbose) {
                    input.print();
                    cout << "j=" << j << ",i=" << i << ": Calling elim(A," << j << "," << i << ","
                         << j << ")" << endl;
                }
                Elim(input, j, i, j, verbose);
            }
            if (input(i, j) > 0) {
                Vector<modulus> temp = input.get_row(j);
                input.set_row(j, input.get_row(i));
                input.set_row(i, temp * (-1));
            }
        }
        int64_t gcd = Euclid(input(j, j), modulus);
        if (!(gcd == 1)) {
            throw std::runtime_error("Not invertible");
        }

        input.set_row(j, input.get_row(j) * Inverse(input(j, j), modulus));
        for (int i = static_cast<int>(j) - 1; i >= 0; i--) {
            input.set_row(i, input.get_row(i) - (input.get_row(j) * input(i, j)));
            if (verbose) {
                input.print();
            }
        }
    }

    Matrix<modulus> inverse = Matrix<modulus>(n_cols, n_cols);

    for (size_t j = 0; j < n_cols; ++j) {
        inverse.set_col(j, input.get_col(n_cols + j));
    }

    return inverse;
}

template int64_t Determinant(Matrix<26> input);

template Matrix<26> Inverse(Matrix<26> A, bool verbose);

template int64_t Determinant(Matrix<5> input);

template Matrix<5> Inverse(Matrix<5> A, bool verbose);
