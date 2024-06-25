#if !defined(SEARCH)
#define SEARCH

#include <vector>
#include <functional>

namespace nm
{
    template<typename T>
    int bound_search(T element, const std::vector<T>& space, std::function<bool(T&, T&)> compare = [](T& a, T& b) {
        return a < b;
    });
} // namespace nm


#endif // SEARCH
