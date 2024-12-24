#if !defined(MODULO_OPERATIONS)
#define MODULO_OPERATIONS

#include <cstdint>
#include <compare>

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
     * 
     * M must be prime. TODO: add check.
     */
    template<std::size_t M>
    class Int32_M {
        private:
            std::int64_t value;
            // value \in [0, M)
        public:
            Int32_M();
            ~Int32_M();

            // type conversion
            virtual operator int() const noexcept;
            
            template<typename T>
            Int32_M(T x);

            static const std::size_t modulus = M;
            int32_t get_value() const noexcept;

            Int32_M<M> inverse() const;

            // direct initialization
            template<typename T>
            Int32_M<M>& operator=(const T &x);

            // binary
            Int32_M<M>& operator=(const Int32_M<M> &x);
            Int32_M<M>& operator+=(const Int32_M<M> &x);
            Int32_M<M>& operator-=(const Int32_M<M> &x);
            Int32_M<M>& operator*=(const Int32_M<M> &x);
            Int32_M<M>& operator/=(const Int32_M<M> &x);

            // unary
            Int32_M<M>& operator++();
            Int32_M<M>& operator--();
            Int32_M<M> operator++(int);
            Int32_M<M> operator--(int);
            // int in postfix is vestigial

            // comparision
            std::strong_ordering operator<=>(const Int32_M<M> &x) const noexcept;

            template<std::uint64_t T>
            friend std::strong_ordering operator<=>(const Int32_M<T> &x, const Int32_M<T> &y) noexcept;

            // constant binary
            template<std::uint64_t T>
            friend Int32_M<T> operator+(const Int32_M<T> &x, const Int32_M<T> &y);

            template<std::uint64_t T>
            friend Int32_M<T> operator-(const Int32_M<T> &x, const Int32_M<T> &y);

            template<std::uint64_t T>
            friend Int32_M<T> operator*(const Int32_M<T> &x, const Int32_M<T> &y);

            template<std::uint64_t T>
            friend Int32_M<T> operator/(const Int32_M<T> &x, const Int32_M<T> &y);
    };
} // namespace nm

using int32_m = nm::Int32_M<1000000007UL>;

#endif // MODULO_OPERATIONS
