#include <primes.hpp>

#include <exponentiation.hpp>

#include <cassert>
#include <utility>
#include <functional>

namespace nm {
    /* T is expected to be any unsigned or equivalent integer data type */
    template<typename T>
    std::vector<T> eratosthenes_sieve(const T n) {
        std::vector<bool> is_prime(n + 1, true);
        for (std::size_t i = 2; i <= n; i++) {
            if (not is_prime[i]) continue;
            
            for (std::size_t j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
        
        std::vector<T> primes;
        for (std::size_t i = 2; i <= n; i++)
            if (is_prime[i])
                primes.push_back(i);
        
        return primes;
    }

} // sieve

template std::vector<std::size_t> nm::eratosthenes_sieve<std::size_t>(std::size_t);
template std::vector<std::int32_t> nm::eratosthenes_sieve<std::int32_t>(std::int32_t);
template std::vector<std::int64_t> nm::eratosthenes_sieve<std::int64_t>(std::int64_t);

namespace nm {
    Primality::Primality(std::uint32_t iterations) : i(iterations) {
        if (i == 0) i = SMALLEST_PERFECT;
    }
    
    bool Primality::fermat(std::uint64_t number) {
        std::uint32_t iterations = this->i;

        Random random;
        while (iterations--) {
            std::uint64_t x = random.number(2LL, number - 1LL);
            if (mod_bin_exp_iterative<std::int64_t>(x, number - 1, number) != 1)
                return false;
        }
        
        return true;
    }

    /*
     * Miller-Rabin
     * Test for non-compositeness.
     * Number must fit in 32 bit unsigned integer.
     */
    bool Primality::miller_rabin(std::uint32_t number) {
        if (number < 2) return 0;
        if (number < 4) return 1;
        
        std::uint32_t iterations = this->i;

        std::uint64_t r = 0;
        std::uint64_t d = number - 1;
        while (not (d % 2)) {
            d /= 2;
            r++;
        }

        std::function<bool(std::uint64_t)> composite = [&] (std::uint64_t a) -> bool {
            std::uint64_t b = mod_bin_exp_iterative<std::int64_t>(a, d, number);
            if (b == 1 or b == number - 1) return false;

            for (std::int64_t j = 0; j < r; j++) {
                b = b * b % number;
                if (b == number - 1)
                    return false;
            }

            return true;
        };

        while (iterations--) {
            std::uint64_t a = this->random.number(2, number - 2);
            if (composite(a)) return false;
        }

        return true;
    }

    /*
     * Solovay–Strassen
     */
    bool Primality::solovay_strassen(std::uint32_t number) {
        std::uint32_t iterations = this->i;

        std::function<std::uint64_t(std::uint64_t, std::uint64_t)> legendre_jacobi = 
            [&] (std::uint64_t p, std::uint64_t q) -> std::int32_t {
                if (p == 0) return 0;
                if (p == 1) return 1;
                
                if (q & 1) return 0;

                std::int64_t r, j = 1;
                const std::int64_t Q = 4;

                while (p) {
                    while (not (p & 1)) {
                        p >>= 1;
                        r = q % (2 * Q);
                        if (r == Q - 1 or r == Q + 1)
                            j = -j;
                    }

                    std::swap(p, q);

                    if (p % Q == Q - 1 and q % Q == Q - 1)
                        j = -j;
                    
                    p %= q;
                }

                if (not q) return 0;
                return (j + number) % number;
            };
        
        while (iterations--) {
            std::uint64_t a = this->random.number(2, number - 2);
            std::uint64_t b = legendre_jacobi(a, number);

            if (b == 0 or mod_bin_exp_iterative<std::int64_t>(a, 
                (number - 1) / 2, number) != b) return false;
        }

        return true;
    }

    /*
     * Agarwal-Kayal-Saxena
     * http://www.cse.iitk.ac.in/users/manindra/algebra/primality_v6.pdf
     */
    bool agarwal_kayal_saxena(std::uint64_t number) {
        // TODO: non-generic practical implementation
        return false;
    }
} // primality

