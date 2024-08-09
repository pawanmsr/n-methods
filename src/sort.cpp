#include <sort.hpp>

#include <algorithm>

namespace nm
{
    template<class T, typename U>
    U partition(const U lo, const U hi, std::vector<T> &list, std::function<bool(T&, T&)> compare) {
        const T pivot = list[hi];
        
        U i = lo;
        U j = hi;
        while (i < j) {
            if (compare(pivot, list[i])) {
                while (j > i && compare(pivot, list[j]))
                    j--;
                
                if (!compare(pivot, list[j]))
                    std::swap(list[i], list[j]);
                else break;
            }
            
            i++;
        }

        std::swap(list[i], list[hi]);
        return i;
    }

    // U is expected to be integer data type.
    template<class T, typename U>
    void quick_sort(U lo, U hi, std::vector<T>& list, std::function<bool(T&, T&)> compare) {
        if (lo >= 0 && lo < hi && hi < list.size()) {
            U k = partition(lo, hi, list, compare);
            quick_sort(lo, k - 1, list, compare);
            quick_sort(k + 1, hi, list, compare);
        }
    }

    // U is expected to be integer data type.
    // V is expected to be long integer data type.
    template<class T, typename U, typename V>
    V merge_sort(U lo, U hi, std::vector<T>& list, std::function<bool(T&, T&)> compare) {
        V inversions = 0;
        
        if (lo >= 0 && lo < hi && hi < list.size()) {
            U mid = lo + (hi - lo) / 2;

            inversions += merge_sort<T, U, V>(lo, mid, list, compare);
            inversions += merge_sort<T, U, V>(mid + 1, hi, list, compare);

            U i = lo;
            U j = mid + 1;
            std::vector<T> merged;
            while (i <= mid && j <= hi) {
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
} // namespace nm
