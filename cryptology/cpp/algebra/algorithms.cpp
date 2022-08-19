#include <iostream>
#include <cryptology/algebra/algorithms.hpp>
#include <cryptology/algebra/matrix.hpp>

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
