#include <search.hpp>

namespace nm
{
    // lo: lower index, hi: higher index
    template<class T, typename U>
    U bound_search(T element, const U lo, const U hi,
        const std::vector<T>& space, std::function<bool(T&, T&)> compare) {
        U i = 0;
        U jump = space.size();
        while (jump > 0) {
            U step = jump / 2;
            U j = i + step;
            T space_value = space[j];
            if (not compare(element, space_value)) {
                i = j + 1;
                jump -= step + 1;
            } else jump = step;
        }

        return i;
    }
} // namespace nm

template int nm::bound_search<int, int>(int, const int, const int,
    const std::vector<int>&, std::function<bool(int&, int&)>);

template int nm::bound_search<long long, int>(long long, const int, const int,
    const std::vector<long long>&, std::function<bool(long long&, long long&)>);
