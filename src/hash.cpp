#include <hash.hpp>

namespace nm {
    template<std::int64_t M, std::int64_t P>
    Hash<M, P>::Hash(std::string &s) : Arithmetic<std::int64_t>::Arithmetic(M) {
        this->n = s.length();
        this->hash.reserve(this->n + 1);
        this->power.reserve(this->n + 1);

        this->hash = {0};
        this->power = {1};
        for (char s_i : s) {
            this->hash.push_back(this->add(this->multiply(this->hash.back(), P), s_i));
            this->power.push_back(this->multiply(this->power.back(), P));
        }
    }

    template<std::int64_t M, std::int64_t P>
    std::int64_t Hash<M, P>::Interval(std::size_t left, std::size_t right) {
        assert(right <= this->n and right >= left);
        return this->subtract(this->hash[right],
            this->multiply(this->hash[left],
                this->power[right - left]));
    }
    
    template<std::int64_t M, std::int64_t P>
    Hash<M, P>::~Hash() {
    }
} // namespace nm
