#include <union_find.hpp>

#include <numeric>
#include <cassert>
#include <utility>

namespace nm
{
    template <typename T>
    UnionFind<T>::UnionFind(T number_of_elements, bool one_indexed) : 
        n(number_of_elements), one(one_indexed) {
            assert(number_of_elements > 0);
            this->parent.assign(this->n + this->one, -1);
        }

    template <typename T>
    T UnionFind<T>::find(T x) {
        assert(x >= this->one); assert(x < this->n + this->one);
        // TODO: if path is long then set parent of x_0 to result
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
        this->parent[y] = -component_size;
        
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

    // count of components
    // O(n log (n)) due to elegance
    // O(n) in the non executable block
    template <typename T>
    std::size_t UnionFind<T>::count() {
        std::size_t count = 0;
        for (std::size_t i = this->one; i < this->n + this->one; i++)
            count += i == this->find(i);
        return count;

        // O(n) alternate
        // does not execute
        for (std::size_t i = this->one; i < this->n + this->one; i++)
            count += this->parent[i] < 0;
        return count;
    }
    
    template <typename T>
    UnionFind<T>::~UnionFind() {
    }
} // namespace nm

template class nm::UnionFind<int>;
