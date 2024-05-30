#include <sort.hpp>

#include <algorithm>

namespace nm
{
    template<typename T>
    int partition(const int lo, const int hi, std::vector<T> &list, std::function<bool(T, T)>& compare) {
        const int pivot = list[hi];
        
        int i = lo;
        int j = hi;
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

    template<typename T>
    void quick_sort(int lo, int hi, std::vector<T> &list, std::function<bool(T, T)>& compare = [&](T& a, T& b) {
        return a < b;
    }) {
        if (lo < hi) {
            int k = partition(lo, hi, list, compare);
            quick_sort(lo, k - 1, list, compare);
            quick_sort(k + 1, hi, list, compare);
        }
    }
} // namespace nm
