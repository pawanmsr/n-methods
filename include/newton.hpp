#if !defined(NEWTON)
#define NEWTON

#include <functional>

// overload for functions as arguments
namespace nm
{
    // f is twice differentiable function
    // f_prime is the derivative of f
    // delta is small
    // functional programming paradigm
    template<typename T>
    T newton(std::function<T(T&)> &f, std::function<T(T&)> &f_prime, const T delta);
} // namespace nm

#endif // NEWTON
