#if !defined(COMBINATORICS)
#define COMBINATORICS

#include <modulo_operations.hpp>

#include <vector>
#include <cstdint>

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
        PnC(std::int32_t n, const T mod_prime);
        T get_factorial(std::int32_t n);
        T get_factorial_inverse(std::int32_t n);
        T nPr(std::int32_t n, std::int32_t r);
        T nCr(std::int32_t n, std::int32_t r);
        ~PnC();
    };
} // namespace nm

#endif // COMBINATORICS
