#if !defined(SEARCH)
#define SEARCH

#include <utility.hpp>

#include <vector>
#include <functional>

namespace nm
{
    template<class T, typename U>
    U bound_search(T element, const U lo, const U hi, const std::vector<T>& space,
        std::function<bool(T&, T&)> compare = default_compare<T>);
} // namespace nm


#endif // SEARCH
