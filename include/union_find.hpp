#if !defined(UNION_FIND)
#define UNION_FIND

#include <vector>

namespace nm
{
    // T is signed data type
    template <typename T>
    class UnionFind
    {
    private:
        bool one;
        std::size_t n;
        std::vector<T> parent;
    
    public:
        UnionFind(T number_of_elements, bool one_indexed = false);
        T find(T x);
        T unite(T x, T y);
        bool united(T x, T y);
        std::size_t size(T x);
        ~UnionFind();
    };
} // namespace nm

#endif // Union Find
