#include <random.hpp>

#include <chrono>

namespace nm {
    Random::Random() {
        this->n = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    }

    Random::Random(int32_m s) {
        this->n = s;
    }

    inline std::size_t Random::number(std::size_t xr) {
        return this->number(0, xr);
    }

    std::size_t Random::number(std::size_t xl, std::size_t xr) {
        std::size_t mod = xr - xl;
        int32_m p = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        this->n *= p;

        return int(this->n) % mod;
    }

    Random::~Random() {};
} // random numbers
