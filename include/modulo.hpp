#if !defined(MODULO_OPERATIONS)
#define MODULO_OPERATIONS

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
    // FIXME: arithmetic is faulty
    // TODO: add operators
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


#endif // MODULO_OPERATIONS
