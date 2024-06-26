#if !defined(PRIMES)
#define PRIMES

#include <vector>

namespace nm {
    template<typename T>
    std::vector<T> eratosthenes_sieve(const T n);
} // namespace nm

#endif // PRIMES
