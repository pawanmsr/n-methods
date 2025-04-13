#if !defined(PRIMES)
#define PRIMES

#include <random.hpp>

#include <vector>
#include <cstdint>

namespace nm {
    template<typename T>
    std::vector<T> eratosthenes_sieve(const T n);
} // primes

namespace nm {
    const std::uint32_t RAMANUJAN_NUMBER = 1729; // smallest
    const std::uint32_t CARMICHAEL_NUMBER = 561; // smallest
    const std::uint32_t SMALLEST_PERFECT = 6;
    const std::uint32_t SMALLEST_HAPPY = 7;

    class Primality {
        private:
            std::uint32_t i;
            Random random;
        
        public:
            Primality(std::uint32_t iterations = SMALLEST_HAPPY);
            ~Primality() {};

            bool fermat(std::uint64_t number);
            bool miller_rabin(std::uint32_t number);
            bool solovay_strassen(std::uint32_t number);
            bool agarwal_kayal_saxena(std::uint64_t number);
    };
} // primality tests

#endif // PRIMES
