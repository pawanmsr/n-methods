#if !defined(EXTENDED_GCD)
#define EXTENDED_GCD

namespace nm
{
    template <typename T>
    T extended_gcd(T a, T b, T& x, T& y);

    template <typename T>
    T extended_gcd_iterative(T a, T b, T& x, T& y);
} // namespace nm

#endif // EXTENDED_GCD
