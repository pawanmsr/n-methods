#include <primes.hpp>

#include <exponentiation.hpp>
#include <random.hpp>

#include <cassert>

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

template std::vector<int> nm::eratosthenes_sieve<int>(int);
template std::vector<long> nm::eratosthenes_sieve<long>(long);
template std::vector<long long> nm::eratosthenes_sieve<long long>(long long);
template std::vector<unsigned int> nm::eratosthenes_sieve<unsigned int>(unsigned int);
template std::vector<unsigned long> nm::eratosthenes_sieve<unsigned long>(unsigned long);

namespace nm {

    Primality::Primality(std::uint32_t iterations) : i(iterations) {
        if (i == 0) i = SMALLEST_PERFECT;
    };
    
    bool Primality::fermat(std::uint64_t number) {
        std::uint32_t iterations = this->i;

        Random random;
        while (iterations--) {
            std::uint32_t x = random.number(2, number - 1);
            if (mod_bin_exp_iterative<std::uint32_t>(x, number - 1, number) != 1)
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

        // implementation
    }

    /*
     * Solovay–Strassen
     */
    bool Primality::solovay_strassen(std::uint64_t number) {
        std::uint32_t iterations = this->i;

        // implementation
    }

    /*
     * Agarwal-Kayal-Saxena
     * http://www.cse.iitk.ac.in/users/manindra/algebra/primality_v6.pdf
     */
    bool agarwal_kayal_saxena(std::uint64_t number) {
        // TODO: non-generic practical implementation
    }
} // primality

