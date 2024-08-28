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
        PnC(T n, const T mod_prime);
        T get_factorial(T n);
        T get_factorial_inverse(T n);
        T nPr(T n, T r);
        T nCr(T n, T r);
        ~PnC();
    };
} // namespace nm

#endif // COMBINATORICS
