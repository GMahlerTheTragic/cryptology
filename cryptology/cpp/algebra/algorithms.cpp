#include <iostream>
#include <cryptology/algebra/algorithms.hpp>
#include <cryptology/algebra/matrix.hpp>
#include <cryptology/algebra/vector.hpp>

using namespace std;

int mod(int i, int n) {
    return (i % n + n) % n;
}

long mod(long i, long n) {
    return (i % n + n) % n;
}

bool is_invertible(long a, long m) {
        if (euklid(a, m) == 1) {
            return true;
        }
        return false;
}

long inverse(long a, long m) {
    if (!is_invertible(a, m)) {
        throw std::runtime_error("left side is not invertible modulo right side"); 
    }
    return mod(extended_euklid(a, m).factor_left, m);
}

long euklid(long a, long b) {
    if (a < b) {
        long temp = a;
        a = b;
        b = temp;
    }
    long r;
    do {
        r = mod(a, b);
        a = b;
        b = r;
    } while (r != 0);

    return a;
}

struct gcd_decomposition extended_euklid(long a, long b) {
    struct gcd_decomposition result;
    long* smaller_p;
    long* larger_p;
    if (a < b) {
        long temp = a;
        a = b;
        b = temp;
        smaller_p = &result.factor_left;
        larger_p = &result.factor_right;
    }
    else {
        smaller_p = &result.factor_right;
        larger_p = &result.factor_left;
    }
    long r, d, p_temp, q_temp;
    long p0 = 1;
    long p1 = 0;
    long q0 = 0;
    long q1 = 1;
    long i = 0;
    do {
        if (i++ != 0) {
            p_temp = p1;
            q_temp = q1;
            p1 = p0 - d*p1;
            q1 = q0 - d*q1;
            p0 = p_temp;
            q0 = q_temp;
        }
        d = a / b;
        r = mod(a, b);
        a = b;
        b = r;
    } while (r != 0);

    result.gcd = a;
    *larger_p = p1;
    *smaller_p = q1;
    return result;
}

template<int modulus>
long elim(Matrix<modulus> &A, size_t i, size_t i_prime, size_t j, bool verbose=false) {
    if (A(i, j) > A(i_prime, j)) {
        size_t temp = i;
        i = i_prime;
        i_prime = temp;
    }
    int d;
    while (A(i, j) != 0) {
        d = A(i_prime, j) / A(i, j);
        if (verbose)
            cout << "d = " << A(i_prime, j) << " div " << A(i, j) << " = " << d << endl;
        A.set_row(i_prime, A.get_row(i_prime) - (A.get_row(i) * d));
        size_t temp = i;
        i = i_prime;
        i_prime = temp;
        if (verbose)
            A.print();
    }
    
}

template<int modulus>
long determinant(Matrix<modulus> A) {
    if (A.cols() != A.rows()) {
        throw std::runtime_error("Only implemented for square matrices");
    }
    size_t n = A.cols();

    
    for (size_t j = 0; j < n; ++j) {
        for (size_t i = n - 1; i > j; --i) {
            if ((A(j, j) =! 0) && (A(i, j) =! 0)) {
                elim(A, j, i, j);
            }
            if (A(i, j) > 0) {
                Vector<modulus> temp = A.get_row(i);
                A.set_row(i, A.get_row(j));
                A.set_row(j, temp * (-1));
            }
        }
    }

    int det = 1;
    for (size_t j = 0; j < n; ++j) {
        det = mod(det * A(j,j), modulus);
    }
    return det;
}

template<int modulus>
Matrix<modulus> inverse(Matrix<modulus> A, bool verbose) {
    if (A.cols() != A.rows()) {
        throw std::runtime_error("Not invertible - not a square matrix");
    }
    size_t n = A.cols();

    A = Matrix<modulus>::concat(A, Matrix<modulus>::eye(n), 1);
    for (size_t j = 0; j < n; ++j) {
        for (size_t i = n - 1; i > j; --i) {
            if ((A(j, j) != 0) && (A(i, j) != 0)) {
                if (verbose) {
                    A.print();
                    cout << "j=" << j << ",i="<<i<<": Calling elim(A,"<<j<<","<<i<<","<<j<<")"<<endl;
                }
                elim(A, j, i, j, verbose);
            }
            if (A(i, j) > 0) {
                Vector<modulus> temp = A.get_row(j);
                A.set_row(j, A.get_row(i));
                A.set_row(i, temp * (-1));
            }
        }
        long gcd = euklid(A(j, j), modulus);
        if (gcd == 1) {
            A.set_row(j, A.get_row(j) * inverse(A(j, j), modulus));
            for (int i = j - 1; i >= 0; i--) {
                A.set_row(i, A.get_row(i) - (A.get_row(j) * A(i, j)));
                if (verbose)
                    A.print();
            }
        }
        else {
            throw std::runtime_error("Not invertible");
        }
    }

    Matrix<modulus> inverse = Matrix<modulus>(n, n);
    
    for (size_t j = 0; j < n; ++j) {
        inverse.set_col(j, A.get_col(n + j));
    }

    return inverse;
}
