#if !defined(UTILS)
#define UTILS

// NO IMPORTS (OR INCLUDES) //

namespace nm {
    // T is type of data to query on
    template<class T>
    struct Integrator {
        T identity;

        // Also modify in update_tree and propagate
        T assign(T data) {
            // Add arguments and math
            // for flexibility and functionality.
            // Must have associative and commutative
            //  (and optionally distributive) properties.
            return data;
        }

        T integrate(T a, T b) {
            // Replace with operation(s) on a and b.
            return identity;
        }

        Integrator() : identity(0) {};
        Integrator(T i) : identity(i) {};
    };
    // default arguments and functions
    // custom simple hash functions that may come handy
    // // add comments on possibility of hash collision
    // // add comments on collision resolution
}

#endif // UTILS
