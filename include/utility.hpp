#if !defined(UTILS)
#define UTILS

#include <functional>

namespace nm {
    template<class T>
    struct Node {
        T key;
        Node* llink, rlink;
        std::function<bool(T&, T&)> compare;

        bool operator < (const Node* a, const Node* b) {
            if (not a or not b) return true;
            return compare(a->key, b->key);
        };

        Node(T k) : key(k), llink(NULL), rlink(NULL), compare(default_compare) {};
        Node(T k, Node* a, Node* b) : key(k), llink(a), rlink(b), compare(default_compare) {};
        
        Node(T k, std::function<bool(T&, T&)> c) :
            key(k), llink(NULL), rlink(NULL), compare(c) {};
        Node(T k, Node* a, Node* b, std::function<bool(T&, T&)> c) :
            key(k), llink(a), rlink(b), compare(c) {};
    };

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

    template<class T>
    std::function<bool(T&, T&)> default_compare = [](T& a, T& b) {
        return a < b;
    };

    // custom simple hash functions that may come handy
    // // add comments on possibility of hash collision
    // // add comments on collision resolution
}

#endif // UTILS
