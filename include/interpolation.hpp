#if !defined(INTERPOLATION)
#define INTERPOLATION

#include <utility>
#include <vector>
#include <functional>
#include <cstdint>

// TODO: #include <stdfloat>

namespace nm {
    const long double PRECISION = 1e-8;
    enum classification {
        zero,
        one,
        infinite,

        // zero: no solution
        // one: one solution
        // infinite: many solutions
    };

    enum solver {
        none, // unsolved
        gauss,

        // others
    };

    class SLE {
        private:
            std::size_t n;
            std::vector<std::vector<long double> > A;
            std::vector<std::uint32_t> pivots;

            solver applied;
            solver gauss();

        protected:
            void normalize();
            std::uint32_t pivot(std::size_t column, std::size_t row = 0,
                long double threshold = PRECISION);
            
            // add solvers
            void cramer();
            void fourier();

            void singular_value();
            void lu();
            void qr();
            
            // square positive definite
            void cholesky();

        public:
            SLE() {this->n = -1;};
            SLE(std::vector<std::vector<long double> > matrix);
            SLE(std::size_t nr, std::size_t nc);
            ~SLE() {};
            
            void add_row(std::vector<long double> row);
            classification solve(std::vector<long double> &x,
                long double threshold = PRECISION, solver use = solver::gauss);
            
            std::size_t rank();
            std::vector<long double> eigenvalues();
            
            // rank equals n
            long double determinant();
            SLE inverse();
    };
} // system of linear equations

// TODO: #include <stdfloat>

namespace nm {
    class SLE {
        private:
            std::size_t n;
            std::vector<std::vector<long double> > A;
        protected:
            void normalize();
            
            // Add solvers
            void gauss();
            void cramer();
            void fourier();
        public:
            SLE() {this->n = -1;};
            SLE(std::vector<std::vector<long double> > matrix);
            SLE(std::size_t nr, std::size_t nc);
            void add_row(std::vector<long double> row);
            std::size_t rank();
            std::vector<long double> eigenvalues();
            
            // rank equals n
            long double determinant();
            SLE inverse();

            ~SLE() {};
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
