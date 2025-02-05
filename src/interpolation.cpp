#include <interpolation.hpp>

#include <sort.hpp>

#include <cstdint>

namespace nm {
    // Coefficients are ordered from left to right,
    // with first being a constant.
    template<typename T>
    std::function<T(T)> polynomial(const std::vector<T> &coefficients) {
        return [&](T x) {
            T term = 1;
            T result = 0;

            for (const T &coefficient : coefficients) {
                result += term * coefficient;
                term *= x;
            }

            return result;
        };
    }

    template<typename T>
    Spline<T>::Spline(std::vector<std::vector<T> > &coefficients,
        std::vector<std::pair<T, T> > &bounds) : coefficients(coefficients), bounds(bounds) {
            assert(this->bounds.size() == this->coefficients.size());

            for (std::pair<T, T> &bound : bounds)
                if (bound.first > bound.second)
                    swap(bound.first, bound.second);
            
            auto compare = [](std::pair<T, T> &a, std::pair<T, T> &b) {
                return a.first < b.first;
            };

            const std::size_t n = bounds.size();
            MultiSort<T, std::int32_t> ms(n);
            ms.sort(bounds, compare);
            ms.apply(coefficients);

            // Figure out how to check overlap for floating points?
            // Bounds must not overlap because they will lead to ambiguity.
            // Within certain degree of error tolerance, maybe 6 decimal places or less (2^(23 - 1))?
        }
} // namespace nm

template std::function<double(double)>
    nm::polynomial<double>(const std::vector<double>&);
template std::function<long double(long double)>
    nm::polynomial<long double>(const std::vector<long double>&);
