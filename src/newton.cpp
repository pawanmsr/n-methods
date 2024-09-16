#include <newton.hpp>

namespace nm
{
    // one dimensional
    // refer quadratic convergence, concave and convex functions
    // possible oscillations, multiplicity
    template<typename T>
    T newton(std::function<T(T&)> &f, std::function<T(T&)> &f_prime, const T delta, T x) {
        // add proof of convergence
        
        delta = std::abs(delta);
        
        do {
            T x_n = x - f(x) / f_prime(x);
            T epsilon = std::abs(x - x_n);
            x = x_n;
        } while (epsilon > delta);
        
        return x;
    }
} // namespace nm
