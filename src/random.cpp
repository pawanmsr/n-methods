#include <random.hpp>

#include <chrono>

namespace nm {
    uint64_t Random::query_clock() {
        return std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    }

    Random::Random() {
        this->p = 0;
        this->n = this->query_clock();
    }

    Random::Random(std::uint32_t s, std::uint32_t p) {
        this->n = s;
        this->p = p;
    }

    std::uint32_t Random::number(std::uint32_t xr) {
        return this->number(0, xr);
    }

    std::uint32_t Random::number(std::uint32_t xl, std::uint32_t xr) {
        std::uint32_t mod = xr - xl + 1UL;
        
        int32_m p = this->p;
        if (not int(p)) p = this->query_clock();
        
        this->n = this->n * p + p;
        return xl + int(this->n) % mod;
    }
} // random numbers
