#include <hash.hpp>

#include <sort.hpp>

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
        assert(right <= this->n and right > left);
        return this->subtract(this->hash[right],
            this->multiply(this->hash[left],
                this->power[right - left]));
    }
} // string

namespace nm {
    template<typename M, M P>
    ModHash<M, P>::ModHash(std::string &s) {
        this->n = s.length();
        this->hash.reserve(this->n + 1);
        this->power.reserve(this->n + 1);

        this->hash = {0};
        this->power = {1};
        for (char s_i : s) {
            this->hash.push_back(this->hash.back() * P + s_i);
            this->power.push_back(this->power.back() * P);
        }
    }

    template<typename M, M P>
    std::int64_t ModHash<M, P>::Interval(std::size_t left, std::size_t right) {
        assert(right <= this->n and right > left);
        return this->hash[right] - this->hash[left] * this->power[right - left];
    }
} // hash function int32_m

namespace nm {
    template <typename T>
    CoordinateCompression<T>::CoordinateCompression(std::vector<T> data) {
        std::int32_t lo = 0; std::int32_t hi = data.size() - 1;
        hybrid_sort<T>(0, hi, data);

        for (T d : data) {
            if (this->coordinates.search(d)) continue;
            this->coordinates.insert(d, elements.size());
            elements.push_back(d);
        };
    }

    template <typename T>
    std::int32_t CoordinateCompression<T>::coordinate(T x) {
        if (not this->coordinates.search(x)) return -1;
        return coordinates.access(x);
    }

    template <typename T>
    T CoordinateCompression<T>::element(std::size_t i) {
        assert(i < this->elements.size())
        return this->element[i];
    }
}

