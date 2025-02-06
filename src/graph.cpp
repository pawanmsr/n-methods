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
} // union find

namespace nm {
    TwoSat::TwoSat(std::size_t number_of_variables) : n(number_of_variables) {
        this->used.resize(2 * this->n, false);
        
        this->assignment.resize(this->n);
        this->order.reserve(2 * this->n);
        
        this->component.resize(2 * this->n, -1);
        
        this->adjacency_forward.resize(2 * this->n);
        this->adjacency_backward.resize(2 * this->n);
    }

    void TwoSat::dfs_forward(std::size_t u) {
        this->used[u] = true;
        for (std::size_t v : this->adjacency_forward[u]) {
            if (this->used[v]) continue;
            this->dfs_forward(v);
        }

        this->order.push_back(u);
    }

    void TwoSat::dfs_backward(std::size_t u, const std::int32_t c) {
        this->component[u] = c;
        for (std::size_t v : this->adjacency_backward[u]) {
            if (this->component[v] >= 0) continue;
            this->dfs_backward(v, c);
        }
    }

    bool TwoSat::satisfiable() {
        this->order.clear();
        this->used.assign(2 * this->n, false);

        for (std::size_t u = 0; u < 2 * this->n; u++) {
            if (this->used[u]) continue;
            this->dfs_forward(u);
        }
        
        std::int32_t c = 0;
        this->component.assign(2 * this->n, -1);
        for (std::size_t i = 0; i < 2 * this->n; i++) {
            std::size_t u = this->order[2 * this->n - i - 1];
            if (this->component[u] >= 0) continue;
            this->dfs_backward(u, c++);
        }

        this->assignment.assign(this->n, false);
        for (std::size_t i = 0; i < 2 * this->n; i+=2) {
            if (this->component[i] == this->component[i + 1]) return false;
            this->assignment[i / 2] = this->component[i] > this->component[i + 1];
        }

        return true;
    }

    void TwoSat::add_clause(std::size_t a, bool negate_a, std::size_t b, bool negate_b) {
        a = 2 * a + negate_a;
        b = 2 * b + negate_b;
        
        std::size_t a_prime = a ^ 1;
        std::size_t b_prime = b ^ 1;

        this->adjacency_forward[a_prime].push_back(b);
        this->adjacency_forward[b_prime].push_back(a);

        this->adjacency_backward[b].push_back(a_prime);
        this->adjacency_backward[a].push_back(b_prime);
    }
} // two sat
