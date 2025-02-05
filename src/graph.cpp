#include <graph.hpp>

#include <numeric>
#include <cassert>
#include <utility>

namespace nm {
    UnionFind::UnionFind(std::size_t number_of_elements, bool one_indexed) : 
        one(one_indexed), n(number_of_elements) {
            assert(number_of_elements > 0);
            this->parent.assign(this->n + this->one, -1);
        }

    std::size_t UnionFind::find(std::size_t x) {
        assert(x >= this->one); assert(x < this->n + this->one);
        // TODO: if path is long then set parent of x_0 to result
        while (this->parent[x] >= this->one)
            x = this->parent[x];
        return x;
    }
    
    std::size_t UnionFind::unite(std::size_t x, std::size_t y) {
        x = this->find(x);
        y = this->find(y);
        
        if (x == y) return x;
        
        std::size_t size_of_x = this->size(x);
        std::size_t size_of_y = this->size(y);
        std::size_t component_size = size_of_x + size_of_y;
        if (size_of_x > size_of_y) std::swap(x, y);
        
        this->parent[x] = y;
        this->parent[y] = -component_size;
        
        return y;
    }

    bool UnionFind::united(std::size_t x, std::size_t y) {
        return this->find(x) == this->find(y);
    }

    std::size_t UnionFind::size(std::size_t x) {
        x = this->find(x);
        return -this->parent[x];
    }

    // count of components
    // O(n log (n)) due to elegance
    // O(n) in the non executable block
    std::size_t UnionFind::count() {
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
} // namespace nm
