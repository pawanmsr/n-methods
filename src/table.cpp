#include <table.hpp>

namespace nm {
    template<typename T>
    Sparse<T>::Sparse(const std::vector<T> &data, std::function<T(T, T)> &f) {
        this->operation = f;
        
        this->k = 1;
        this->n = 1;
        const std::size_t m = data.size();
        while (this->n < m) {
            this->k += 1;
            this->n *= 2LL;
        }

        this->table.resize(this->k + 1, std::vector<T>(this->n));
        this->table[0].assign(data.begin(), data.end());

        for (std::size_t i = 1; i <= this->k; i++) {
            for (std::size_t j = 0; j + (1 << i) <= this->n; j++) {
                this->table[i][j] = this->operation(this->table[i - 1][j],
                    this->table[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    
    template<typename T>
    Sparse<T>::~Sparse() {}
}
