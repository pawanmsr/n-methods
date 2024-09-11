#if !defined(SEGMENT_TREE)
#define SEGMENT_TREE

#include <vector>

namespace nm
{
    template<class T, class U>
    class SegmentTree
    {
    private:
        size_t n;
        vector<T> tree;
        U integrator;
    protected:
        void construct(std::vector<T> &data, size_t lo, size_t hi, size_t i);
        T query_tree(size_t lo, size_t hi, size_t tlo, size_t thi, size_t i);
        bool update_tree(T value, size_t position, size_t lo, size_t hi, size_t i);
    public:
        SegmentTree(std::vector<T> &data, U *integrator_struct);
        T query(size_t left, size_t right);
        bool update(T value, size_t position);
        ~SegmentTree();
    };
} // namespace nm


#endif // SEGMENT_TREE
