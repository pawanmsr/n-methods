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
    KMP::KMP(std::string word, bool case_sensitive) :
        w(word), case_sensitive(case_sensitive) {
        this->flush();
        this->prefix = {0};
        this->partial = {-1};
        this->failure_function();
    }

    bool KMP::compare(char x, char y) {
        auto lower_case = [] (char z) {
            if (z >= 'A' and z <= 'Z')
                z = 'a' + (z - 'A');
            
            return z;
        };

        if (this->case_sensitive) return x == y;
        return lower_case(x) == lower_case(y);
    }

    void KMP::prefix_function() {
        while (this->i < this->n) {
            std::int32_t j = this->partial[i - 1];
            while (j > 0 and not compare(this->s[j], this->s[i]))
                j = this->partial[j - 1];
            
            if (this->s[i] == this->s[j]) j++;
            this->partial.push_back(j);
            this->i++;
        }
    }

    std::vector<int32_t> KMP::search() {
        std::int32_t k = 0;
        std::size_t len_w = this->w.size();
        
        while (this->i < this->n) {
            if (compare(this->w[k], this->s[i])) {
                this->i++;

                k++;
                if (k == len_w) {
                    this->positions.push_back(this->i - k);
                    k = this->partial[k];
                }
            } else {
                k = this->partial[k];
                if (k < 0) {
                    k++;
                    this->i++;
                }
            }
        }

        return this->positions;
    }

    void KMP::failure_function() {
        std::int32_t i = 0;
        std::int32_t j = 1;

        std::size_t len_w = this->w.size();

        while (j < len_w) {
            if (this->compare(this->w[i], this->w[j]))
                this->partial.push_back(this->partial[i]);
            else {
                this->partial.push_back(i);
                while (i >= 0 and not this->compare(this->w[i], this->w[j]))
                    i = this->partial[i];
            }

            j++;
            i++;
        }

        this->partial.push_back(i);
    }

    void KMP::flush() {
        this->s.clear();
        this->n = 0;
        this->i = 0;
    }

    void KMP::clear() {
        this->positions.clear();
        this->partial.clear();
        this->prefix.clear();

        w.clear();
        this->flush();
    }

    void KMP::stream(std::string s) {
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
