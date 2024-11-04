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
            if (compare(space_value, element)) {
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


namespace nm {
    KMP::KMP(std::string word) : w(word) {
        this->prefix = {0};
    }

    void KMP::prefix_function() {
        while (this->i < this->n) {
            std::size_t j = this->partial[i - 1];
            while (j > 0 and this->s[j] != this->s[i])
                j = this->partial[j - 1];
            
            if (this->s[i] == this->s[j]) j++;
            this->partial.push_back(j);
        }
    }

    void KMP::append(std::string s) {
        this->s += s;
        this->n += s.length();
    }
    
    void KMP::stream(char c) {
        this->s += c;
        this->n++;
    }
    
    KMP::~KMP() {
    }
} // namespace nm
