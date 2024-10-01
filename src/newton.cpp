#include <newton.hpp>

#include <cassert>

namespace nm
{
    // one dimensional
    // refer quadratic convergence, concave and convex functions
    // possible oscillations, multiplicity
    template<typename T>
    T newton(std::function<T(T)> &f, std::function<T(T)> &f_prime,
        const T delta, T x, std::size_t iterations) {
            // add proof of convergence
            assert(iterations > 0);
            delta = std::abs(delta);
            
            do {
                if (f(x) == 0 and f_prime(x) == 0)
                    x = f(iterations);

                T x_n = x - f(x) / f_prime(x);
                T epsilon = std::abs(x - x_n);
                x = x_n;
            } while (epsilon > delta and --iterations);
            
            return x;
        }
} // namespace nm
