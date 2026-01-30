#include <table.hpp>

#include <bit>
#include <cassert>

namespace nm {
    template<typename T>
    Sparse<T>::Sparse(const std::vector<T> &data, std::function<T(T, T)> &operation) :
        f(operation) {
        this->k = 1;
        this->n = 1;
        const std::size_t m = data.size();
        while (this->n < m) {
            this->k += 1;
            this->n *= 2LL;
        }

        this->table.resize(this->k + 1);
        this->table[0].assign(data.begin(), data.end());

        this->table[0].resize(this->n);
        for (std::size_t i = 1; i <= this->k; i++) {
            this->table[i].resize(this->n);
            
            for (std::size_t j = 0; j + (1 << i) <= this->n; j++) {
                this->table[i][j] = this->f(this->table[i - 1][j],
                    this->table[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    template<typename T>
    T Sparse<T>::query(std::int32_t l, std::int32_t r) {
        assert(l <= r); assert(l >= 0);
        // for non cumulative queries
        int i = std::bit_width(r - l + 1UL) - 1;
        return this->f(this->table[i][l], this->table[i][r - (1 << i) + 1]);
    }

    template<typename T>
    T Sparse<T>::cquery(std::int32_t l, std::int32_t r) {
        assert(l <= r); assert(l >= 0);
        // for cumulative queries
        T result = this->f(0, 0); // modify
        for (std::int32_t i = this->k; i >= 0; i--) {
            if ((1 << i) > r - l + 1) continue;
            
            result = this->f(result, this->table[i][l]);
            l += 1 << i;
        }
        
        return result;
    }
} // sparse table

template class nm::Sparse<int>;
