#include <sort.hpp>

#include <numeric>
#include <utility>
#include <cassert>
#include <cmath>

namespace nm {
    /*
     * Introspective sort.
     * Inrospective plus Insertion three part hybrid
     * sorting but easier to understand, copy and use
     * Refer: LLVM's libc++.
     * 
     * https://danlark.org/2022/04/20/changing-stdsort-at-googles-scale-and-beyond/
     * 
     * Insertion sort for small sizes.
     * Quick sort until recursion stack is maxed out.
     * Heap sort when recursion stack is maxed out.
     * 
     * Hybrid sort is quicker than all others in
     * worst time as well as average time.
     * See LastTest.log for more details.
     */

    // Add type conversion for lambda functions //
    // Are functions allowed to be constexpr ? //
    // TODO: replace all with constexpr where ever possible //

    template<class T, typename U>
    void hybrid_sort(U lo, U hi, std::vector<T>& list, std::function<bool(T&, T&)> compare) {
        introspective_qsort<T, U>(lo, hi, list, U(std::log2(list.size()) * 2), compare);
    }

    // partition is utility function of q_sort and introspective_qsort //
    template<class T, typename U>
    U partition(const U lo, const U hi, std::vector<T> &list,
        std::function<bool(T&, T&)> compare) {
            T pivot = list[hi];
            
            U i = lo;
            for (U j = lo; j < hi; j++) {
                if (not compare(list[j], pivot)) continue;

                std::swap(list[i], list[j]);
                i++;
            }

            std::swap(list[i], list[hi]);
            return i;
        }

    template<class T, typename U>
    void introspective_qsort(U lo, U hi, std::vector<T>& list, U depth,
        std::function<bool(T&, T&)> compare) {
            assert(lo >= 0); assert(hi < U(list.size())); assert(depth >= 0);

            if (lo >= hi) return ;
            
            if (list.size() < SIZE_LIMIT_IS) insertion_sort<T, U>(lo, hi, list, compare);
            else if (depth == 0) heap_sort<T, U>(lo, hi, list, compare);
            else {
                U k = partition<T, U>(lo, hi, list, compare);
                introspective_qsort<T, U>(lo, k - 1, list, depth - 1, compare);
                introspective_qsort<T, U>(k + 1, hi, list, depth - 1, compare);
            }
        }
    
    template<class T, typename U>
    void heap_sort(U lo, U hi, std::vector<T>& list, std::function<bool(T&, T&)> compare) {
        assert(lo >= 0); assert(hi < U(list.size()));

        auto down_left = [&](U i) {
            return lo + (i - lo) * 2 + 1;
        };

        auto down_right = [&](U i) {
            return lo + (i - lo) * 2 + 2;
        };

        U back = hi;
        U front = lo + (hi - lo + 1) / 2;
        while (back > lo) {
            if (front == lo) {
                std::swap(list[back], list[lo]);
                back--;
            } else front--;

            // form the heap from front to back
            U i = front;
            while (down_left(i) <= back) {
                U down = down_left(i);
                if (down_right(i) <= back and 
                    compare(list[down_left(i)], list[down_right(i)]))
                        down = down_right(i);
                
                if (compare(list[i], list[down])) {
                    std::swap(list[i], list[down]);
                    i = down;
                } else break;
            }
        }
    }

    template<class T, typename U>
    void insertion_sort(U lo, U hi, std::vector<T>& list, std::function<bool(T&, T&)> compare) {
        assert(lo >= 0); assert(hi < U(list.size()));

        for (U i = lo; i <= hi; i++) {
            T pivot = list[i];
            
            for (U j = i; j > lo; j--) {
                if (compare(list[j - 1], pivot)) {
                    list[j] = pivot;
                    break;
                }

                list[j] = list[j - 1];
            }
        }
    }
    
    // Prefer merge_sort.
    // U is expected to be integer data type.
    template<class T, typename U>
    void quick_sort(U lo, U hi, std::vector<T>& list, std::function<bool(T&, T&)> compare) {
        assert(lo >= 0); assert(hi < U(list.size()));
        
        if (lo >= hi) return ;
        
        U k = partition<T, U>(lo, hi, list, compare);
        quick_sort<T, U>(lo, k - 1, list, compare);
        quick_sort<T, U>(k + 1, hi, list, compare);
    }

