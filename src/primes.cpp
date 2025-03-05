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
    bool fermat(std::uint64_t number, std::uint32_t iterations) {
        assert(iterations > 0);
        
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
     */

    /*
     * Agarwal-Kayal-Saxena
     * http://www.cse.iitk.ac.in/users/manindra/algebra/primality_v6.pdf
     */
} // primality

