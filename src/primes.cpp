#include <primes.hpp>

#include <exponentiation.hpp>
#include <random.hpp>

#include <cassert>
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
     */
    bool Primality::miller_rabin(std::uint64_t number) {
        std::uint32_t iterations = this->i;

        std::uint64_t r = 0;
        std::uint64_t d = number - 1;
        while (not (d % 2LL)) {
            d /= 2LL;
            r++;
        }

        std::function<bool(std::uint64_t)> composite = [&] (std::uint64_t a) -> bool {
            std::uint64_t b = mod_bin_exp_iterative<std::int64_t>(a, d, number);
            if (b == 1 or b == number - 1) return false;

            for (std::int64_t j = 1; j < r; j++) {
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
    bool Primality::solovay_strassen(std::uint64_t number) {
        std::uint32_t iterations = this->i;

        // implementation
        return false;
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

