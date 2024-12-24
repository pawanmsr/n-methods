#if !defined(MODULO_OPERATIONS)
#define MODULO_OPERATIONS

#include <cstdint>

namespace nm {
    template <typename T>
    T mod_bin_exp(T x, T y, const T m);
    
    template <typename T>
    T mod_bin_exp_iterative(T x, T y, const T m);

    template<typename T>
    T modular_multiplicative_inverse(T num, const T mod);

    template<typename T>
    T prime_modular_multiplicative_inverse_by_bin_exp(T num, const T mod);

    template<typename T>
    T prime_modular_multiplicative_inverse(T num, const T mod);
}


namespace nm {
    /*
     * Arithmetic
     * Divide requires multiplicative_inverse.
     * Raise requires exponentiation.
     * T is expected to be integer type.
     */
    template<typename T>
    class Arithmetic {
    private:
        T mod;
    public:
        Arithmetic(T mod_prime);
        T underflow(T x);
        T fix(T x);
        T add(T x, T y);
        T subtract(T x, T y);
        T multiply(T x, T y);
        T raise(T x, T y);
        T divide(T x, T y);
        ~Arithmetic();
    };
} // namespace nm

namespace nm {
    /*
     * Derived data type for simplified modular arithmetic.
     *
     * TODO: apply lower bound on M to 1
     * TODO: apply upper bound on M to Mersenne Prime
     * M \in (1, std::numeric_limits::max(int32_t))
     * OEIS-A0668: 2,147,483,647
     */
    template<std::size_t M>
    class int32_m {
        private:
            std::int64_t value;
            // value \in [0, M)
        public:
            int32_m();
            ~int32_m();

            // binary
            int32_m& operator+=(const int32_m<M> &x);
            int32_m& operator-=(const int32_m<M> &x);
            int32_m& operator*=(const int32_m<M> &x);
            int32_m& operator/=(const int32_m<M> &x);

            // unary
            int32_m& operator++();
            int32_m& operator--();
            int32_m operator++(int);
            int32_m operator--(int);
            // int in postfix is vestigial
    };
} // namespace nm


#endif // MODULO_OPERATIONS
