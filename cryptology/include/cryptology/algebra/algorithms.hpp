#ifndef CRYPTOLOGY_ALGEBRA_ALGORITHMS_HPP_
#define CRYPTOLOGY_ALGEBRA_ALGORITHMS_HPP_

#include "cryptology/algebra/matrix.hpp"
#include "cryptology/algebra/vector.hpp"

using namespace std;

int64_t Mod(int64_t input, int64_t modulus);

struct GcdDecomposition {
    int64_t gcd;
    int64_t factor_left;
    int64_t factor_right;
} typedef GcdDecomposition;

bool IsInvertible(int64_t input, int64_t m);

int64_t Inverse(int64_t input, int64_t m);

int64_t Euclid(int64_t first, int64_t second);

struct GcdDecomposition ExtendedEuclid(int64_t first, int64_t second);

template <int modulus>
int64_t Determinant(Matrix<modulus> input);

template <int modulus>
Matrix<modulus> Inverse(Matrix<modulus> input, bool verbose = false);

#endif
