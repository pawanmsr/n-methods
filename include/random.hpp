#if !defined(RANDOM)
#define RANDOM

#include <cstdint>

#include <modulo.hpp>

namespace nm {
    /*
     * X_{L} and X_{R} are same terminology as in
     *   Surreal Numbers, Knuth.
     *
     * TODO: generate floating points numbers.
     *  by concatenating number from 0-9.
     */
    class Random {
        private:
            int32_m n;
        public:
            Random();
            Random(int32_m s);
            std::size_t number(std::size_t xr);
            std::size_t number(std::size_t xl, std::size_t xr);
            ~Random();
    }
} // random numbers


#endif // RANDOM
