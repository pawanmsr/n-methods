#if !defined(NEWTON)
#define NEWTON

#include <functional>

// overload for functions as arguments
namespace nm {
    const std::size_t MAX_ITERATIONS = 1e5;

    // f is twice differentiable function
    // f_prime is the derivative of f
    // functional programming paradigm
    // T is floating point type
    // delta is small
    template<typename T>
    T newton(std::function<T(T)> &f, std::function<T(T)> &f_prime,
        T delta = T(0.01), T x = T(0.0), std::size_t iterations = MAX_ITERATIONS);
} // namespace nm

#endif // NEWTON
