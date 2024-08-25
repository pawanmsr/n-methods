#include <sort.hpp>

#include <algorithm>

namespace nm
{
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
    
    // Prefer merge_sort.
    // U is expected to be integer data type.
    template<class T, typename U>
    void quick_sort(U lo, U hi, std::vector<T>& list, std::function<bool(T&, T&)> compare) {
        if (lo >= 0 and lo < hi and hi < U(list.size())) {
            U k = partition<T, U>(lo, hi, list, compare);
            quick_sort<T, U>(lo, k - 1, list, compare);
            quick_sort<T, U>(k + 1, hi, list, compare);
        }
    }

    // U is expected to be integer data type.
    // V is expected to be long integer data type.
    template<class T, typename U, typename V>
    V merge_sort(U lo, U hi, std::vector<T>& list, std::function<bool(T&, T&)> compare) {
        V inversions = 0;
        
        if (lo >= 0 and lo < hi and hi < U(list.size())) {
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
        }

        return inversions;
    }

    template<typename T, typename U>
    MultiSort<T, U>::MultiSort(T n) {
        this->n = n;
        this->permutation.resize(n);
        std::iota(this->permutation.begin(), this->permutation.end(), 1);
    }

    template<typename T, typename U>
    void MultiSort<T, U>::sort(std::vector<U> &list,
        std::function<bool(U&, U&)> compare = [](U& a, U& b) {
            return a < b;
        }) {
            auto compare_wrapper = [&](std::size_t i, std::size_t j) {
                return compare(list[i], list[j]);
            };
            merge_sort(0, this->n - 1, this->permutation, compare_wrapper);
            return this->apply(list);
        }

    template<typename T, typename U>
    void MultiSort<T, U>::apply(std::vector<U> &list) {
        std::transform(this->permutation.begin(), this->permutation.end(),
            list.begin(), [&](std::size_t i) {
                return list[i];
            });
    }
    
    template<typename T, typename U>
    MultiSort<T, U>::~MultiSort() {
        delete this;
    }

} // namespace nm

template int nm::merge_sort<int, int, int>(int, int,
    std::vector<int>&, std::function<bool(int&, int&)>);
template int nm::merge_sort<long long, int, int>(int, int,
    std::vector<long long>&, std::function<bool(long long&, long long&)>);

template void nm::quick_sort<int, int>(int, int,
    std::vector<int>&, std::function<bool(int&, int&)>);
template void nm::quick_sort<long long, int>(int, int,
    std::vector<long long>&, std::function<bool(long long&, long long&)>);
