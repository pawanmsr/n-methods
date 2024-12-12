#include <exponentiation.hpp>

namespace nm {
    /* T is expected to be any integer data type */
    template <typename T>
    T bin_exp(T x, T y) {
        if (y<=0) return 1;
        
        T z = bin_exp<T>(x, y/2);
        return y%2 ? z*z*x : z*z;
    }

    template <typename T>
    T bin_exp_iterative(T x, T y) {
        if (y<=0) return 1;
        
        T res = 1;
        while (y) {
            if (y & 1) res *= x;
            x = x*x;
            y >>= 1;
        }
        return res;
    }
} // namespace nm

template int nm::bin_exp<int>(int, int);
template long nm::bin_exp<long>(long, long);
template long long nm::bin_exp<long long>(long long, long long);

template int nm::bin_exp_iterative<int>(int, int);
template long nm::bin_exp_iterative<long>(long, long);
template long long nm::bin_exp_iterative<long long>(long long, long long);
