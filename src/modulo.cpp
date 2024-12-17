#include <modulo.hpp>

#include <gcd.hpp>
#include <exponentiation.hpp>

#include <limits>

// Modular Binary Exponentiation
namespace nm {
    template <typename T>
    T mod_bin_exp(T x, T y, const T m) {
        if (m<=1) return 0;
        if (y<=0) return 1;
        
        T z = mod_bin_exp<T>(x, y/2, m);
        return y%2 ? (z*z % m)*x % m : z*z % m;
    }

    template <typename T>
    T mod_bin_exp_iterative(T x, T y, const T m) {
        if (y<=0) return 1;
        
        T res = 1;
        while (y) {
            if (y & 1) res = res*x % m;
            x = x*x % m;
            y >>= 1;
        }
        return res;
    }
}


template int nm::mod_bin_exp<int>(int, int, int);
template long nm::mod_bin_exp<long>(long, long, long);
template long long nm::mod_bin_exp<long long>(long long, long long, long long);

template int nm::mod_bin_exp_iterative<int>(int, int, int);
template long nm::mod_bin_exp_iterative<long>(long, long, long);
template long long nm::mod_bin_exp_iterative<long long>(long long, long long, long long);

namespace nm
{
    // T is expected to be signed integer type.
    // mod is a prime number.
    template<typename T>
    T modular_multiplicative_inverse(T num, const T mod) {
        T x, y;
        if (extended_gcd<T>(num, mod, x, y) != 1) return -1;

        // (num * x + mod * y = 1) % mod
        // num * x = 1 % mod
        return (x % mod + mod) % mod;
    }

    // mod is a prime number.
    template<typename T>
    T prime_modular_multiplicative_inverse_by_bin_exp(T num, const T mod) {
        return mod_bin_exp_iterative<T>(num, mod - 2, mod);
        // mod is prime => phi-function(mod) = mod - 1
        // phi-function counts number of coprimes to its argument
        // that are less than the argument a.k.a. Euler Totient Function.
    }

    // num is non-negative integer.
    // mod is a prime number.
    template<typename T>
    T prime_modular_multiplicative_inverse(T num, const T mod) {
        num %= mod;
        
        // mod is prime => gcd(num, mod) is 1
        return num < 2 ? num : mod - (long long)(mod / num) *
            prime_modular_multiplicative_inverse<T>(mod % num, mod) % mod;
    }
} // namespace nm

template long long nm::modular_multiplicative_inverse<long long>(long long, const long long);
template long long nm::prime_modular_multiplicative_inverse_by_bin_exp<long long>(long long, const long long);
template long long nm::prime_modular_multiplicative_inverse<long long>(long long, const long long);

template int nm::modular_multiplicative_inverse<int>(int, const int);
template int nm::prime_modular_multiplicative_inverse_by_bin_exp<int>(int, const int);
template int nm::prime_modular_multiplicative_inverse<int>(int, const int);

// Modular Arithmetic //
namespace nm {
    template<typename T>
    Arithmetic<T>::Arithmetic(T mod_prime) : mod(mod_prime) {}

    template<typename T>
    T Arithmetic<T>::underflow(T x) {
        if (x >= 0) return x % this->mod;
        return (std::numeric_limits<T>::max() % this->mod +
            (x - std::numeric_limits<T>::min() + 1)) % this->mod;
    }

    template<typename T>
    T Arithmetic<T>::fix(T x) {
        if (x >= 0) return x % this->mod;
        return (this->mod + x) % this->mod;
    }

    // x and y are expected to be non negative integers.
    template<typename T>
    T Arithmetic<T>::add(T x, T y) {
        return this->fix((x + y) % this->mod);
    }

    // x and y are expected to be non negative integers
    template<typename T>
    T Arithmetic<T>::subtract(T x, T y) {
        return this->fix((x - y) % this->mod);
    }

    // multiply is log(y) operation
    template<typename T>
    T Arithmetic<T>::multiply(T x, T y) {
        if (y == 0) return 0;
        
        T z = 0;
        while (y) {
            if (y & 1) z = (z + x) % this->mod;
            x = 2 * x % this->mod;
            y >>= 1;
        }

        return z;
    }

    // Raise requires exponentiation.
    template<typename T>
    T Arithmetic<T>::raise(T x, T y) {
        return mod_bin_exp_iterative<T>(x, y, this->mod);
    }

    // Divide requires multiplicative_inverse.
    template<typename T>
    T Arithmetic<T>::divide(T x, T y) {
        return this->multiply(x, prime_modular_multiplicative_inverse<T>(y, this->mod));
    }

    template<typename T>
    Arithmetic<T>::~Arithmetic() {
        // delete this;
    }
}

template class nm::Arithmetic<int>;
template class nm::Arithmetic<long long>;
