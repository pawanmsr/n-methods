#include <trees.hpp>

#include <utility.hpp>

#include <cassert>
#include <stdexcept>

namespace nm {
    // !? lookout for // modify // in popagate function
    // and assignment in update_tree function
    // More complex problems may require overhaul.
    template <class T, class U>
    SegmentTree<T, U>::SegmentTree(std::vector<T> &data, U *integrator_struct) : 
        integrator(integrator_struct) {
            this->n = 1;
            while (this->n < std::int32_t(data.size()))
                this->n *= 2;
            
            data.resize(this->n, this->integrator->identity);
            
            this->tree.resize(this->n * 2);
            this->auxiliary.resize(this->n * 2, this->integrator->identity); // modify //
            // auxiliary holds delayed range updates

            this->construct(data, 0, this->n - 1, 1);
        }

    // modify //
    // propagate needs to be customized according to requirement
    template <class T, class U>
    bool SegmentTree<T, U>::propagate(std::int32_t i) {
        if (this->auxiliary[i] == this->integrator->identity) return false;

        // lazy propagation
        this->tree[i * 2] = this->integrator->assign(this->auxiliary[i]);     // modify //
        this->tree[i * 2 + 1] = this->integrator->assign(this->auxiliary[i]); // modify //
        this->tree[i] = this->integrator->integrate(this->tree[i * 2], this->tree[i * 2 + 1]);

        // FIXME: this is perhaps not needed when i * 2
        //  is greater than or equal to this->n
        this->auxiliary[i * 2] = this->integrator->assign(this->auxiliary[i]);     // modify //
        this->auxiliary[i * 2 + 1] = this->integrator->assign(this->auxiliary[i]); // modify //

        this->auxiliary[i] = this->integrator->identity;
        return true;
    }

    template <class T, class U>
    T SegmentTree<T, U>::query_tree(std::int32_t lo, std::int32_t hi,
        std::int32_t tlo, std::int32_t thi, std::int32_t i) {
            if (lo > hi) return this->integrator->identity;
            if (lo == tlo and hi == thi) return this->tree[i];

            this->propagate(i);

            std::int32_t mid = tlo + (thi - tlo) / 2;
            return this->integrator->integrate(this->query_tree(lo, std::min(mid, hi), tlo, mid, i * 2),
                this->query_tree(std::max(lo, mid + 1), hi, mid + 1, thi, i * 2 + 1));
        }

    // position is index in zero indexed sequence
    template <class T, class U>
    T SegmentTree<T, U>::update_tree(T value, std::int32_t position,
        std::int32_t lo, std::int32_t hi, std::int32_t i) {
            if (lo == hi) return this->tree[i] = this->integrator->assign(value); // modify //

            std::int32_t mid = lo + (hi - lo) / 2;
            if (position <= mid) this->update_tree(value, position, lo, mid, i * 2);
            else this->update_tree(value, position, mid + 1, hi, i * 2 + 1);

            return this->tree[i] = this->integrator->integrate(this->tree[i * 2],
                this->tree[i * 2 + 1]);
        }

    template <class T, class U>
    T SegmentTree<T, U>::update_tree(T value, std::int32_t lo, std::int32_t hi,
        std::int32_t tlo, std::int32_t thi, std::int32_t i) {
        if (lo > hi) return this->integrator->identity;

        if (lo == tlo and hi == thi) {
            this->auxiliary[i] = this->integrator->assign(value);   // modify //
            return this->tree[i] = this->integrator->assign(value); // modify //
        } else {
            this->propagate(i);

            std::int32_t mid = tlo + (thi - tlo) / 2;
            this->update_tree(value, lo, std::min(mid, hi), tlo, mid, i * 2);
            this->update_tree(value, std::max(lo, mid + 1), hi, mid + 1, thi, i * 2 + 1);
            
            return this->tree[i] = this->integrator->integrate(this->tree[i * 2],
                this->tree[i * 2 + 1]);
        }
    }

    // left and right are indices in zero indexed sequence
    template <class T, class U>
    T SegmentTree<T, U>::query(std::int32_t left, std::int32_t right) {
        assert(left >= 0); assert(right < this->n);
        return this->query_tree(left, right, 0, this->n - 1, 1);
    }

    // position is index in zero indexed sequence
    template <class T, class U>
    T SegmentTree<T, U>::update(T value, std::int32_t position) {
        assert(position >= 0 and position < this->n);
        return update_tree(value, position, 0, this->n - 1, 1);
    }

    // left and right are indices in zero indexed sequence
    // !? modify assignment in update_tree protected method
    template <class T, class U>
    T SegmentTree<T, U>::update(T value, std::int32_t left, std::int32_t right) {
        assert(left >= 0); assert(right < this->n);
        return update_tree(value, left, right, 0, this->n - 1, 1);
    }

