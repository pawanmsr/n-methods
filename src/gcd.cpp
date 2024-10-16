#include <gcd.hpp>

#include <tuple>
#include<utility>

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

    /* T is expected to be any unsigned integer data type */
    /* time complexity O(log min (a, b)) */
    /* num * x + mod * y = 1 */
    template <typename T>
    T extended_gcd(T a, T b, T& x, T& y) {
        if (!b) {
            x = 1;
            y = 0;
            return a;
        }

        T x1, y1;
        T g = extended_gcd<T>(b, a % b, x1, y1);

        x = y1;
        y = x1 - y1 * (a / b);

        return g;
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
            
            std::tie(x, x1) = std::make_tuple(x1, x - q * x1);
            std::tie(y, y1) = std::make_tuple(y1, y - q * y1);
            std::tie(a1, b1) = std::make_tuple(b1, a1 - q * b1);
        }
        
        return a1;
    }
} // namespace nm

template int nm::gcd<int>(int, int);
template long nm::gcd<long>(long, long);
template long long nm::gcd<long long>(long long, long long);

template int nm::gcd_iterative<int>(int, int);
template long nm::gcd_iterative<long>(long, long);
template long long nm::gcd_iterative<long long>(long long, long long);

template int nm::extended_gcd<int>(int, int, int&, int&);
template long nm::extended_gcd<long>(long, long, long&, long&);
template long long nm::extended_gcd<long long>(long long, long long, long long&, long long&);

template int nm::extended_gcd_iterative<int>(int, int, int&, int&);
template long nm::extended_gcd_iterative<long>(long, long, long&, long&);
template long long nm::extended_gcd_iterative<long long>(long long, long long, long long&, long long&);
