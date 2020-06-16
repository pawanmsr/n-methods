#include <iostream>
using namespace std;

/* T is expected to be any signed integer data type */
/* time complexity O(log min (a, b)) */

template <typename T>
T extended_gcd(T a, T b, T& x, T& y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }

    T x1, y1;
    T g = extended_gcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - y1 * (a / b);

    return d;
}

/* https://cp-algorithms.com/algebra/extended-euclid-algorithm.html */

template <typename T>
T extended_gcd_iterative(T a, T b, T& x, T& y) {
    x = 1;
    y = 0;

    T x1 = 0;
    T y1 = 1;
    T a1 = a;
    T b1 = b;

    while (b1) {
        T q = a1 / b1;
        
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    
    return a1;
}