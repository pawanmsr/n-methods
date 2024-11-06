#if !defined(TREES)
#define TREES

#include <utility.hpp>

#include <vector>
#include <cstdint>
#include <functional>

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

    
    /*
     * Reference: TAOCP Volume 3
     * 6.2.2 : MIXAL -> C++
     * class C is of type Node
     *  as defined in utility.hpp.
     */
    template <class C, class T, class U>
    class SearchTree {
    private:
        C* root;
        std::size_t tree_size; // TODO: not needed.
        std::function<bool(T&, T&)> compare;
    
    protected:
        C* create(T x);
        C* successor(C* n, bool return_parent = false);
        C* predecessor(C* n, bool return_parent = false);
        C* node(T x, bool return_parent = false, bool mark = false);
        void preorder(C* n, std::vector<T> &keys);
    
    public:
        SearchTree(std::function<bool(T&, T&)> compare = default_compare<T>);
        
        U insert(T x, U y); // map-like
        void insert(T x); // set-like
        
        bool remove(T x);
        bool search(T x);
        
        U obtain(T x);
        
        ~SearchTree();
        
        U & operator [](T x);
        const U & operator [](T x) const;

        std::vector<T> keys();

        std::size_t size();
    };

    /*
     * Reference: TAOCP Volume 3
     * 6.2.3 : MIXAL -> C++
     * Alternate: libdict/hb_tree
     * 
     * Fibonacci tree of order h + 1
     *  has height h, and lowest possible
     *  number of nodes.
     * N > (\frac{\phi^{h + 2}}{\sqrt{5}} - 1) - 1
     *  where \phi is the golden ratio.
     * Rounding \frac{\phi^{h + 1}}{\sqrt{5}}
     *  to nearest integer gives fibonacci h + 1
     *  of height h.
     */
    template <class C, class T, class U>
    class AVL : protected SearchTree<C, T, U> {
    private:
        // expected height of right subtree
        // minus the height of left subtree
        std::int16_t balance_factor;
        // balance factor is one of [-1, 0, 1]
    protected:
        C* rotate_left(C* n);
        C* rotate_right(C* n);
        C* balance(C* n);
    public:
        AVL(std::function<bool(T&, T&)> compare = default_compare<T>,
            std::int16_t balance_factor = 0);
        void insert(T x, U y);
        void insert(T x);
        bool remove(T x);
        bool search(T x);
        ~AVL();

        U & operator [](T x);
        const U & operator [](T x) const;
    };
} // namespace nm

#endif // TREES
