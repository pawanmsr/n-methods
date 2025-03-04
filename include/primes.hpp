#if !defined(PRIMES)
#define PRIMES

#include <vector>

namespace nm {
    template<typename T>
    std::vector<T> eratosthenes_sieve(const T n);
} // primes

namespace nm {
    std::uint32_t RAMANUJAN_NUMBER = 1729;
    std::uint32_t SMALLEST_PERFECT = 6;
    std::uint32_t SMALLEST_HAPPY = 7;
    
    bool fermat(std::uint64_t number, std::uint32_t iterations = SMALLEST_HAPPY);
} // primality tests

#endif // PRIMES
