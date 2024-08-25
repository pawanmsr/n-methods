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
    
    template<typename T, typename U>
    class MultiSort
    {
    private:
        size_t n;
        std::vector<std::size_t> permutation;
    public:
        MultiSort(T n);
        void sort(std::vector<U> &list, std::function<bool(U&, U&)> compare = [](U& a, U& b) {
            return a < b;
        });
        void apply(std::vector<U> &list);
        ~MultiSort();
    };
} // namespace nm

#endif // SORT
