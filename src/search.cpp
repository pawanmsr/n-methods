#include <search.hpp>

namespace nm
{
    // lo: lower index, hi: higher index
    template<class T, typename U>
    U bound_search(T element, const U lo, const U hi, const std::vector<T>& space, std::function<bool(T&, T&)> compare) {
        U i = 0;
        U jump = space.size();
        while (jump > 0) {
            U step = jump / 2;
            U j = i + step;
            if (!compare(element, space[j])) {
                i = j + 1;
                jump -= step + 1;
            } else jump = step;
        }

        return i;
    }
} // namespace nm
