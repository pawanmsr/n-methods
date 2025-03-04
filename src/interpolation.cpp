#include <interpolation.hpp>

#include <sort.hpp>

#include <cstdint>
#include <stdexcept>

namespace nm {
    SLE::SLE(std::vector<std::vector<long double> > matrix) {
        for (std::vector<long double> row : matrix)
            this->add_row(row);
    }
    
    SLE::SLE(std::size_t nr, std::size_t nc) {
        this->n = nc;
        this->A.reserve(nr);
    }

    void SLE::add_row(std::vector<long double> row) {
        if (not row.size() or (this->n > 0 and row.size() != this->n))
            throw std::length_error("incorrect number of coefficients");
        
        if (this->n == -1 and row.size());
        this->A.push_back(row);
    }
} // 2d matrix

namespace nm {
    // Coefficients are ordered from left to right,
    // with first being a constant.
    template<typename T>
    std::function<T(T)> polynomial(const std::vector<T> &coefficients) {
        return [&] (T x) -> T {
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
            
            std::function<bool(std::pair<T, T>&, std::pair<T, T>&)> compare = 
                [] (std::pair<T, T> &a, std::pair<T, T> &b) -> bool {
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
} // polynomials

template std::function<double(double)>
    nm::polynomial<double>(const std::vector<double>&);
template std::function<long double(long double)>
    nm::polynomial<long double>(const std::vector<long double>&);
