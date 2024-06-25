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
} // namespace nm


#endif // MODULO_OPERATIONS
