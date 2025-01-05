#if !defined(RANDOM)
#define RANDOM

#include <cstdint>

#include <modulo.hpp>

namespace nm {
    /* 
     * All numbers \in [xl, xr].
     * X_{L} and X_{R} are terminology from
     *   Surreal Numbers, Knuth.
     *
     * TODO: generate floating points numbers
     *  by concatenating sequence of numbers \in [0, 9].
     * TODO: generate negative numbers by adding subtraction
     *  sign.
     */
    class Random {
        private:
            int32_m n;
            int32_m p;
        public:
            Random();
            ~Random();

            Random(std::size_t s);
            // pseudo random initialization
            Random(std::size_t s, std::size_t p);
            
            std::size_t number(std::size_t xr);
            std::size_t number(std::size_t xl, std::size_t xr);
    };
} // random numbers


#endif // RANDOM
