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

#endif // Union Find
