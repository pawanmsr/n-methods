#if !defined(TREES)
#define TREES

#include <vector>
#include <cstdint>

namespace nm
{
    /*
     * U is a pointer to object or struct.
     * U must contain an 'identity' element.
     * U must contain an 'assign' function
     *  which must have associative and commutative
     *  (and optionally distributive) properties.
     * U must contain an 'integrate' function
     *  to combine two separate parts of the tree.
     * See utility.hpp for sample integrators.
     */
    template <class T, class U>
    class SegmentTree
    {
    private:
        std::int32_t n;
        std::vector<T> tree;
        std::vector<T> auxiliary;
        U *integrator;

    protected:
        bool propagate(std::int32_t i);
        void construct(std::vector<T> &data,
            std::int32_t lo, std::int32_t hi, std::int32_t i);
        T query_tree(std::int32_t lo, std::int32_t hi,
            std::int32_t tlo, std::int32_t thi, std::int32_t i);
        T update_tree(T value, std::int32_t position,
            std::int32_t lo, std::int32_t hi, std::int32_t i);
        T update_tree(T value, std::int32_t lo, std::int32_t hi,
            std::int32_t tlo, std::int32_t thi, std::int32_t i);

    public:
        SegmentTree(std::vector<T> &data, U *integrator_struct = new U());
        T query(std::int32_t left, std::int32_t right);
        T update(T value, std::int32_t position);
        T update(T value, std::int32_t left, std::int32_t right);
        ~SegmentTree();
    };


    template <class C>
    class SearchTree {
    private:
        // define storage type
    public:
        SearchTree();
        ~SearchTree();
    };

    // Reference: ACP Volume 2
    template <class C>
    class AVL : protected SearchTree {
    private:
        // positive / true or 
        // negative / false to specify
        // direction of lean for the tree
        bool balance_factor;
    public:
        AVL();
        void insert();
        void remove();
        void search();
        ~AVL();
    };
} // namespace nm

#endif // SEGMENT_TREE
