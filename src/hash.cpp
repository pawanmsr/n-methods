#include <hash.hpp>

namespace nm
{
    template<typename T>
    Linear<T>::Linear(std::size_t mod_prime) : Arithmetic<T>::Arithmetic(mod_prime) {
    }

    template<typename T>
    std::size_t Linear<T>::hash(T x) {
        // use integer or string polymorph
        return 0;
    }

    template<typename T>
    std::size_t Linear<T>::hash(std::string s) {
        // implement uniform hash
        return 0;
    }

    template<typename T>
    std::size_t Linear<T>::hash(std::int64_t s) {
        // implement hash
        return 0;
    }
    
    template<typename T>
    Linear<T>::~Linear() {
    }
} // namespace nm
