#include <newton.hpp>

#include <cassert>

namespace nm {
    // one dimensional
    // refer quadratic convergence, concave and convex functions
    // possible oscillations, multiplicity
    template<typename T>
    T newton(std::function<T(T)> &f, std::function<T(T)> &f_prime,
        T delta, T x, std::size_t iterations) {
            // add proof of convergence
            assert(iterations > 0);
            delta = std::abs(delta);
            T epsilon = delta + 1.0;

            while (epsilon > delta and iterations--) {
                // TODO: add resolution for inflection
                // point and extremum
                if (f(x) == 0 and f_prime(x) == 0)
                    break;

                T x_n = x - f(x) / f_prime(x);
                T epsilon = std::abs(x - x_n);
                x = x_n;
            }

            return x;
        }
} // namespace nm

template double nm::newton<double>(std::function<double(double)>&,
    std::function<double(double)>&, double, double, unsigned long);
template long double nm::newton<long double>(std::function<long double(long double)>&,
    std::function<long double(long double)>&, long double, long double, unsigned long);
