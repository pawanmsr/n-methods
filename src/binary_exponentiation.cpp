#include <binary_exponentiation.hpp>

namespace nm
{
    /* T is expected to be any integer data type */

    template <typename T>
    T bin_exp(T x, T y) {
        if (y<=0) return 1;
        
        T z = bin_exp(x, y/2);
        return y%2 ? z*z*x : z*z;
    }

    template <typename T>
    T mod_bin_exp(T x, T y, T m) {
        if (m<=1) return 0;
        if (y<=0) return 1;
        
        T z = mod_bin_exp(x, y/2, m);
        return y%2 ? (z*z % m)*x % m : z*z % m;
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

    template <typename T>
    T mod_bin_exp_iterative(T x, T y, T m) {
        if (y<=0) return 1;
        
        T res = 1;
        while (y) {
            if (y & 1) res = res*x % m;
            x = x*x % m;
            y >>= 1;
        }
        return res;
    }
} // namespace nm
