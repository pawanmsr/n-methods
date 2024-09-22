#if !defined(INTERPOLATION)
#define INTERPOLATION

#include <vector>

namespace nm
{
    template<typename T>
    class Spline
    {
    private:
        std::vector<vector<T> > coefficients;
        std::vector<pair<T, T> > bounds;
    public:
        // bounds is expected to be sorted
        // coefficients and bounds correspond
        Spline(std::vector<std::vector<T> > &coefficients, std::vector<std::pair<T, T> > &bounds);
        ~Spline();
    };
    
} // namespace nm


#endif // INTERPOLATION