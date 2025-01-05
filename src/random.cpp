#include <random.hpp>

#include <chrono>

namespace nm {
    Random::Random() {
        this->n = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        this->p = 0;
    }

    Random::Random(std::size_t s) {
        this->n = s;
        this->p = 0;
    }

    Random::Random(std::size_t s, std::size_t p) {
        this->n = s;
        this->p = p;
    }

    inline std::size_t Random::number(std::size_t xr) {
        return this->number(0, xr);
    }

    std::size_t Random::number(std::size_t xl, std::size_t xr) {
        std::size_t mod = xr - xl + 1;
        
        int32_m p = this->p;
        if (not int(p)) p = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        this->n *= p;

        return xl + int(this->n) % mod;
    }

    Random::~Random() {};
} // random numbers