    // Prefer hybrid_sort.
    // U is expected to be integer data type.
    // V is expected to be long integer data type.
    template<class T, typename U, typename V>
    V merge_sort(U lo, U hi, std::vector<T>& list, std::function<bool(T&, T&)> compare) {
        assert(lo >= 0); assert(hi < U(list.size()));
        
        V inversions = 0;
        if (lo >= hi) return inversions;

        U mid = lo + (hi - lo) / 2;
        inversions += merge_sort<T, U, V>(lo, mid, list, compare);
        inversions += merge_sort<T, U, V>(mid + 1, hi, list, compare);

        U i = lo;
        U j = mid + 1;
        std::vector<T> merged;
        while (i <= mid and j <= hi) {
            if (compare(list[j], list[i])) {
                merged.push_back(list[j++]);
                inversions += mid + 1 - i;
            } else merged.push_back(list[i++]);
        }

        while (i <= mid) merged.push_back(list[i++]);
        while (j <= hi) merged.push_back(list[j++]);

        for (U k = 0; k <= hi - lo; k++)
            list[lo + k] = merged[k];

        return inversions;
    }

    template<class T, typename U>
    MultiSort<T, U>::MultiSort(U size) : n(size) {
        this->permutation.resize(size);
        std::iota(this->permutation.begin(), this->permutation.end(), 0);
    }

    template<class T, typename U>
    U MultiSort<T, U>::sort(std::vector<T> &list, std::function<bool(T&, T&)> compare) {
        std::function<bool(std::size_t&, std::size_t&)> wrapped_compare = 
            [&](std::size_t i, std::size_t j) {
                return compare(list[i], list[j]);
            };
        
        U inversions = merge_sort<std::size_t, U, U>(0, this->n - 1,
            this->permutation, wrapped_compare);
        
        this->apply(list);
        return inversions;
    }

    template<class T, typename U>
    void MultiSort<T, U>::apply(std::vector<T> &list) {
        std::vector<T> list_prime(this->n);
        std::transform(this->permutation.begin(), this->permutation.end(),
            list_prime.begin(), [&](std::size_t i) {
                return list[i];
            });
        
        list.assign(list_prime.begin(), list_prime.end());
    }
} // namespace nm

template void nm::introspective_qsort<int, int>(int, int, std::vector<int>&, int depth,
    std::function<bool(int&, int&)> compare);
template void nm::introspective_qsort<long long, int>(int, int, std::vector<long long>&, int depth,
    std::function<bool(long long&, long long&)> compare);

template void nm::hybrid_sort<int, int>(int, int,
    std::vector<int>&, std::function<bool(int&, int&)>);
template void nm::hybrid_sort<long long, int>(int, int,
    std::vector<long long>&, std::function<bool(long long&, long long&)>);

template void nm::heap_sort<int, int>(int, int,
    std::vector<int>&, std::function<bool(int&, int&)>);
template void nm::heap_sort<long long, int>(int, int,
    std::vector<long long>&, std::function<bool(long long&, long long&)>);

template int nm::merge_sort<int, int, int>(int, int,
    std::vector<int>&, std::function<bool(int&, int&)>);
template int nm::merge_sort<long long, int, int>(int, int,
    std::vector<long long>&, std::function<bool(long long&, long long&)>);

template void nm::quick_sort<int, int>(int, int,
    std::vector<int>&, std::function<bool(int&, int&)>);
template void nm::quick_sort<long long, int>(int, int,
    std::vector<long long>&, std::function<bool(long long&, long long&)>);

template class nm::MultiSort<int, int>;
template class nm::MultiSort<long long, int>;

template void nm::insertion_sort<int, int>(int, int,
    std::vector<int>&, std::function<bool(int&, int&)>);
template void nm::insertion_sort<long long, int>(int, int,
    std::vector<long long>&, std::function<bool(long long&, long long&)>);
