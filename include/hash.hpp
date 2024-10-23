#if !defined(HASH)
#define HASH

#include <string>
#include <cstdint>

#include <modulo.hpp>

namespace nm
{

    template<typename T>
    class Linear : public Arithmetic<T> {
    private:

    protected:
        std::size_t hash(std::string s);
        std::size_t hash(std::int64_t n);

    public:
        Linear(std::size_t mod_prime);
        std::size_t hash(T x);
        ~Linear();
    };
    
} // namespace nm


#endif // HASH
