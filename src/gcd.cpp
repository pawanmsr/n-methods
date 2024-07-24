#include <gcd.hpp>

#include<algorithm>

namespace nm
{
    /* T is expected to be any integer data type */
    /* time complexity O(log min (a, b)) */
    template <typename T>
    T gcd(T a, T b) {
        return b ? gcd<T>(b, a % b) : a;
    }

    template <typename T>
    T gcd_iterative(T a, T b) {
        while (b) {
            a %= b;
            std::swap(a, b);
        }
        return a;
    }
} // namespace nm

template int nm::gcd<int>(int, int);
template long nm::gcd<long>(long, long);
template long long nm::gcd<long long>(long long, long long);

template int nm::gcd_iterative<int>(int, int);
template long nm::gcd_iterative<long>(long, long);
template long long nm::gcd_iterative<long long>(long long, long long);
