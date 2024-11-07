#if !defined(UTILS)
#define UTILS

#include <cstdint>
#include <utility>
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
            //  for flexibility and functionality.
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


    template<class C>
    struct Link {
        C* link = NULL;

        std::size_t size() {
            if (link) _size = link->size();
            else _size = 0;
            
            return _size;
        }

        std::int16_t height() {
            if (link) _height = link->height();
            else _height = 0;
            
            return _height;
        }

        void operator = (C* n) {
            link = n;
            size();
            height();
        }

        operator C* () {
            return link;
        }

        Link() : link(NULL), _size(0), _height(0) {};
        Link(C* n) : link(n) {
            size();
            height();
        };

        private:
        std::size_t _size = 0;
        std::int16_t _height = 0;
    };

    /*
     * Node contains key, llink, rlink, info.
     * Terminology from TAOCP.
     */
    template<class T, class U>
    struct Node {
        U info;
        Link<Node<T, U> > llink = NULL;
        Link<Node<T, U> > rlink = NULL;

        bool operator < (Node n) {
            return compare(key, n.key);
        }

        bool operator > (Node n) {
            return compare(n.key, key);
        }

        bool operator == (Node n) {
            return key == n.key;
        }

        bool operator < (T x) {
            return compare(key, x);
        }

        bool operator > (T x) {
            return compare(x, key);
        }

        bool operator == (T x) {
            return key == x;
        }

        operator T () const {
            return key;
        }

        void mark() {
            marker = true;
        }

        std::size_t size() {
            return llink.size() + rlink.size() + 1;
        }

        std::int16_t height() {
            return std::max(llink.height(), rlink.height()) + 1;
        }

        std::int16_t balance() {
            return rlink.height() - llink.height();
        }

        bool marked() {
            return marker;
        }

        void unmark() {
            marker = false;
        }

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
        T key;
        bool marker;
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
