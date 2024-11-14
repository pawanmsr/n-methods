#include <modulo.hpp>

#include <gcd.hpp>
#include <exponentiation.hpp>

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

    template<typename T>
    Arithmetic<T>::Arithmetic(T mod_prime) : mod(mod_prime) {}

    template<typename T>
    T Arithmetic<T>::rem(T x) {
        T z = x % this->mod;
        if (z >= this->mod) z -= this->mod;
        if (z < 0) z += this->mod;
        return z;
    }

    template<typename T>
    T Arithmetic<T>::add(T x, T y) {
        T z = this->rem(x) + this->rem(y);
        if (z >= this->mod) z -= this->mod;
        return z;
    }

    template<typename T>
    T Arithmetic<T>::subtract(T x, T y) {
        T z = this->rem(x) - this->rem(y);
        if (z < 0) z += this->mod;
        return z;
    }

    template<typename T>
    T Arithmetic<T>::multiply(T x, T y) {
        T z = this->rem(x) * this->rem(y) % this->mod;
        if (z < 0) z += this->mod;
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
        T z = this->rem(x) * prime_modular_multiplicative_inverse<T>(y, this->mod);
        return z % this->mod;
    }

    template<typename T>
    Arithmetic<T>::~Arithmetic() {
        // delete this;
    }
} // namespace nm

template long long nm::modular_multiplicative_inverse<long long>(long long, const long long);
template long long nm::prime_modular_multiplicative_inverse_by_bin_exp<long long>(long long, const long long);
template long long nm::prime_modular_multiplicative_inverse<long long>(long long, const long long);

template int nm::modular_multiplicative_inverse<int>(int, const int);
template int nm::prime_modular_multiplicative_inverse_by_bin_exp<int>(int, const int);
template int nm::prime_modular_multiplicative_inverse<int>(int, const int);

template class nm::Arithmetic<int>;
template class nm::Arithmetic<long long>;
