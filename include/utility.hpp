#if !defined(UTILS)
#define UTILS

#include <functional>

namespace nm {
    // default arguments and functions

    template<class T>
    std::function<bool(T&, T&)> default_compare = [](T& a, T& b) {
        return a < b;
    };
}

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

    template<class T>
    struct Node {
        T key;
        Node<T>* llink;
        Node<T>* rlink;
        std::function<bool(T&, T&)> compare;

        bool operator < (const Node* n) {
            if (not n) return true;
            return compare(this->key, n->key);
        };

        Node(T k) : key(k), llink(NULL), rlink(NULL), compare(default_compare<T>) {};
        Node(T k, Node* a, Node* b) : key(k), llink(a), rlink(b), compare(default_compare<T>) {};
        
        Node(T k, std::function<bool(T&, T&)> c) :
            key(k), llink(NULL), rlink(NULL), compare(c) {};
        Node(T k, Node* a, Node* b, std::function<bool(T&, T&)> c) :
            key(k), llink(a), rlink(b), compare(c) {};
    };
}

namespace nm {
    // custom simple hash functions that may come handy
    // // add comments on possibility of hash collision
    // // add comments on collision resolution
}

#endif // UTILS
