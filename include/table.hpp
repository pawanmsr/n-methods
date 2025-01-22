#if !defined(TABLE)
#define TABLE

#include <vector>
#include <functional>

namespace nm {
    /*
     * Operation(0, 0) must return
     *  identity element.
     */
    template<typename T>
    class Sparse {
        private:
            std::size_t k;
            std::size_t n;
            std::vector<std::vector<T> > table;
            std::function<T(T, T)> f;
        public:
            Sparse(const std::vector<T> &data, const std::function<T(T, T)> &operation);
            T query(std::size_t l, std::size_t r);
            ~Sparse();
    };
}

#endif
