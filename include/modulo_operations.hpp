#if !defined(MODULO_OPERATIONS)
#define MODULO_OPERATIONS

namespace nm
{
    template<typename T>
    T modular_multiplicative_inverse(T num, const T mod);

    template<typename T>
    T prime_modular_multiplicative_inverse_by_bin_exp(T num, const T mod);

    template<typename T>
    T prime_modular_multiplicative_inverse(T num, const T mod);

    template<typename T>
    class Arithmetic
    {
    private:
        T mod;
    public:
        Arithmetic(T m);
        T add(T x, T y);
        T subtract(T x, T y);
        T multiply(T x, T y);
        T divide(T x, T y);
        ~Arithmetic();
    };
} // namespace nm


#endif // MODULO_OPERATIONS
