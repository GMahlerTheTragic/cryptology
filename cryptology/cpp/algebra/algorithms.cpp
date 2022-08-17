#include <iostream>
#include <cryptology/algebra/algorithms.hpp>

using namespace std;

long euklid(long a, long b) {
    if (a < b) {
        long temp = a;
        a = b;
        b = temp;
    }
    long r;
    do {
        r = a % b;
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
        r = a % b;
        a = b;
        b = r;
    } while (r != 0);

    result.gcd = a;
    *larger_p = p1;
    *smaller_p = q1;
    return result;
}
