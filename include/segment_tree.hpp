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
        int32_t n;
        vector<T> tree;
        vector<T> auxiliary;
        U *integrator;
    
    protected:
        bool propagate(int32_t i);
        void construct(std::vector<T> &data, int32_t lo, int32_t hi, int32_t i);
        T query_tree(int32_t lo, int32_t hi, int32_t tlo, int32_t thi, int32_t i);
        T update_tree(T value, int32_t position, int32_t lo, int32_t hi, int32_t i);
        T update_tree(T value, int32_t lo, int32_t hi, int32_t tlo, int32_t thi, int32_t i);
    
    public:
        SegmentTree(std::vector<T> &data, U *integrator_struct = new U());
        T query(int32_t left, int32_t right);
        T update(T value, int32_t position);
        T update(T value, int32_t left, int32_t right);
        ~SegmentTree();
    };
} // namespace nm


#endif // SEGMENT_TREE
