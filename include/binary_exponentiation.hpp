#if !defined(BINARY_EXPONENTIATION)
#define BINARY_EXPONENTIATION

template <typename T>
T bin_exp(T x, T y);

template <typename T>
T mod_bin_exp(T x, T y, T m);

template <typename T>
T bin_exp_iterative(T x, T y);

template <typename T>
T mod_bin_exp_iterative(T x, T y, T m);

#endif // BINARY_EXPONENTIATION
