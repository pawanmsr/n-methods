#include <segment_tree.hpp>

#include <utility.hpp>

namespace nm
{
    // !? lookout for // modify // in popagate function
    // and assignment in update_tree function
    // More complex problems may require overhaul.
    template <class T, class U>
    SegmentTree<T, U>::SegmentTree(std::vector<T> &data, U *integrator_struct) : 
        integrator(integrator_struct) {
            this->n = 1;
            while (this->n < std::int32_t(data.size()))
                this->n *= 2;
            
            data.resize(this->n, this->integrator->identity);
            
            this->tree.resize(this->n * 2);
            this->auxiliary.resize(this->n * 2, this->integrator->identity); // modify //
            // auxiliary holds delayed range updates

            this->construct(data, 0, this->n - 1, 1);
        }

    // modify //
    // propagate needs to be customized according to requirement
    template <class T, class U>
    bool SegmentTree<T, U>::propagate(std::int32_t i) {
        if (this->auxiliary[i] == this->integrator->identity) return false;

        // lazy propagation
        this->tree[i * 2] = this->integrator->assign(this->auxiliary[i]);     // modify //
        this->tree[i * 2 + 1] = this->integrator->assign(this->auxiliary[i]); // modify //
        this->tree[i] = this->integrator->integrate(this->tree[i * 2], this->tree[i * 2 + 1]);

        // FIXME: this is perhaps not needed when i * 2
        // is greater than or equal to this->n
        this->auxiliary[i * 2] = this->integrator->assign(this->auxiliary[i]);     // modify //
        this->auxiliary[i * 2 + 1] = this->integrator->assign(this->auxiliary[i]); // modify //

        this->auxiliary[i] = this->integrator->identity;
        return true;
    }

    template <class T, class U>
    T SegmentTree<T, U>::query_tree(std::int32_t lo, std::int32_t hi,
        std::int32_t tlo, std::int32_t thi, std::int32_t i) {
            if (lo > hi) return this->integrator->identity;
            if (lo == tlo and hi == thi) return this->tree[i];

            this->propagate(i);

            std::int32_t mid = tlo + (thi - tlo) / 2;
            return this->integrator->integrate(this->query_tree(lo, min(mid, hi), tlo, mid, i * 2),
                this->query_tree(max(lo, mid + 1), hi, mid + 1, thi, i * 2 + 1));
        }

    // position is index in zero indexed sequence
    template <class T, class U>
    T SegmentTree<T, U>::update_tree(T value, std::int32_t position,
        std::int32_t lo, std::int32_t hi, std::int32_t i) {
            if (lo == hi) return this->tree[i] = this->integrator->assign(value); // modify //

            std::int32_t mid = lo + (hi - lo) / 2;
            if (position <= mid) this->update_tree(value, position, lo, mid, i * 2);
            else this->update_tree(value, position, mid + 1, hi, i * 2 + 1);

            return this->tree[i] = this->integrator->integrate(this->tree[i * 2],
                this->tree[i * 2 + 1]);
        }

    template <class T, class U>
    T SegmentTree<T, U>::update_tree(T value, std::int32_t lo, std::int32_t hi,
        std::int32_t tlo, std::int32_t thi, std::int32_t i) {
        if (lo > hi) return this->integrator->identity;

        if (lo == tlo and hi == thi) {
            this->auxiliary[i] = this->integrator->assign(value);   // modify //
            return this->tree[i] = this->integrator->assign(value); // modify //
        } else {
            this->propagate(i);

            std::int32_t mid = tlo + (thi - tlo) / 2;
            this->update_tree(value, lo, min(mid, hi), tlo, mid, i * 2);
            this->update_tree(value, max(lo, mid + 1), hi, mid + 1, thi, i * 2 + 1);
            
            return this->tree[i] = this->integrator->integrate(this->tree[i * 2],
                this->tree[i * 2 + 1]);
        }
    }

    // left and right are indices in zero indexed sequence
    template <class T, class U>
    T SegmentTree<T, U>::query(std::int32_t left, std::int32_t right) {
        assert(left >= 0); assert(right < this->n);
        return this->query_tree(left, right, 0, this->n - 1, 1);
    }

    // position is index in zero indexed sequence
    template <class T, class U>
    T SegmentTree<T, U>::update(T value, std::int32_t position) {
        assert(position >= 0 and position < this->n);
        return update_tree(value, position, 0, this->n - 1, 1);
    }

    // left and right are indices in zero indexed sequence
    // !? modify assignment in update_tree protected method
    template <class T, class U>
    T SegmentTree<T, U>::update(T value, std::int32_t left, std::int32_t right) {
        assert(left >= 0); assert(right < this->n);
        return update_tree(value, left, right, 0, this->n - 1, 1);
    }

    template <class T, class U>
    void SegmentTree<T, U>::construct(std::vector<T> &data,
        std::int32_t lo, std::int32_t hi, std::int32_t i) {
            if (lo == hi) this->tree[i] = this->integrator->assign(data[lo]); // modify //
            else {
                std::int32_t mid = lo + (hi - lo) / 2;
                this->construct(data, lo, mid, i * 2);
                this->construct(data, mid + 1, hi, i * 2 + 1);

                this->tree[i] = this->integrator->integrate(this->tree[i * 2],
                    this->tree[i * 2 + 1]);
            }
        }

    template <class T, class U>
    SegmentTree<T, U>::~SegmentTree() {}
} // namespace nm

template class nm::SegmentTree<int, nm::Integrator<int>>;
