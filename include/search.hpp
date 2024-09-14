#if !defined(SEARCH)
#define SEARCH

#include <utility>

#include <vector>
#include <functional>

namespace nm
{
    template<class T, typename U>
    U bound_search(T element, const U lo, const U hi, const std::vector<T>& space,
        std::function<bool(T&, T&)> compare = default_compare);
} // namespace nm


#endif // SEARCH
