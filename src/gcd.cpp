#include "gcd.hpp"

/* T is expected to be any integer data type */
/* time complexity O(log min (a, b)) */

template <typename T>
T gcd(T a, T b) {
    return b ? gcd(b, a % b) : a;
}

template <typename T>
T gcd_iterative(T a, T b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}
