#if !defined(INTERPOLATION)
#define INTERPOLATION

#include <utility>
#include <vector>
#include <functional>

namespace nm
{
    template<typename T>
    std::function<T(T)> polynomial(const std::vector<T> &coefficients);

    template<typename T>
    class Spline
    {
    private:
        std::vector<std::vector<T> > coefficients;
        std::vector<std::pair<T, T> > bounds;
    public:
        // bounds is expected to be sorted
        // coefficients and bounds correspond
        Spline(std::vector<std::vector<T> > &coefficients,
            std::vector<std::pair<T, T> > &bounds);
        ~Spline();
    };
    
} // namespace nm


#endif // INTERPOLATION
