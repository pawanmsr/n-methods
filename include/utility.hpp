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


    /*
     * Node contains key, llink, rlink, info.
     * Terminology from TAOCP.
     */
    template<class T, class U>
    struct Node {
        T key;
        U info;
        std::size_t lsize = 0;
        std::size_t rsize = 0;
        Node<T, U>* llink = NULL;
        Node<T, U>* rlink = NULL;

        void operator = (Node n) {
            key = n.key;
            info = n.info;
            llink = n.llink;
            rlink = n.rlink;
            lsize = n.lsize;
            rsize = n.rsize;
        }

        bool operator < (Node n) {
            return compare(key, n.key);
        };

        bool operator > (Node n) {
            return compare(n.key, key);
        };

        bool operator == (Node n) {
            return key == n.key;
        };

        bool operator < (T x) {
            return compare(key, x);
        };

        bool operator > (T x) {
            return compare(x, key);
        };

        bool operator == (T x) {
            return key == x;
        };

        std::size_t size() {
            if (not lsize and llink)
                lsize = llink->size();
            if (not rsize and rlink)
                rsize = rlink->size();
            
            return lsize + rsize + 1;
        };

        Node(T k) : key(k) {};

        Node(T k, Node* a, Node* b) :
            key(k), llink(a), rlink(b) {};
        
        Node(T k, std::function<bool(T&, T&)> c) :
            key(k), compare(c) {};
        
        Node(T k, Node* a, Node* b, std::function<bool(T&, T&)> c) :
            key(k), llink(a), rlink(b), compare(c) {};

        Node(T k, U i) : key(k), info(i) {};
        
        Node(T k, U i, Node* a, Node* b) :
            key(k), info(i), llink(a), rlink(b) {};
        
        Node(T k, U i, std::function<bool(T&, T&)> c) :
            key(k), info(i), compare(c) {};
        
        Node(T k, U i, Node* a, Node* b, std::function<bool(T&, T&)> c) :
            key(k), info(i), llink(a), rlink(b), compare(c) {};
        
        private:
        std::function<bool(T&, T&)> compare
            = default_compare<T>;
    };
}

namespace nm {
    // custom simple hash functions that may come handy
    // // add comments on possibility of hash collision
    // // add comments on collision resolution
}

#endif // UTILS
