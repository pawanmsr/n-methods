#include <combinatorics.hpp>

#include <algorithm>
#include <cassert>

namespace nm {
    template<typename T>
    bool next_permutation(std::vector<T>& permutation) {
        const std::int32_t n = permutation.size();

        std::int32_t i = n - 1;
        while (i > 0 and permutation[i - 1] >= permutation[i])
            i--;
        
        if (i > 0) {
            std::int32_t j = i - 1;
            std::int32_t k = n - 1;
            while (k > i and permutation[k] <= permutation[j])
                k--;

            std::swap(permutation[j], permutation[k]);
        }

        std::reverse(permutation.begin() + i, permutation.end());
        return i > 0;
    }
    
    template<typename T>
    PnC<T>::PnC(std::int32_t n, T mod_prime) : mod(mod_prime), Arithmetic<T>::Arithmetic(mod_prime) {
        this->factorial.resize(n + 1, 1);
        this->factorial_inverse.resize(n + 1, 1);

        for (std::int32_t i = 1; i <= n; i++) {
            this->factorial[i] = this->multiply(this->factorial[i - 1], i);
            this->factorial_inverse[i] =
                prime_modular_multiplicative_inverse<T>(factorial[i], mod);
        }
    }

    template<typename T>
    T PnC<T>::get_factorial(std::int32_t n) {
        assert(n < this->factorial.size());
        return this->factorial[n];
    }

    template<typename T>
    T PnC<T>::get_factorial_inverse(std::int32_t n) {
        assert(n < this->factorial_inverse.size());
        return this->factorial_inverse[n];
    }

    template<typename T>
    T PnC<T>::nPr(std::int32_t n, std::int32_t r) {
        assert(n >= r);
        assert(n < this->factorial.size());
        
        return this->multiply(this->factorial[n], this->factorial_inverse[n]);
    }

    template<typename T>
    T PnC<T>::nCr(std::int32_t n, std::int32_t r) {
        assert(n >= r);
        assert(n < this->factorial.size());
        
        return this->multiply(this->multiply(this->factorial[n],
            this->factorial_inverse[r]), this->factorial_inverse[n - r]);
    }
} // permutation and combination

template bool nm::next_permutation<int>(std::vector<int>&);
template class nm::PnC<int>;
template class nm::PnC<long long>;
