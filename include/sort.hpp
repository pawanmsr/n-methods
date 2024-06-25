#if !defined(SORT)
#define SORT

#include <functional>
#include<vector>

namespace nm
{
    template<typename T, typename U>
    void quick_sort(U lo, U hi, std::vector<T>& v, std::function<bool(T&, T&)> compare = [](T& a, T& b) {
        return a < b;
    });

    template<typename T, typename U>
    void merge_sort(U lo, U hi, std::vector<T>& v, std::function<bool(T&, T&)> compare = [](T& a, T& b) {
        return a < b;
    });
} // namespace nm

#endif // SORT
