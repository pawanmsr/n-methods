#include <combinatorics.hpp>

namespace nm
{
    template<typename T>
    bool next_permutation(std::vector<T>& permutation) {
        const size_t n = permutation.size();

        size_t i = n - 1;
        while (i > 0 and permutation[i - 1] >= permutation[i])
            i--;
        
        if (i > 0) {
            size_t j = i - 1;
            size_t k = n - 1;
            while (k > i and permutation[k] <= permutation[j])
                k--;

            swap(permutation[j], permutation[k]);
        }

        reverse(permutation.begin() + i, permutation.end());
        return i > 0;
    }
} // namespace nm
