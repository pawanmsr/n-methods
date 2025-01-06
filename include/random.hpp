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
     * TODO: generate floating point numbers
     *  by concatenating sequence of numbers \in [0, 9].
     * TODO: generate negative numbers by adding subtraction
     *  sign.
     */
    class Random {
        private:
            int32_m n;
            int32_m p;
        protected:
            uint64_t query_clock();
        public:
            Random();
            ~Random();

            Random(std::uint32_t s);
            // pseudo random initialization
            Random(std::uint32_t s, std::uint32_t p);
            
            std::uint32_t number(std::uint32_t xr);
            std::uint32_t number(std::uint32_t xl, std::uint32_t xr);
    };
} // random numbers


#endif // RANDOM
