#if !defined(INTERPOLATION)
#define INTERPOLATION

#include <utility>
#include <vector>
#include <functional>
#include <cstdint>

// TODO: #include <stdfloat>

namespace nm {
    const long double PRECISION = 1e-8;

    class SLE {
        private:
            enum classification {
                zero,
                one,
                infinite
            };

            std::size_t n;
            std::vector<std::vector<long double> > A;
            std::vector<long double> x;
            std::vector<std::uint32_t> pivots;
        protected:
            void normalize();
            std::uint32_t pivot(std::size_t column, std::size_t row = 0,
                long double threshold = PRECISION);
            
            // add solvers
            void gauss();
            void cramer();
            void fourier();
        public:
            SLE() {this->n = -1;};
            SLE(std::vector<std::vector<long double> > matrix);
            SLE(std::size_t nr, std::size_t nc);
            ~SLE() {};
            
            void add_row(std::vector<long double> row);
            
            std::size_t rank();
            std::vector<long double> eigenvalues();
            
            // rank equals n
            long double determinant();
            SLE inverse();
    };
} // system of linear equations

namespace nm {
    template<typename T>
    std::function<T(T)> polynomial(const std::vector<T> &coefficients);

    template<typename T>
    class Spline {
        private:
            std::vector<std::vector<T> > coefficients;
            std::vector<std::pair<T, T> > bounds;
        public:
            // bounds is expected to be sorted
            // coefficients and bounds correspond
            Spline(std::vector<std::vector<T> > &coefficients,
                std::vector<std::pair<T, T> > &bounds);
            ~Spline() {};
    };
    
} // polynomials and spline


#endif // INTERPOLATION
