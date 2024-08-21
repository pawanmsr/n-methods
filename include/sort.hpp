#if !defined(SORT)
#define SORT

#include <functional>
#include <vector>

namespace nm
{
    template<class T, typename U>
    void quick_sort(U lo, U hi, std::vector<T>& v,
        std::function<bool(T&, T&)> compare = [](T& a, T& b) {
            return a < b;
        });

    template<class T, typename U, typename V>
    V merge_sort(U lo, U hi, std::vector<T>& v,
        std::function<bool(T&, T&)> compare = [](T& a, T& b) {
            return a < b;
        });
} // namespace nm

#endif // SORT
