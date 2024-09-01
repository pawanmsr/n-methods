#if !defined(SORT)
#define SORT

#include <functional>
#include <vector>

namespace nm
{
    template<typename T>
    std::function<bool(T&, T&)> default_compare = [](T& a, T& b) {
        return a < b;
    };

    template<class T, typename U>
    void hybrid_sort(U lo, U hi, std::vector<T>& list,
        std::function<bool(T&, T&)> compare = default_compare);

    template<class T, typename U>
    void introspective_qsort(U lo, U hi, std::vector<T>& v,
        std::function<bool(T&, T&)> compare = default_compare, U depth);
    
    template<class T, typename U>
    void heap_sort(U lo, U hi, std::vector<T>& list,
        std::function<bool(T&, T&)> compare = default_compare);

    template<class T, typename U>
    void insertion_sort(U lo, U hi, std::vector<T>& list,
        std::function<bool(T&, T&)> compare = default_compare);
    
    template<class T, typename U>
    void quick_sort(U lo, U hi, std::vector<T>& v,
        std::function<bool(T&, T&)> compare = default_compare);

    template<class T, typename U, typename V>
    V merge_sort(U lo, U hi, std::vector<T>& v,
        std::function<bool(T&, T&)> compare = default_compare);
    
    // U is expected to be positive integral type.
    template<class T, typename U>
    class MultiSort
    {
    private:
        std::size_t n;
        std::vector<std::size_t> permutation;
    public:
        MultiSort(U n);
        U sort(std::vector<T> &list, std::function<bool(T&, T&)> compare = default_compare);

        void apply(std::vector<T> &list);
        ~MultiSort();
    };
} // namespace nm

#endif // SORT