    template <class T, class U>
    void SegmentTree<T, U>::construct(std::vector<T> &data,
        std::int32_t lo, std::int32_t hi, std::int32_t i) {
            if (lo == hi) this->tree[i] = this->integrator->assign(data[lo]); // modify //
            else {
                std::int32_t mid = lo + (hi - lo) / 2;
                this->construct(data, lo, mid, i * 2);
                this->construct(data, mid + 1, hi, i * 2 + 1);

                this->tree[i] = this->integrator->integrate(this->tree[i * 2],
                    this->tree[i * 2 + 1]);
            }
        }

    template <class T, class U>
    SegmentTree<T, U>::~SegmentTree() {}
} // namespace nm

template class nm::SegmentTree<int, nm::Integrator<int>>;

// Search Trees
namespace nm {   
    template <class C, class T, class U>
    SearchTree<C, T, U>::SearchTree(std::function<bool(T&, T&)> compare) : 
        compare(compare) {
            this->root = NULL;
        }
    
    template <class C, class T, class U>
    std::size_t SearchTree<C, T, U>::size() {
        return this->root->size();
    }
    
    template <class C, class T, class U>
    C* SearchTree<C, T, U>::node(T x, bool return_parent, bool mark) {
        C* parent = NULL;
        C* seeker = this->root;
        
        while (seeker) {
            if (mark) seeker->mark();
            
            if (*seeker > x) {
                if (seeker->llink) {
                    parent = seeker;
                    seeker = seeker->llink;
                } else break;
            } else if (*seeker < x) {
                if (seeker->rlink) {
                    parent = seeker;
                    seeker = seeker->rlink;
                } else break;
            } else break;
        }

        if (return_parent) return parent;
        return seeker;
    }

    template <class C, class T, class U>
    C* SearchTree<C, T, U>::create(T x) {
        C* n = this->node(x, false, true);
        if (n and *n == x) return n;

        if (not n) {
            this->root = new C(x, this->compare);
            return this->root;
        }
        
        C* ni = new C(x, this->compare);
        if (*n < *ni) n->rlink = ni;
        else n->llink = ni;
        n = ni;

        return n;
    }

    template <class C, class T, class U>
    C* SearchTree<C, T, U>::element(std::size_t k, C* n) {
        if (k > n->size()) return NULL;
        if (not --k) return n;
        
        if (n->llink and k > n->llink.size())
            return element(k - n->llink.size(), n->rlink);
        else return element(k, n->llink);
    }

    template <class C, class T, class U>
    U SearchTree<C, T, U>::element(std::size_t k) {
        C* n = element(k, this->root);
        if (not n) throw std::runtime_error("range violation");
        return n->info;
    }

    template <class C, class T, class U>
    C* SearchTree<C, T, U>::successor(C* seeker, bool return_parent) {
        C* parent = NULL;
        
        while (seeker->llink) {
            parent = seeker;
            seeker = seeker->llink;
        }

        if (return_parent) return parent;
        return seeker;
    }

    template <class C, class T, class U>
    C* SearchTree<C, T, U>::predecessor(C* seeker, bool return_parent) {
        C* parent = NULL;

        while (seeker->rlink) {
            parent = seeker;
            seeker = seeker->rlink;
        }

        if (return_parent) return parent;
        return seeker;
    }

    template <class C, class T, class U>
    U SearchTree<C, T, U>::insert(T x, U y) {
        C* n = this->create(x);
        return n->info = y;
    }

    template <class C, class T, class U>
    bool SearchTree<C, T, U>::insert(T x) {
        C* n = this->create(x);
        return *n == x;
    }

    template <class C, class T, class U>
    bool SearchTree<C, T, U>::remove(T x) {
        C* parent = this->node(x, true, true);
        
        bool left = false;
        C* n = this->root;
        if (parent and parent->llink and *parent->llink == x) {
            n = parent->llink;
            left = true;
        } else if (parent and parent->rlink and *parent->rlink == x)
            n = parent->rlink;
        
        if (not n or *n != x) return false;

        auto re_link = [&](C* link) {
            if (not parent) {
                this->root = link;
                if (this->root) this->root->mark();
            } else parent->mark();
            
            if (parent and left) parent->llink = link;
            if (parent and not left) parent->rlink = link;
        };
        
        if (not n->llink and not n->rlink) re_link(NULL);
        else if (not n->llink) re_link(n->rlink);
        else if (not n->rlink) re_link(n->llink);
        else {
            C* parent_prime = successor(n->rlink, true);

            C* n_prime = parent_prime;
            if (not n_prime) {
                n_prime = n->rlink;
                n->rlink = n_prime->rlink;
            } else if (parent_prime->llink) {
                n_prime = parent_prime->llink;
                parent_prime->llink = n_prime->rlink;
            }

            n_prime->llink = n->llink;
            n_prime->rlink = n->rlink;

            n_prime->mark();

            re_link(n_prime);
        }

        return true;
    }

