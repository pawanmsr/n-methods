#include <union_find.hpp>

#include <numeric>
#include <cassert>
#include <utility>

namespace nm
{
    template <typename T>
    UnionFind<T>::UnionFind(T number_of_elements) : n(number_of_elements) {
        assert(number_of_elements > 0);
        this->parent.assign(this->n + 1, -1);
    }

    template <typename T>
    T UnionFind<T>::find(T x) {
        assert(x > 0); assert(x <= this->n);
        while (this->parent[x] > 0)
            x = this->parent[x];
        return x;
    }
    
    template <typename T>
    T UnionFind<T>::unite(T x, T y) {
        x = this->find(x);
        y = this->find(y);
        if (x == y) return x;
        
        T size_of_x = this->size(x);
        T size_of_y = this->size(y);
        T component_size = size_of_x + size_of_y;
        if (size_of_x > size_of_y) std::swap(x, y);
        
        this->parent[x] = y;
        this->parent[y] = -(size_of_x + size_of_y);
        return y;
    }

    template <typename T>
    bool UnionFind<T>::united(T x, T y) {
        return this->find(x) == this->find(y);
    }

    template <typename T>
    std::size_t UnionFind<T>::size(T x) {
        x = this->find(x);
        return -this->parent[x];
    }
    
    template <typename T>
    UnionFind<T>::~UnionFind() {
    }
} // namespace nm

template class nm::UnionFind<int>;
