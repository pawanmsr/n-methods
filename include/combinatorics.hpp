#if !defined(COMBINATORICS)
#define COMBINATORICS

#include <vector>

namespace nm
{
    template<typename T>
    bool next_permutation(std::vector<T>& permutation);

    template<typename T>
    class PnC
    {
    private:
        std::vector<T> factorial;
    public:
        PnC(T n);
        ~PnC();
    };
} // namespace nm

#endif // COMBINATORICS
