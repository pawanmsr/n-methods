#include <exponentiation.hpp>

#include <cstdint>

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
} // binary exponentiation

template std::int32_t nm::bin_exp<std::int32_t>(std::int32_t, std::int32_t);
template std::int64_t nm::bin_exp<std::int64_t>(std::int64_t, std::int64_t);

template std::int32_t nm::bin_exp_iterative<std::int32_t>(std::int32_t, std::int32_t);
template std::int64_t nm::bin_exp_iterative<std::int64_t>(std::int64_t, std::int64_t);
