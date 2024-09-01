#include <combinatorics.hpp>

#include <modulo_operations.hpp>

#include <algorithm>
#include <cassert>

namespace nm
{
    template<typename T>
    bool next_permutation(std::vector<T>& permutation) {
        const std::size_t n = permutation.size();

        std::size_t i = n - 1;
        while (i > 0 and permutation[i - 1] >= permutation[i])
            i--;
        
        if (i > 0) {
            std::size_t j = i - 1;
            std::size_t k = n - 1;
            while (k > i and permutation[k] <= permutation[j])
                k--;

            std::swap(permutation[j], permutation[k]);
        }

        std::reverse(permutation.begin() + i, permutation.end());
        return i > 0;
    }
    
    template<typename T>
    PnC<T>::PnC(std::size_t n, T mod_prime) {
        this->mod = mod_prime;
        this->factorial.resize(n + 1, 1);
        this->factorial_inverse.resize(n + 1, 1);

        for (std::size_t i = 1; i <= n; i++) {
            this->factorial[i] = this->factorial[i - 1] * i;
            this->factorial[i] %= mod;

            this->factorial_inverse[i] =
                prime_modular_multiplicative_inverse<T>(factorial[i], mod);
            this->factorial_inverse[i] %= mod;
        }
    }

    template<typename T>
    T PnC<T>::get_factorial(std::size_t n) {
        assert(n < this->factorial.size());
        return this->factorial[n];
    }

    template<typename T>
    T PnC<T>::get_factorial_inverse(std::size_t n) {
        assert(n < this->factorial_inverse.size());
        return this->factorial_inverse[n];
    }

    template<typename T>
    T PnC<T>::nPr(std::size_t n, std::size_t r) {
        assert(n >= r);
        assert(n < this->factorial.size());
        
        T p = (this->factorial[n] * this->factorial_inverse[n]) % this->mod;
        if (p < 0) p += this->mod;
        return p % this->mod;
    }

    template<typename T>
    T PnC<T>::nCr(std::size_t n, std::size_t r) {
        assert(n >= r);
        assert(n < this->factorial.size());
        
        T c = (((this->factorial[n] * this->factorial_inverse[r]) % this->mod) * 
            this->factorial_inverse[n - r]) % this->mod;
        if (c < 0) c += this->mod;
        return c % this->mod;
    }
    
    template<typename T>
    PnC<T>::~PnC() {
        this->factorial.clear();
        this->factorial_inverse.clear();
        
        // delete this;
    }
} // namespace nm

template bool nm::next_permutation<int>(std::vector<int>&);
template class nm::PnC<int>;
template class nm::PnC<long long>;
