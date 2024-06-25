#include <search.hpp>

namespace nm
{
    template<typename T>
    int bound_search(T element, const int lo, const int hi, const std::vector<T>& space, std::function<bool(T&, T&)> compare) {
        int i = 0;
        int jump = space.size();
        while (jump > 0) {
            int step = jump / 2;
            int j = i + step;
            if (!compare(element, space[j])) {
                i = j + 1;
                jump -= step + 1;
            } else jump = step;
        }

        return i;
    }
} // namespace nm
