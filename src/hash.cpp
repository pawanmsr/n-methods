#include <hash.hpp>

#include <modulo.hpp>

namespace nm
{
    template<typename T>
    Linear<T>::Linear(std::size_t mod) : m(mod) {
    }

    template<typename T>
    T hash(T x) {
        return T(0);
    }
    
    template<typename T>
    Linear<T>::~Linear() {
    }
} // namespace nm
