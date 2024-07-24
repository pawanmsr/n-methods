#if !defined(SEARCH)
#define SEARCH

#include <vector>
#include <functional>

namespace nm
{
    template<class T, typename U>
    U bound_search(T element, const U lo, const U hi, const std::vector<T>& space,
        std::function<bool(T&, T&)> compare = [](T& a, T& b) {
            return a < b;
        });
} // namespace nm


#endif // SEARCH
