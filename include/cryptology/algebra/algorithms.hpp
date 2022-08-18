#ifndef CRYPTOLOGY_ALGEBRA_ALGORITHMS_HPP_
#define CRYPTOLOGY_ALGEBRA_ALGORITHMS_HPP_

#include <iostream>

using namespace std;

int mod(int i, int n);

long mod(long i, long n);

struct gcd_decomposition {long gcd; long factor_left; long factor_right;} typedef gcd_decomposition;

bool is_invertible(long a, long m);

long inverse(long a, long m);

long euklid(long a, long b);

struct gcd_decomposition extended_euklid(long a, long b);

#endif
