#if !defined(GCD)
#define GCD

namespace nm {
    template <typename T>
    T gcd(T a, T b);

    template <typename T>
    T gcd_iterative(T a, T b);

    template <typename T>
    T extended_gcd(T a, T b, T& x, T& y);

    template <typename T>
    T extended_gcd_iterative(T a, T b, T& x, T& y);
} // namespace nm

#endif // GCD
