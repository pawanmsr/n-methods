#if !defined(COMBINATORICS)
#define COMBINATORICS

#include <vector>

namespace nm
{
    template<typename T>
    bool next_permutation(std::vector<T>& permutation);

    template<typename T>
    class PnC {
    private:
        T mod;
        std::vector<T> factorial;
        std::vector<T> factorial_inverse;
    public:
        PnC(size_t n, const T mod_prime);
        T get_factorial(size_t n);
        T get_factorial_inverse(size_t n);
        T nPr(size_t n, size_t r);
        T nCr(size_t n, size_t r);
        ~PnC();
    };
} // namespace nm

#endif // COMBINATORICS
