#include <random.hpp>

#include <chrono>

namespace nm {
    Random::Random() {
        this->n = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        this->p = 0;
    }

    Random::Random(std::uint32_t s) {
        this->n = s;
        this->p = 0;
    }

    Random::Random(std::uint32_t s, std::uint32_t p) {
        this->n = s;
        this->p = p;
    }

    inline std::uint32_t Random::number(std::uint32_t xr) {
        return this->number(0, xr);
    }

    std::uint32_t Random::number(std::uint32_t xl, std::uint32_t xr) {
        std::uint32_t mod = xr - xl + 1UL;
        
        int32_p p = this->p;
        if (not int(p)) p = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        this->n *= p;

        return xl + int(this->n) % mod;
    }

    Random::~Random() {};
} // random numbers
