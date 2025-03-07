#include <interpolation.hpp>

#include <sort.hpp>

#include <stdexcept>
#include <cassert>
#include <cstdlib>
#include <utility>

namespace nm {
    SLE::SLE(std::vector<std::vector<long double> > matrix) {
        this->n = -1;
        this->A.clear();
        this->pivots.clear();

        for (std::vector<long double> row : matrix)
            this->add_row(row);
    }
    
    SLE::SLE(std::size_t nr, std::size_t nc) : n(nc) {
        this->A.reserve(nr);
        this->pivots.reserve(this->n);
    }

    void SLE::add_row(std::vector<long double> row) {
        if (not row.size() or (this->n > 0 and row.size() != this->n))
            throw std::length_error("incorrect number of coefficients");
        
        if (this->n == -1 and row.size()) {
            this->n = row.size();
            this->pivots.assign(this->n, -1);
        }

        this->A.push_back(row);
    }

    // returns -1 if pivot is not found
    std::uint32_t SLE::pivot(std::size_t column, std::size_t row, long double threshold) {
        std::size_t m = this->A.size();
        assert(column < this->n);

        if (row == 0)
            while (row < m and std::abs(this->A[row][column]) > threshold)
                row++;

        std::size_t i = row;
        std::uint32_t pivot = -1;
        while (i < m) {
            if (std::abs(this->A[i][column]) > threshold and (pivot == -1 or
                std::abs(this->A[pivot][column]) > std::abs(this->A[i][column])))
                    pivot = i;
            i++;
        }

        if (pivot >= 0) {
            std::swap(this->A[pivot], this->A[row]);
            this->pivots[column] = row;
        }
        
        return pivot;
    }

    void SLE::gauss() {
        std::size_t m = this->A.size();
        this->pivots.assign(this->n, -1);

        std::size_t row = 0;
        std::size_t column = 0;
        while (row < m and column < this->n) {
            std::uint32_t pivot = this->pivot(column, row);
            if (pivot < 0) continue;

            for (std::size_t i = 0; i < m; i++) {
                if (i == row) continue;

                double multiplier = this->A[i][column] / this->A[row][column];
                for (std::size_t j = 0; j < this->n; j++)
                    this->A[i][j] -= this->A[row][column] * multiplier;
            }

            row++;
        }
    }

    classification nm::SLE::solve(std::vector<long double> &x, long double threshold) {
        std::size_t m = this->A.size();
        assert(x.size() == m);

        for (std::size_t column = 0; column < this->n; column++) {
            if (this->pivots[column] != -1)
                x[column] = x[this->pivots[column]] / this->A[this->pivots[column]][column];
        }

        for (std::size_t row = 0; row < m; row++)
            if (this->pivots[row] == -1) return classification::infinite;

        for (std::size_t row = 0; row < m; row++) {
            long double product = 0;
            
            for (std::size_t column = 0; column < this->n; column++) {
                product += x[column] * this->A[row][column];
                if (std::abs(product - x[row]) > threshold)
                    return classification::zero;
            }
        }
        
        return classification::one;
    }
} // 2d matrix

namespace nm {
    // Coefficients are ordered from left to right,
    //  with first being a constant.
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
