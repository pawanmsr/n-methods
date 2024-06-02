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
        if (lo >= 0 && lo < hi && hi < list.size()) {
            int k = partition(lo, hi, list, compare);
            quick_sort(lo, k - 1, list, compare);
            quick_sort(k + 1, hi, list, compare);
        }
    }


    template<typename T>
    void merge_sort(int lo, int hi, std::vector<T> &list, std::function<bool(T, T)>& compare = [&](T& a, T& b) {
        return a < b;
    }) {
        if (lo >= 0 && lo < hi && hi < list.size()) {
            int mid = lo + (hi - lo) / 2;

            merge_sort(lo, mid, list, compare);
            merge_sort(mid + 1, hi, list, compare);

            int i = lo;
            int j = mid + 1;
            std::vector<int> merged;
            while (i <= mid && j <= hi) {
                if (compare(list[j], list[i]))
                    merged.push_back(list[j++]);
                else merged.push_back(list[i++]);
            }

            while (i <= mid) merged.push_back(list[i++]);
            while (j <= hi) merged.push_back(list[j++]);

            for (int k = 0; k <= hi - lo; k++)
                list[lo + k] = merged[k];
        }
    }
} // namespace nm
