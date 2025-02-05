#if !defined(GRAPH)
#define GRAPH

#include <vector>
#include <cstdint>

namespace nm {
    /*
     * Galler and Fischer
     * Generic implementation
     */
    class UnionFind {
        private:
            bool one;
            std::size_t n;
            std::vector<std::int32_t> parent;
        
        public:
            UnionFind(std::size_t number_of_elements, bool one_indexed = false);
            std::size_t find(std::size_t x);
            std::size_t unite(std::size_t x, std::size_t y);
            bool united(std::size_t x, std::size_t y);
            std::size_t size(std::size_t x);
            std::size_t count();
            ~UnionFind() {};
    };
} // union find

namespace nm {
    class TwoSat {
        private:
            bool solved;
            std::size_t n;
            std::vector<bool> used;
            std::vector<std::int32_t> order, component;
            std::vector<std::vector<std::size_t> > adjacency_forward;
            std::vector<std::vector<std::size_t> > adjacency_backward;

            void dfs_forward(std::size_t u);
            void dfs_backward(std::size_t u, std::size_t c);
        
        protected:
            std::vector<bool> assignment;

        public:
            TwoSat(std::size_t number_of_variables);
            bool satisfiable();
            void add_clause(std::size_t a, bool negate_a, std::size_t b, bool negate_b);
            ~TwoSat() {};
    };
} // two satisfiability


#endif // Union Find
