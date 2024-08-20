#include <combinatorics.hpp>

#include <modulo_operations.hpp>

#include <algorithm>

namespace nm
{
    template<typename T>
    bool next_permutation(std::vector<T>& permutation) {
        const size_t n = permutation.size();

        size_t i = n - 1;
        while (i > 0 and permutation[i - 1] >= permutation[i])
            i--;
        
        if (i > 0) {
            size_t j = i - 1;
            size_t k = n - 1;
            while (k > i and permutation[k] <= permutation[j])
                k--;

            std::swap(permutation[j], permutation[k]);
        }

        std::reverse(permutation.begin() + i, permutation.end());
        return i > 0;
    }
    
    template<typename T>
    PnC<T>::PnC(T n, T mod) {
        this->mod = mod;
        this->factorial.resize(n + 1, 1);
        this->factorial_inverse.resize(n + 1, 1);

        for (T i = 1; i <= n; i++) {
            this->factorial[i] = this->factorial[i - 1] * i;
            this->factorial[i] %= mod;

            this->factorial_inverse[i] =
                prime_modular_multiplicative_inverse<T>(factorial[i], mod);
            this->factorial_inverse[i] %= mod;
        }
    }

    template<typename T>
    T PnC<T>::get_factorial(T n) {
        // validate n

        return (this->factorial[n]);
    }

    template<typename T>
    T PnC<T>::nPr(T n, T r) {
        // validate n and r
        T p = (this->factorial[n] * this->factorial_inverse[n]) % this->mod;
        if (p < 0) p += this->mod;
        return p % this->mod;
    }

    template<typename T>
    T PnC<T>::nCr(T n, T r) {
        // validate n and r
        T c = (((this->factorial[n] * this->factorial_inverse[r]) % this->mod) * 
            this->factorial_inverse[n - r]) % this->mod;
        if (c < 0) c += this->mod;
        return c % this->mod;
    }
    
    template<typename T>
    PnC<T>::~PnC() {
        // delete this;
    }
} // namespace nm

template bool nm::next_permutation<int>(std::vector<int>&);
template class nm::PnC<int>;
