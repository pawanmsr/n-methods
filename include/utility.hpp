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
        Node<T, U>* llink = NULL;
        Node<T, U>* rlink = NULL;

        bool operator < (Node* n) {
            if (not n) return true;
            return compare(this->key, n->key);
        };

        bool operator > (Node* n) {
            if (not n) return true;
            return compare(n->key, this->key);
        };

        bool operator == (Node* n) {
            if (not n) return false;
            return this->key == n->key;
        };

        bool operator < (T x) {
            return compare(this->key, x);
        };

        bool operator > (T x) {
            return this->compare(x, this->key);
        };

        bool operator == (T x) {
            return this->key == x;
        };

        std::size_t size() {
            if (not this->lsize and this->llink)
                this->lsize = this->llink->size();
            if (not this->rsize and this->rlink)
                this->rsize = this->rlink->size();
            return this->lsize + this->rsize + 1;
        };

        Node(T k) : key(k) {};

        Node(T k, U i) : key(k), info(i) {};
        
        Node(T k, U i, Node* a, Node* b) :
            key(k), info(i), llink(a), rlink(b) {};
        
        Node(T k, U i, std::function<bool(T&, T&)> c) :
            key(k), info(i), compare(c) {};
        
        Node(T k, U i, Node* a, Node* b, std::function<bool(T&, T&)> c) :
            key(k), info(i), llink(a), rlink(b), compare(c) {};
        
        private:
        std::size_t lsize = 0;
        std::size_t rsize = 0;
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
