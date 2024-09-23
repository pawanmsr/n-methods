#include <interpolation.hpp>

#include <sort.hpp>

namespace nm
{
    template<typename T>
    Spline<T>::Spline(std::vector<std::vector<T> > &coefficients, std::vector<std::pair<T, T> > &bounds) : 
        this->coefficients(coefficients), this->bounds(bounds) {
            assert(this->bounds.size() == this->coefficients.size())

            for (std::pair<T, T> &bound : bounds)
                if (bound.first > bound.second)
                    swap(bound.first, bound.second);
            
            const int n = bounds.size();
            MultiSort<T, int32_t> ms(n);
            ms.sort(bounds, compare = [](std::pair<T, T> &a, std::pair<T, T> &b) {
                return a.first < b.first;
            }); ms.apply(coefficients);

            // Figure out how to check overlap for floating points?
            // Bounds must not overlap because they will lead to ambiguity.
            // Within certain degree of error tolerance, maybe 6 decimal places or less (2^(23 - 1))?
        }
    
    template<typename T>
    Spline<T>::~Spline() {
    }
} // namespace nm
