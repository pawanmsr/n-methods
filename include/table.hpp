#if !defined(TABLE)
#define TABLE

#include <vector>
#include <functional>

namespace nm {
    template<typename T>
    class Sparse {
        private:
            std::size_t k;
            std::size_t n;
            std::vector<vector<T> > table
            std::function<T(T, T)> operation;
        public:
            Sparse(const std::vector<T> &data, std::function<T(T, T)> &f);
            T query(std::size_t l, std::size_t r);
            ~Sparse();
    };
}

#endif