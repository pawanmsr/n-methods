#if !defined(COMBINATORICS)
#define COMBINATORICS

#include <modulo_operations.hpp>

#include <vector>

namespace nm
{
    template<typename T>
    bool next_permutation(std::vector<T>& permutation);

    template<typename T>
    class PnC : public Arithmetic<T> {
    private:
        T mod;
        std::vector<T> factorial;
        std::vector<T> factorial_inverse;
    public:
        PnC(std::size_t n, const T mod);
        T get_factorial(std::size_t n);
        T get_factorial_inverse(std::size_t n);
        T nPr(std::size_t n, std::size_t r);
        T nCr(std::size_t n, std::size_t r);
        ~PnC();
    };
} // namespace nm

#endif // COMBINATORICS
