#if !defined(UTILS)
#define UTILS

#include <functional>

namespace nm {
    // default arguments and functions

    template<typename T>
    std::function<bool(T&, T&)> default_compare = [](T& a, T& b) {
        return a < b;
    };

    // custom simple hash functions that may come handy
    // // add comments on possibility of hash collision
    // // add comments on collision resolution
}

#endif // UTILS
