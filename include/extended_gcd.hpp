#if !defined(EXTENDED_GCD)
#define EXTENDED_GCD

template <typename T>
T extended_gcd(T a, T b, T& x, T& y);

template <typename T>
T extended_gcd_iterative(T a, T b, T& x, T& y);

#endif // EXTENDED_GCD