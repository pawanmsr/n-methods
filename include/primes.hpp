#if !defined(PRIMES)
#define PRIMES

#include <vector>

namespace nm {
    template<typename T>
    std::vector<T> eratosthenes_sieve(const T n);
} // primes

namespace nm {
    bool fermat(std::uint64_t number, std::uint32_t iterations);
} // primality tests

#endif // PRIMES
