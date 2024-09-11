#include <segment_tree.hpp>

namespace nm
{
    template<class T, class U>
    SegmentTree<T, U>::SegmentTree(std::vector<T> &data, U *integrator_struct) : 
        integrator(integrator_struct) {
            size_t m = 1;
            while (m < data.size()) m *= 2;
            data.resize(m, integrator->identity);
            
            this->n = m;
            this->tree.resize(this->n * 2);
            this->construct(data, 0, this->n - 1, 0);
        }
    
    template<class T, class U>
    T SegmentTree<T, U>::traverse(size_t lo, size_t hi, size_t tlo, size_t thi, size_t i) {
        if (lo > hi) return this->integrator->identity;
        if (lo == tlo and hi == thi)
            return this->tree[i];
        
        size_t mid = tlo + (thi - tlo) / 2;
        return this->integrator->integrate(this->traverse(lo, min(mid, hi), tlo, mid, 2 * i),
            this->traverse(max(lo, mid + 1), hi, mid + 1, thi, 2 * i + 1));
    }
    
    template<class T, class U>
    T SegmentTree<T, U>::query(size_t left, size_t right) {
        // validate left and right
        return this->traverse(left, right, 0, this->n - 1, 0);
    }
    
    template<class T, class U>
    void SegmentTree<T, U>::construct(std::vector<T> &data, size_t lo, size_t hi, size_t i) {
        if (lo == hi) this->tree[lo] = data[i];
        else {
            size_t mid = lo + (hi - lo) / 2;
            this->construct(data, lo, mid, i * 2);
            this->construct(data, mid + 1, hi, i * 2 + 1);
            this->tree = this->integrator->integrate(this->tree[i * 2], this->tree[i * 2 + 1]);
        }
    }
    
    template<class T, class U>
    SegmentTree<T, U>::~SegmentTree() {
    }
} // namespace nm