    template <class C, class T, class U>
    bool SearchTree<C, T, U>::search(T x) {
        C* n = this->node(x);
        if (n and *n == x) return true;
        return false;
    }

    template <class C, class T, class U>
    U SearchTree<C, T, U>::obtain(T x) {
        C* n = this->node(x);
        if (*n == x) return n->info;

        throw std::runtime_error("non existent key");
    }

    template <class C, class T, class U>
    void SearchTree<C, T, U>::inorder(C* n, std::vector<T> &keys) {
        if (not n) return ;

        inorder(n->llink, keys);
        keys.push_back(*n);
        inorder(n->rlink, keys);
    }

    template <class C, class T, class U>
    void SearchTree<C, T, U>::preorder(C* n, std::vector<T> &keys) {
        if (not n) return ;

        keys.push_back(*n);
        preorder(n->llink, keys);
        preorder(n->rlink, keys);
    }

    template <class C, class T, class U>
    void SearchTree<C, T, U>::postorder(C* n, std::vector<T> &keys) {
        if (not n) return ;

        postorder(n->llink, keys);
        postorder(n->rlink, keys);
        keys.push_back(*n);
    }

    template <class C, class T, class U>
    std::vector<T> SearchTree<C, T, U>::keys() {
        std::vector<T> keys;
        inorder(this->root, keys);
        return keys;
    }
    
    template <class C, class T, class U>
    SearchTree<C, T, U>::~SearchTree() {
        // delete this;
    }
} // namespace nm

template class nm::SearchTree<nm::Node<int, int>, int, int>;

namespace nm {
    template <class C, class T, class U>
    AVL<C, T, U>::AVL(std::function<bool(T&, T&)> compare, std::int16_t balance_factor) :
        SearchTree<C, T, U>(compare), balance_factor(balance_factor) {
            if (this->balance_factor < -1 or this->balance_factor > 1)
                this->balance_factor = 0;
        }

    template <class C, class T, class U>
    C* AVL<C, T, U>::rotate_left(C* n) {
        C* right = n->rlink;
        if (not right) return n;

        n->rlink = right->llink;
        right->llink = n;

        return right;
    }

    template <class C, class T, class U>
    C* AVL<C, T, U>::rotate_right(C* n) {
        C* left = n->llink;
        if (not left) return n;
        
        n->llink = left->rlink;
        left->rlink = n;

        return left;
    }

    template <class C, class T, class U>
    C *AVL<C, T, U>::balance(C *n) {
        // TODO: try doing it iteratively too.
        if (not n or not n->marked()) return n;

        auto balanced = [&] (C* link, std::int16_t lcr = 0) {
            if (not link) return true;
            
            if (lcr == -1)
                return n->balance() >= this->balance_factor - 1;
            else if (lcr == 1)
                return n->balance() <= this->balance_factor + 1;
            
            return link->balance() >= this->balance_factor - 1
                and link->balance() <= this->balance_factor + 1;
        };

        auto marked = [] (C* link) {
            if (not link) return false;
            return link->marked();
        };

        if (marked(n->llink))
            n->llink = this->balance(n->llink);
        
        if (marked(n->rlink))
            n->rlink = this->balance(n->rlink);

        if (balanced(n)) n->unmark();

        if (not balanced(n, -1))
            return this->rotate_right(n);
        else if (not balanced(n, 1))
            return this->rotate_left(n);

        return n;
    }

    template <class C, class T, class U>
    U AVL<C, T, U>::insert(T x, U y) {
        y = SearchTree<C, T, U>::insert(x, y);
        this->root = this->balance(this->root);
        return y;
    }

    template <class C, class T, class U>
    bool AVL<C, T, U>::insert(T x) {
        bool inserted = SearchTree<C, T, U>::insert(x);
        this->root = this->balance(this->root);
        return inserted;
    }

    template <class C, class T, class U>
    bool AVL<C, T, U>::remove(T x) {
        bool removed = SearchTree<C, T, U>::remove(x);
        if (not removed) return false;

        this->root = this->balance(this->root);
        return true;
    }

    template <class C, class T, class U>
    AVL<C, T, U>::~AVL() {
    }
} // namespace nm

template class nm::AVL<nm::Node<int, int>, int, int>;
