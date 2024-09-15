#if !defined(NEWTON)
#define NEWTON

#include <functional>

// overload for functions as arguments
namespace nm
{
    // f is twice differentiable function
    // f_prime is the derivative of f
    // functional programming paradigm
    // T is floating point type
    // delta is small
    template<typename T>
    T newton(std::function<T(T&)> &f, std::function<T(T&)> &f_prime,
        const T delta = T(0.01), T x = T(0.0));
} // namespace nm

#endif // NEWTON
