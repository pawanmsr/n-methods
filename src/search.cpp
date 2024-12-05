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
    SS::SS(std::string word, bool case_sensitive, std::size_t memory) :
    w(word), case_sensitive(case_sensitive), critical_memory(memory) {
    }

    void SS::flush() {
        this->s.clear();
        this->n = 0;
        this->i = 0;
    }

    void SS::clear() {
        w.clear();
        this->flush();
    }

    void SS::stream(std::string s) {
        this->s += s;
        this->n += s.length();
    }
    
    void SS::stream(char c) {
        this->s += c;
        this->n++;
    }

    SS::~SS() {}
}

namespace nm {
    KMP::KMP(std::string word, bool case_sensitive, std::size_t memory) :
        SS(word, case_sensitive, critical_memory) {
        this->flush();
        this->prefix = {0};
        this->partial = {-1};
        this->failure_function();
    }

    std::size_t KMP::memory(bool all) {
        std::size_t m = sizeof(this->s) + sizeof(char) * this->n;
        if (not all) return m;
        
        m += sizeof(this->positions) + 
            sizeof(std::int32_t) * this->positions.size();
        m += sizeof(this->partial) + 
            sizeof(std::int32_t) * this->partial.size();
        m += sizeof(this->prefix) + 
            sizeof(std::int32_t) * this->prefix.size();
        return m;
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

        if (memory() > this->critical_memory)
            this->flush();
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

        if (memory() > this->critical_memory)
            this->flush();

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

    void KMP::clear() {
        this->positions.clear();
        this->partial.clear();
        this->prefix.clear();

        SS::clear();
    }
    
    KMP::~KMP() {
    }
} // namespace nm
