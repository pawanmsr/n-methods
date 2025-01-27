#if !defined(TREES)
#define TREES

#include <utility.hpp>

#include <vector>
#include <cstdint>
#include <functional>

namespace nm {
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
    protected:
        C* root;
        std::function<bool(T&, T&)> compare;
        
        C* create(T x);
        C* rotate_left(C* n);
        C* rotate_right(C* n);
        
        C* successor(C* n, bool return_parent = false);
        C* predecessor(C* n, bool return_parent = false);
        C* node(T x, bool return_parent = false, bool mark = false) const;
        
        // traversal
        void inorder(C* n, std::vector<T> &keys);
        void preorder(C* n, std::vector<T> &keys);
        void postorder(C* n, std::vector<T> &keys);
        C* element(std::size_t k, C* n);
    
    public:
        SearchTree(std::function<bool(T&, T&)> compare = default_compare<T>);
        
        U insert(T x, U y); // map-like
        bool insert(T x); // set-like
        
        bool remove(T x);
        bool search(T x) const;
        
        U obtain(T x) const;
        
        ~SearchTree() {};
        
        U & operator [] (T x);

        // TODO: return info
        //  of k-th element
        U element(size_t k);

        std::vector<T> keys();

        std::size_t size() const noexcept;
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
     * 
     * class C is of type Node
     *  as defined in utility.hpp.
     */
    template <class C, class T, class U>
    class AVL : public SearchTree<C, T, U> {
    private:
        // expected height of right subtree
        // minus the height of left subtree
        std::int16_t balance_factor;
        // balance factor is one of {-1, 0, 1}
    protected:
        C* balance(C* n);
    public:
        AVL(std::function<bool(T&, T&)> compare = default_compare<T>,
            std::int16_t balance_factor = 0);
        U insert(T x, U y);
        bool insert(T x);
        bool remove(T x);
        ~AVL() {};

        U & operator [] (T x);
    };
} // namespace nm

namespace nm {
    template<typename T>
    class Fenwick {
        private:
            std::size_t n;
            std::vector<T> bit;
            std::function<T(T, T)> f;
        
        public:
            Fenwick(const std::size_t size, const std::function<T(T, T)> &operation);
            Fenwick(const std::vector<T> &data, const std::function<T(T, T)> &operation);

            T query(std::int32_t i);
            T query(std::int32_t l, std::int32_t r);

            void update(std::int32_t i, T data);

            ~Fenwick() {};
    };
} // fenwick bit tree

namespace nm {
    /*
     * Sleator, Tarjan. ACM.
     * https://www.cs.cmu.edu/~sleator/papers/Self-Adjusting.htm
     * 
     * Derived. Log(n) with Large Constant.
     * Operations: access, insert, delete (remove), join and split.
     */
    template <class C, class T, class U>
    class Splay : public SearchTree<C, T, U> {
        protected:
            C* splay(C* n); // operation
            C* access(T i, C* n);
        public:
            Splay(std::function<bool(T&, T&)> compare = default_compare<T>);
            
            C* access(T i);
            bool insert(T i);
            U insert(T i, U y);
            bool remove(T i);

            ~Splay() {};

            U & operator [] (T i);

            // join and split
            template <class C, class T, class U>
            friend Splay<C, T, U> join(const Splay<C, T, U> &t1, const Splay<C, T, U> &t2);
            
            template <class C, class T, class U>
            friend std::pair<Splay<C, T, U>, Splay<C, T, U> > split(const T &i, const Splay<C, T, U> &t);
    };
} // splay tree

#endif // TREES
