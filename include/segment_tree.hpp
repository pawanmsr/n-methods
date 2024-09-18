#if !defined(SEGMENT_TREE)
#define SEGMENT_TREE

#include <vector>

namespace nm
{
    // T is type of data to query on
    template<class T>
    struct U {
        T identity;

        // Also modify in update_tree and propagate
        T assign(T data) {
            // Add arguments and math
            // for flexibility and functionality.
            // Must be associative and commutative
            //  (and optionally distributive) properties.
            return data;
        }

        T integrate(T a, T b) {
            // Replace with operation(s) on a and b.
            return identity;
        }

        U(T i) : identity(i) {};
    };
    
    /*
     * U is a pointer to object or struct.
     * U must contain an 'identity' element.
     * U must contain an 'assign' function
     *  which must have associative and commutative
     *  (and optionally distributive) properties.
     * U must contain an 'integrate' function
     *  to combine two separate parts of the tree.
     */
    template<class T, class U>
    class SegmentTree
    {
    private:
        size_t n;
        vector<T> tree;
        vector<T> auxiliary;
        U *integrator;
    
    protected:
        bool propagate(size_t i);
        void construct(std::vector<T> &data, size_t lo, size_t hi, size_t i);
        T query_tree(size_t lo, size_t hi, size_t tlo, size_t thi, size_t i);
        T update_tree(T value, size_t position, size_t lo, size_t hi, size_t i);
        T update_tree(T value, size_t lo, size_t hi, size_t tlo, size_t thi, size_t i);
    
    public:
        SegmentTree(std::vector<T> &data, U *integrator_struct = new U());
        T query(size_t left, size_t right);
        T update(T value, size_t position);
        T update(T value, size_t left, size_t right);
        ~SegmentTree();
    };
} // namespace nm


#endif // SEGMENT_TREE
