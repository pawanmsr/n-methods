#include <primes.hpp>

/* T is expected to be any unsigned or equivalent integer data type */
template<typename T>
std::vector<T> eratosthenes_sieve(T n) {
    std::vector<bool> is_prime(n + 1, true);
    for (size_t i = 2; i <= n; i++) {
        if (!is_prime[i]) continue;
        
        for (int j = i * i; j <= n; j += i)
            is_prime[j] = false;
    }
    
    std::vector<T> primes;
    for (size_t i = 2; i <= n; i++)
        if (is_prime[i])
            primes.push_back(i);
    
    return primes
}
