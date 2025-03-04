#include <search.hpp>

#include <functional>

namespace nm {
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
} // binary search

template int nm::bound_search<int, int>(int, const int, const int,
    const std::vector<int>&, std::function<bool(int&, int&)>);

template int nm::bound_search<long long, int>(long long, const int, const int,
    const std::vector<long long>&, std::function<bool(long long&, long long&)>);

namespace nm {
    std::vector<std::uint32_t> z_function(std::string s) {
        std::int32_t st = 0;
        std::int32_t en = 0;
        std::uint32_t n = s.length();
        std::vector<std::uint32_t> z(n);
        for (std::int32_t i = 0; i < n; i++) {
            z[i] = std::max(std::min(std::int32_t(z[i - st]), en - i), 0);
            while (i + z[i] < n and s[z[i]] == s[i + z[i]]) {
                st = i;
                en = i + z[i];
                z[i]++;
            }
        }

        return z;
    }
} // z function

namespace nm {
    SS::SS(std::string word, bool case_sensitive, std::size_t memory) :
    w(word), case_sensitive(case_sensitive), critical_memory(memory) {}

    bool SS::compare(char x, char y) {
        auto lower_case = [] (char z) {
            if (z >= 'A' and z <= 'Z')
                z = 'a' + (z - 'A');
            
            return z;
        };

        if (this->case_sensitive) return x == y;
        return lower_case(x) == lower_case(y);
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
}

namespace nm {
    KMP::KMP(std::string word, bool case_sensitive, std::size_t memory) :
        SS(word, case_sensitive, memory) {
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

    void KMP::prefix_function() {
        const std::size_t len_w = this->w.length();
        
        for (std::int32_t i = 1; i < len_w; i++) {
            std::int32_t j = this->prefix[i - 1];
            while (j > 0 and not this->compare(this->w[j], this->w[i]))
                j = this->prefix[j - 1];
            
            if (this->compare(this->w[j], this->w[i])) j++;
            this->prefix.push_back(j);
        }

        if (memory() > this->critical_memory)
            this->flush();
    }

    std::vector<int32_t> KMP::search() {
        std::int32_t k = 0;
        std::size_t len_w = this->w.size();
        
        while (this->i < this->n) {
            if (this->compare(this->w[k], this->s[i])) {
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
} // namespace nm

namespace nm {
    BMA::BMA(std::string word, bool case_sensitive, std::size_t memory) : 
        SS(word, case_sensitive, memory) {
        this->flush();
        this->delta_function();
    }

    void BMA::delta_function() {
        const std::size_t len_w = this->w.length();
        
        this->delta_one.resize(ASCII, len_w);
        for (std::int32_t j = len_w - 1; j >= 0; j--) {
            if (this->delta_one[this->w[j]] == len_w)
                this->delta_one[this->w[j]] -= j + 1;
        }

        std::uint32_t prefix_j = 0;
        // prefix_j is the smallest j for which there is prefix for suffix starting from j + 1
        std::function<std::int32_t(std::int32_t)> rpr =
            [&] (const std::size_t j) -> std::int32_t {
                // rightmost plausible reoccurrence //
                std::uint32_t len_suffix = len_w - (j + 1);
                
                bool is_prefix = len_suffix;
                for (std::uint32_t k = 0; k < len_suffix; k++) {
                    if (this->w[k] == this->w[j + 1 + k]) continue;
                    
                    is_prefix = false;
                    break;
                }
                
                if (is_prefix) prefix_j = j;

                for (std::int32_t k = len_w - 1; k >= 0; k--) {
                    std::int32_t j_prime = len_w - 1;
                    
                    if (j + 1 > j_prime) break;

                    std::int32_t k_prime = k;
                    while (k_prime >= 0 and j_prime > j) {
                        if (this->w[k_prime] != this->w[j_prime]) break;
                        
                        k_prime--;
                        j_prime--;
                    }
                    
                    if (k_prime >= 0 and j_prime == j and 
                        this->w[k_prime] != this->w[j_prime])
                            return k + 1 - len_suffix; // verify
                }

                return j - prefix_j; // verify
            };

        this->delta_two.resize(len_w);
        for (std::int32_t j = len_w - 1; j >= 0; j--)
            this->delta_two[j] = len_w - rpr(j);
    }

    std::size_t BMA::memory(bool all) {
        std::size_t m = sizeof(this->s) + sizeof(char) * this->n;
        if (not all) return m; // memory in bytes
        
        m += sizeof(this->positions) + 
            sizeof(std::uint32_t) * this->positions.size();
        m += sizeof(this->delta_one) +
            sizeof(std::uint32_t) * this->delta_one.size();
        m += sizeof(this->delta_two) +
            sizeof(std::uint32_t) * this->delta_two.size();
        m += sizeof(this->delta_zero) +
            sizeof(std::uint32_t) * this->delta_zero.size();
        
        return m;
    }

    void BMA::clear() {
        this->positions.clear();

        SS::clear();
    }

    std::vector<std::uint32_t> BMA::search() {
        const std::size_t len_w = this->w.size();

        // adapted for understandability
        std::int32_t j, i = this->i + len_w - 1;
        while (i < this->n) {
            this->i = i;
            j = len_w - 1;

            
            // analysis pending //
            // slow implementation //
            // sequence is matched in backwards order //
            while (j >= 0 and this->compare(this->s[i], this->w[j])) {
                i--;
                j--;
            }

            if (j < 0) {
                // found a match //
                this->positions.push_back(++i);
                i += len_w;
                continue;
            }

            i += std::max(this->delta_one[this->s[i]], this->delta_two[j]);
        }

        return this->positions;
    }
} // sublinear string search
