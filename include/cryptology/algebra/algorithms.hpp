#ifndef CRYPTOLOGY_ALGEBRA_ALGORITHMS_HPP_
#define CRYPTOLOGY_ALGEBRA_ALGORITHMS_HPP_

#include <iostream>

using namespace std;

struct gcd_decomposition {long gcd; long factor_left; long factor_right;} typedef gcd_decomposition;

long euklid(long a, long b);

struct gcd_decomposition extended_euklid(long a, long b);

#endif
