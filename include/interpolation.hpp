#if !defined(INTERPOLATION)
#define INTERPOLATION

#include <utility>
#include <vector>
#include <functional>

// TODO: #include <stdfloat>

namespace nm {
    class SLE {
        private:
            std::size_t n;
            std::vector<std::vector<long double> > A;
        public:
            SLE() {this->n = -1;};
            SLE(std::vector<std::vector<long double> > matrix);
            SLE(std::size_t nr, std::size_t nc);
            void add_row(std::vector<long double> row);
            ~SLE();
    };
    
    SLE::~SLE() {}
}

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
    
} // namespace nm


#endif // INTERPOLATION
