// STLs //
#include <chrono>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <functional>

// NMethods //
#include <primes.hpp>
#include <exponentiation.hpp>
#include <gcd.hpp>
#include <sort.hpp>
#include <modulo.hpp>
#include <search.hpp>
#include <combinatorics.hpp>
#include <trees.hpp>
#include <union_find.hpp>
#include <utility.hpp>
#include <newton.hpp>
#include <interpolation.hpp>
#include <random.hpp>
#include <table.hpp>

// GTest //
#include <gtest/gtest.h>

// Constants
const int N_LOG = 1e5 + 1;
const int N_ROOT = 1e3 + 1;
const int N_CROOT = 1e2 + 1;
const int N_FACT = 10;
const int P = 9592;
const int E = 31;
const long long M = 1e9 + 7;

const char ASSERTION_REGEX[] = "Assertion.*failed";
const char BUILD_TYPE_IDENTIFIER[] = "CMAKE_BUILD_TYPE";
const char BUILD_TYPE[] = "Debug";
const char TOTAL_RUNTIME[] = "Total runtime: ";
const char AVERAGE_RUNTIME[] = "Average runtime: ";
const char WORST_RUNTIME[] = "Worst runtime: ";

const std::vector<double> PARABOLA_ONE = {1.0, -2.0, 1.0};
const std::vector<double> PARABOLA_ONE_PRIME = {-2.0, 2.0};

bool verify_build_type(const char build_type[] = BUILD_TYPE) {
    if (not std::getenv(BUILD_TYPE_IDENTIFIER)) return false;
    return std::strcmp(std::getenv(BUILD_TYPE_IDENTIFIER), build_type) == 0;
}

void runtime(int count, double total, double worst, std::string prefix = "") {
    if (not prefix.empty()) std::cout << prefix << '\n';
    std::cout << TOTAL_RUNTIME << total << '\t';
    if (count) std::cout << AVERAGE_RUNTIME << total / count << '\t';
    std::cout << WORST_RUNTIME << worst << '\n';
}

std::vector<std::int32_t> generate_random_array(std::size_t n, const std::size_t r) {
    nm::Random random;
    std::vector<std::int32_t> data(n);
    for (std::size_t i = 0; i < n; i++)
        data[i] = random.number(1, r);
    return data;
}

template<typename T>
bool is_sorted(std::vector<T> &v) {
    bool sorted = true;
    for (std::size_t i = 1; i < v.size(); i++) {
        if (v[i] >= v[i - 1]) continue;

        sorted = false;
        break;
    }

    return sorted;
}

TEST(PrimesTest, CountCheck) {
    std::vector<int> primes = nm::eratosthenes_sieve(N_LOG);
    ASSERT_EQ(primes.size(), P);
}

TEST(ExponentiationTest, PowersOfTwo) {
    int expect = 1;
    for (int i = 0; i < E; i++) {
        EXPECT_EQ(nm::bin_exp(2, i), expect);
        expect *= 2;
    }
}

TEST(GCDTest, RecursiveGCDPrimes) {
    std::vector<int> primes = nm::eratosthenes_sieve(N_LOG);
    for (int i = 1; i < P; i++)
        EXPECT_EQ(nm::gcd(primes[i], primes[i - 1]), 1);
}

TEST(GCDTest, RecursiveGCDEquals) {
    for (int i = 1; i < N_LOG; i++)
        EXPECT_EQ(nm::gcd(i, i), i);
}

TEST(GCDTest, RecursiveGCDMultiples) {
    for (int i = 1; i < E; i++) {
        int a = nm::bin_exp(2, i);
        int b = nm::bin_exp(2, i - 1);
        EXPECT_EQ(nm::gcd(b, a), b);
    }
}

TEST(ModInvTest, PrimeModIterativeSimple) {
    for (long long i = 2; i < N_LOG; i++) {
        long long a = nm::prime_modular_multiplicative_inverse(i, M);
        long long b = nm::prime_modular_multiplicative_inverse_by_bin_exp(i, M);
        EXPECT_EQ(a, b);
    }
}

TEST(ModInvTest, PrimeModIterative) {
    for (long long i = M + 1; i < M + N_LOG; i++) {
        long long a = nm::prime_modular_multiplicative_inverse(i, M);
        long long b = nm::prime_modular_multiplicative_inverse_by_bin_exp(i, M);
        EXPECT_EQ(a, b);
    }
}

TEST(PermutationTest, DifferentMod) {
    const int M_PRIME = 7;
    nm::PnC<int> c1{int(N_FACT), int(M)};
    nm::PnC<int> c2{int(N_FACT), int(M_PRIME)};
    for (int i = 0; i <= N_FACT; i++)
        ASSERT_EQ(c1.get_factorial(i) % M_PRIME, c2.get_factorial(i));
}

TEST(PermutationSortTest, SmallBruteForce) {
    int count = 0;
    const int N = N_FACT - 1;

    std::vector<int> permutation(N);
    std::iota(permutation.begin(), permutation.end(), 1);
    
    do {
        count++;
    } while (nm::next_permutation(permutation));

    nm::PnC<int> c{int(N_FACT), int(M)};
    ASSERT_EQ(c.get_factorial(int(N)), count);
}

TEST(SortTest, AverageRunTimeMergeSort) {
    const int N = N_FACT - 1;

    std::vector<int> permutation(N);
    std::iota(permutation.begin(), permutation.end(), 1);

    int count = 0;
    double total_time = 0.0;
    double worst_time = 0.0;

    do {
        std::vector<int> auxiliary(permutation.begin(), permutation.end());
        
        auto start = std::chrono::steady_clock::now();
        nm::merge_sort<int, int, int>(0, N - 1, auxiliary);
        auto finish = std::chrono::steady_clock::now();
        
        std::chrono::duration<double> elapsed = finish - start;
        worst_time = std::max(worst_time, elapsed.count());
        total_time += elapsed.count();
        count++;

        EXPECT_TRUE(is_sorted(auxiliary));
    } while (nm::next_permutation(permutation));

    runtime(count, total_time, worst_time);
}

TEST(SortTest, AverageRunTimeHeapSort) {
    const int N = N_FACT - 1;

    std::vector<int> permutation(N);
    std::iota(permutation.begin(), permutation.end(), 1);

    int count = 0;
    double total_time = 0.0;
    double worst_time = 0.0;

    do {
        std::vector<int> auxiliary(permutation.begin(), permutation.end());
        
        auto start = std::chrono::steady_clock::now();
        nm::heap_sort<int, int>(0, N - 1, auxiliary);
        auto finish = std::chrono::steady_clock::now();
        
        std::chrono::duration<double> elapsed = finish - start;
        worst_time = std::max(worst_time, elapsed.count());
        total_time += elapsed.count();
        count++;

        EXPECT_TRUE(is_sorted(auxiliary));
    } while (nm::next_permutation(permutation));

    runtime(count, total_time, worst_time);
}

TEST(SortTest, AverageRunTimeQuickSort) {
    const int N = N_FACT - 1;

    std::vector<int> permutation(N);
    std::iota(permutation.begin(), permutation.end(), 1);

    int count = 0;
    double total_time = 0.0;
    double worst_time = 0.0;

    do {
        std::vector<int> auxiliary(permutation.begin(), permutation.end());
        
        auto start = std::chrono::steady_clock::now();
        nm::quick_sort<int, int>(0, N - 1, auxiliary);
        auto finish = std::chrono::steady_clock::now();
        
        std::chrono::duration<double> elapsed = finish - start;
        worst_time = std::max(worst_time, elapsed.count());
        total_time += elapsed.count();
        count++;

        EXPECT_TRUE(is_sorted(auxiliary));
    } while (nm::next_permutation(permutation));

    runtime(count, total_time, worst_time);
}

TEST(SortTest, AverageRunTimeHybridSort) {
    const int N = N_FACT - 1;

    std::vector<int> permutation(N);
    std::iota(permutation.begin(), permutation.end(), 1);

    int count = 0;
    double total_time = 0.0;
    double worst_time = 0.0;

    do {
        std::vector<int> auxiliary(permutation.begin(), permutation.end());
        
        auto start = std::chrono::steady_clock::now();
        nm::hybrid_sort<int, int>(0, N - 1, auxiliary);
        auto finish = std::chrono::steady_clock::now();
        
        std::chrono::duration<double> elapsed = finish - start;
        worst_time = std::max(worst_time, elapsed.count());
        total_time += elapsed.count();
        count++;

        EXPECT_TRUE(is_sorted(auxiliary));
    } while (nm::next_permutation(permutation));

    runtime(count, total_time, worst_time);
}

TEST(BoundSearch, DistinctElements) {
    std::vector<int> space(N_FACT);
    std::iota(space.begin(), space.end(), 1);
    for (int i = 1; i <= N_FACT; i++) {
        int idx = nm::bound_search(i, 0, N_FACT - 1, space);
        ASSERT_LE(space[idx], i);
    }
}

TEST(BoundSearch, DistinctPrimes) {
    std::vector<int> primes = nm::eratosthenes_sieve(N_LOG);
    for (int i = 2; i < N_LOG; i++) {
        int idx = nm::bound_search(i, 0, P - 1, primes);
        if (idx < P) ASSERT_GE(primes[idx], i);
        
        std::function<bool(int& a, int& b)> compare =  [](int& a, int& b) {
            return not (b < a);
        }; idx = nm::bound_search(i, 0, P - 1, primes, compare);

        if (idx < P) ASSERT_GT(primes[idx], i);
    }
}

TEST(SegmentTree, DeathTest) {
    const int i = 1;
    
    std::vector<int> data(N_LOG, i);
    nm::Integrator<int> *integrator = new nm::Integrator<int>(i);
    nm::SegmentTree<int, nm::Integrator<int> > st(data);

    ASSERT_NO_FATAL_FAILURE(st.query(P, P));
    ASSERT_NO_FATAL_FAILURE(st.query(0, N_LOG - 1));
    ASSERT_NO_FATAL_FAILURE(st.update(i, P));
    ASSERT_NO_FATAL_FAILURE(st.update(i, 0, N_LOG - 1));
    
    if (not verify_build_type()) GTEST_SKIP();
    EXPECT_DEATH(st.update(i, 2 * N_LOG), ASSERTION_REGEX);
}

TEST(UnionFind, DeathTest) {
    nm::UnionFind<int> uf(N_LOG, true);
    ASSERT_NO_FATAL_FAILURE(uf.find(N_LOG));
    EXPECT_TRUE(uf.united(N_FACT, N_FACT));
    EXPECT_EQ(uf.unite(N_ROOT, N_ROOT), N_ROOT);

    if (not verify_build_type()) GTEST_SKIP();
    EXPECT_DEATH(uf.find(0), ASSERTION_REGEX);
    EXPECT_DEATH(uf.find(N_LOG + 1), ASSERTION_REGEX);
}

TEST(NRMethod, ParabolaSingle) {
    std::function<double(double)> f = nm::polynomial<double>(PARABOLA_ONE);
    std::function<double(double)> f_prime = nm::polynomial<double>(PARABOLA_ONE_PRIME);

    double root = nm::newton<double>(f, f_prime);
    
    ASSERT_LE(root, 1.01);
    ASSERT_LE(f(root), 0.01);
}

TEST(BST, InsertionSearchTest) {
    nm::SearchTree<nm::Node<int, int>, int, int> st;
    for (int i = 0; i < N_CROOT; i++) {
        st.insert(i);
        for (int j = 0; j < N_CROOT; j++) {
            bool found = st.search(j);
            if (j <= i) ASSERT_TRUE(found);
            else ASSERT_FALSE(found);
        }
    }
    
    EXPECT_EQ(st.size(), N_CROOT);
    EXPECT_EQ(st.keys().size(), N_CROOT);

    nm::SearchTree<nm::Node<int, int>, int, int> str;
    for (int i = N_CROOT - 1; i >= 0; i--) {
        str.insert(i);
        for (int j = N_CROOT; j >= 0; j--) {
            bool found = str.search(j);
            if (j >= i and j < N_CROOT)
                ASSERT_TRUE(found);
            else ASSERT_FALSE(found);
        }
    }
    
    EXPECT_EQ(str.size(), N_CROOT);
    EXPECT_EQ(str.keys().size(), N_CROOT);
}

TEST(BST, InsertionDeletionTest) {
    nm::SearchTree<nm::Node<int, int>, int, int> st;
    for (int i = N_CROOT; i > 0; i--) st.insert(i);

    for (int i = 0; i <= N_CROOT; i++) {
        bool result = st.remove(i);
        
        if (i) ASSERT_TRUE(result);
        else ASSERT_FALSE(result);
        
        std::size_t size = N_CROOT - (i ? 1 : 0);
        std::vector<int> keys = st.keys();
        EXPECT_TRUE(is_sorted(keys));
        EXPECT_EQ(keys.size(), size);
        EXPECT_EQ(st.size(), size);

        if (i) st.insert(i);
    }
}

TEST(AVL, ObtainTest) {
    nm::AVL<nm::Node<int, int>, int, int> avl;
    for (int i = N_CROOT; i > 0; i--) avl.insert(i);
    EXPECT_NO_FATAL_FAILURE(avl[N_CROOT]);
    EXPECT_THROW(avl.obtain(N_ROOT), std::runtime_error);
}

TEST(BST, TimeTest) {
    const int N = N_FACT - 1;
    std::vector<int> permutation(N);
    std::iota(permutation.begin(), permutation.end(), 1);

    int count = 0;
    double total_search_time = 0.0;
    double worst_search_time = 0.0;
    double total_insertion_time = 0.0;
    double worst_insertion_time = 0.0;
    double total_extraction_time = 0.0;
    double worst_extraction_time = 0.0;

    do {
        nm::SearchTree<nm::Node<int, int>, int, int> st;
        
        // time for insertion
        auto i_start = std::chrono::steady_clock::now();
        for (int p : permutation) ASSERT_TRUE(st.insert(p));
        auto i_finish = std::chrono::steady_clock::now();
        
        std::chrono::duration<double> i_elapsed = i_finish - i_start;
        worst_insertion_time = std::max(worst_insertion_time, i_elapsed.count());
        total_insertion_time += i_elapsed.count();

        // time for search
        auto s_start = std::chrono::steady_clock::now();
        for (int i = 1; i <= N; i++) ASSERT_TRUE(st.search(i));
        auto s_finish = std::chrono::steady_clock::now();

        std::chrono::duration<double> s_elapsed = s_finish - s_start;
        worst_search_time = std::max(worst_search_time, s_elapsed.count());
        total_search_time += s_elapsed.count();

        // time for extraction
        auto e_start = std::chrono::steady_clock::now();
        for (int i = 1; i <= N; i++) ASSERT_TRUE(st.remove(i));
        auto e_finish = std::chrono::steady_clock::now();

        std::chrono::duration<double> e_elapsed = e_finish - e_start;
        worst_extraction_time = std::max(worst_extraction_time, s_elapsed.count());
        total_extraction_time += e_elapsed.count();

        count++;
    } while (nm::next_permutation(permutation));
    
    runtime(count, total_insertion_time, worst_insertion_time, "Insertion");
    runtime(count, total_search_time, worst_search_time, "Search");
    runtime(count, total_extraction_time, worst_extraction_time, "Extraction");
}

TEST(AVL, InsertionDeletionTest) {
    nm::AVL<nm::Node<int, int>, int, int> avl;
    for (int i = N_CROOT; i > 0; i--)
        ASSERT_TRUE(avl.insert(i));

    for (int i = 0; i <= N_CROOT; i++) {
        bool result = avl.remove(i);
        if (i) ASSERT_TRUE(result);
        else ASSERT_FALSE(result);
        
        std::size_t size = N_CROOT - (i ? 1 : 0);
        std::vector<int> keys = avl.keys();
        EXPECT_TRUE(is_sorted(keys));
        EXPECT_EQ(keys.size(), size);
        EXPECT_EQ(avl.size(), size);

        if (i) ASSERT_TRUE(avl.insert(i));
    }
}

TEST(AVL, TimeTest) {
    const int N = N_FACT - 1;
    std::vector<int> permutation(N);
    std::iota(permutation.begin(), permutation.end(), 1);

    int count = 0;
    double total_search_time = 0.0;
    double worst_search_time = 0.0;
    double total_insertion_time = 0.0;
    double worst_insertion_time = 0.0;
    double total_extraction_time = 0.0;
    double worst_extraction_time = 0.0;

    do {
        nm::AVL<nm::Node<int, int>, int, int> avl;
        
        // time for insertion
        auto i_start = std::chrono::steady_clock::now();
        for (int p : permutation) ASSERT_TRUE(avl.insert(p));
        auto i_finish = std::chrono::steady_clock::now();
        
        std::chrono::duration<double> i_elapsed = i_finish - i_start;
        worst_insertion_time = std::max(worst_insertion_time, i_elapsed.count());
        total_insertion_time += i_elapsed.count();

        // time for search
        auto s_start = std::chrono::steady_clock::now();
        for (int i = 1; i <= N; i++) ASSERT_TRUE(avl.search(i));
        auto s_finish = std::chrono::steady_clock::now();

        std::chrono::duration<double> s_elapsed = s_finish - s_start;
        worst_search_time = std::max(worst_search_time, s_elapsed.count());
        total_search_time += s_elapsed.count();

        // time for extraction
        auto e_start = std::chrono::steady_clock::now();
        for (int i = 1; i <= N; i++) ASSERT_TRUE(avl.remove(i));
        auto e_finish = std::chrono::steady_clock::now();

        std::chrono::duration<double> e_elapsed = e_finish - e_start;
        worst_extraction_time = std::max(worst_extraction_time, s_elapsed.count());
        total_extraction_time += e_elapsed.count();

        count++;
    } while (nm::next_permutation(permutation));
    
    runtime(count, total_insertion_time, worst_insertion_time, "Insertion");
    runtime(count, total_search_time, worst_search_time, "Search");
    runtime(count, total_extraction_time, worst_extraction_time, "Extraction");
}

TEST(BST, AssignmentTest) {
    nm::SearchTree<nm::Node<int, int>, int, int> st;
    for (std::size_t i = 1; i < N_ROOT; i++)
        ASSERT_EQ(st[i] = (N_ROOT - i), st[i]);

    for (std::size_t i = N_ROOT; i > 0; i--) {
        EXPECT_NO_THROW(st[i]);
        if (i < N_ROOT) ASSERT_EQ(st[i], N_ROOT - i);
    }
}

TEST(AVL, AssignmentTest) {
    nm::AVL<nm::Node<int, int>, int, int> avl;
    for (std::size_t i = 1; i < N_ROOT; i++)
        ASSERT_EQ(avl[i] = N_ROOT - i, avl[i]);
    
    EXPECT_THROW(avl.element(N_ROOT), std::runtime_error);
    for (std::size_t i = N_ROOT; i > 0; i--) {
        EXPECT_NO_THROW(avl[i]);
        if (i == N_ROOT) continue;
        
        ASSERT_EQ(avl[i], N_ROOT - i);
        EXPECT_NO_THROW(avl.element(i));
    }
}

TEST(Splay, AssignmentTest) {
    nm::Splay<nm::Node<int, int>, int, int> splay;
    for (std::size_t i = 1; i < N_ROOT; i++)
        ASSERT_EQ(splay[i], splay.insert(i, N_ROOT - i));
    
    EXPECT_THROW(splay.element(N_ROOT), std::runtime_error);
    for (std::size_t i = N_ROOT - 1; i > 0; i--) {
        ASSERT_EQ(splay[i], N_ROOT - i);
        EXPECT_NO_THROW(splay.element(i));
    }
}

TEST(Splay, ObtainTest) {
    nm::Splay<nm::Node<int, int>, int, int> splay;
    for (int i = N_CROOT; i > 0; i--) splay.insert(i);
    EXPECT_NO_FATAL_FAILURE(splay[N_CROOT]);
    EXPECT_THROW(splay.obtain(N_ROOT), std::runtime_error);
}

TEST(Splay, InsertionDeletionTest) {
    nm::Splay<nm::Node<int, int>, int, int> splay;
    for (int i = N_CROOT; i > 0; i--) splay.insert(i);

    for (int i = 0; i <= N_CROOT; i++) {
        bool result = splay.remove(i);
        
        if (i) ASSERT_TRUE(result);
        else ASSERT_FALSE(result);
        
        std::size_t size = N_CROOT - (i ? 1 : 0);
        std::vector<int> keys = splay.keys();
        EXPECT_TRUE(is_sorted(keys));
        EXPECT_EQ(keys.size(), size);
        EXPECT_EQ(splay.size(), size);

        if (i) splay.insert(i);
    }
}

TEST(Splay, TimeTest) {
    const int N = N_FACT - 1;
    std::vector<int> permutation(N);
    std::iota(permutation.begin(), permutation.end(), 1);

    int count = 0;
    double total_search_time = 0.0;
    double worst_search_time = 0.0;
    double total_insertion_time = 0.0;
    double worst_insertion_time = 0.0;
    double total_extraction_time = 0.0;
    double worst_extraction_time = 0.0;

    do {
        nm::Splay<nm::Node<int, int>, int, int> splay;
        
        // time for insertion
        auto i_start = std::chrono::steady_clock::now();
        for (int p : permutation) ASSERT_TRUE(splay.insert(p));
        auto i_finish = std::chrono::steady_clock::now();
        
        std::chrono::duration<double> i_elapsed = i_finish - i_start;
        worst_insertion_time = std::max(worst_insertion_time, i_elapsed.count());
        total_insertion_time += i_elapsed.count();

        // time for search
        auto s_start = std::chrono::steady_clock::now();
        for (int i = 1; i <= N; i++) ASSERT_TRUE(splay.search(i));
        auto s_finish = std::chrono::steady_clock::now();

        std::chrono::duration<double> s_elapsed = s_finish - s_start;
        worst_search_time = std::max(worst_search_time, s_elapsed.count());
        total_search_time += s_elapsed.count();

        // time for extraction
        auto e_start = std::chrono::steady_clock::now();
        for (int i = 1; i <= N; i++) ASSERT_TRUE(splay.remove(i));
        auto e_finish = std::chrono::steady_clock::now();

        std::chrono::duration<double> e_elapsed = e_finish - e_start;
        worst_extraction_time = std::max(worst_extraction_time, s_elapsed.count());
        total_extraction_time += e_elapsed.count();

        count++;
    } while (nm::next_permutation(permutation));
    
    runtime(count, total_insertion_time, worst_insertion_time, "Insertion");
    runtime(count, total_search_time, worst_search_time, "Search");
    runtime(count, total_extraction_time, worst_extraction_time, "Extraction");
}

TEST(KMP, StringSearch) {
    std::vector<std::string> sentences = {
        "I've gotta get out of this place. Someday, I'm getting on that train. (Spirited Away)",
        "Sometimes the wrong train takes you to the right destination. (The Lunchbox)"
    };

    std::vector<std::string> words = {
        "Train",
        "Some"
    };
    
    for (std::string &word : words) {
        std::size_t count = 0;
        nm::KMP kmp(word, false);
        for (std::string sentence : sentences) {
            kmp.stream(sentence);
            EXPECT_EQ(kmp.search().size(), ++count);
        }
    }

    nm::KMP kmp(words[0]);
    for (std::string sentence : sentences) {
        kmp.stream(sentence);
        EXPECT_EQ(kmp.search().size(), 0);
    }
}

TEST(MOD, INT32_M) {
    EXPECT_EQ(std::int64_t(nm::int32_m::modulus), M);

    for (std::int64_t x = M - N_ROOT; x <= M + N_ROOT; x++) {
        for (std::int64_t y = M - N_ROOT; y <= M + N_ROOT; y++) {
            nm::int32_m mx = x;
            nm::int32_m my = y;

            if (x % M < y % M) {
                ASSERT_LT(mx, my);
                ASSERT_TRUE(mx < my);
                ASSERT_FALSE(mx >= my);
            } else {
                ASSERT_GE(mx, my);
                ASSERT_TRUE(mx >= my);
                ASSERT_FALSE(mx < my);
            }

            EXPECT_EQ(mx * mx, 1LL * x * x % M);
            EXPECT_EQ(my * my, 1LL * y * y % M);
            EXPECT_EQ(mx - my, (x - y + M) % M);
            EXPECT_EQ(my - mx, (y - x + M) % M);
        }

        std::int64_t z = x;
        nm::int32_m mz = x;
        EXPECT_EQ(z++ % M, mz++);
        EXPECT_EQ(z-- % M, mz--);
        EXPECT_EQ(++z % M, ++mz);
        EXPECT_EQ(--z % M, --mz);

        EXPECT_GE(z, mz);

        mz *= P;
        z = (z * P) % M;
        EXPECT_EQ(mz, z);
    }
}

TEST(MOD, LIMITS) {
    nm::Arithmetic<int> o(M);

    int x = 1e9 - 1;
    int y = 1e9 + 1;

    EXPECT_EQ(o.multiply(x, x), 1LL * x * x % M);
    EXPECT_EQ(o.subtract(x, y), (x - y + M) % M);
    EXPECT_EQ(o.subtract(y, x), (y - x + M) % M);
}

TEST(Random, Secure) {
    nm::Random random_x;
    nm::Random random_y;

    std::size_t count = 0;
    const std::uint32_t N = N_LOG * N_FACT;
    for (std::uint32_t i = 0; i <= N; i++) {
        std::uint32_t x = random_x.number(i, N);
        std::uint32_t y = random_y.number(i, N);

        ASSERT_GE(x, i); ASSERT_LE(x, N);
        ASSERT_GE(y, i); ASSERT_LE(y, N);

        count += x == y;
    }
    
    EXPECT_LT(count, N);
    EXPECT_GT(count, 0);
}

TEST(Random, Pseudo) {
    nm::Random random_x(P, nm::M93);
    nm::Random random_y(P, nm::M93);

    std::size_t count = 0;
    const std::uint32_t N = N_LOG * N_FACT;
    for (std::uint32_t i = 0; i < N; i++)
        count += random_x.number(N) == random_y.number(N);
    
    EXPECT_EQ(count, N);
}

TEST(BMA, StringSearch) {
    std::vector<std::string> sentences = {
        "The laws of physics are the same in all inertial frames of reference.",
        "The speed of light in free space has the same value in all inertial frames of reference."
    };

    std::vector<std::string> words = {
        "Reference",
        "Frames",
    };

    for (std::string &word : words) {
        std::size_t count = 0;
        nm::BMA bma(word, false);
        for (std::string sentence : sentences) {
            bma.stream(sentence);
            EXPECT_EQ(bma.search().size(), ++count);
        }
    }
}

TEST(Fenwick, SumQuery) {
    std::vector<std::int32_t> data = generate_random_array(N_LOG, N_ROOT);
    
    std::function<std::int32_t(std::int32_t, std::int32_t)> operation = 
        [] (std::int32_t x, std::int32_t y) -> std::int32_t {
                return x + y;
            };
    
    nm::Random random;
    nm::Fenwick fw(data, operation);
    for (std::size_t i = 0; i < N_FACT; i++) {
        std::int32_t l = random.number(0, N_LOG - 1);
        std::int32_t r = random.number(l, N_LOG - 1);

        std::int32_t j = l;
        std::size_t expected = 0;
        while (j <= r) expected += data[j++];
        EXPECT_EQ(fw.query(l, r), expected);
    }
}

TEST(SparseTable, XORQuery) {
    std::vector<std::int32_t> data = generate_random_array(N_LOG, N_ROOT);

    std::function<std::int32_t(std::int32_t, std::int32_t)> operation = 
        [] (std::int32_t x, std::int32_t y) -> std::int32_t {
                return x ^ y;
            };
    
    nm::Random random;
    nm::Sparse st(data, operation);
    for (std::size_t i = 0; i < N_FACT; i++) {
        std::int32_t l = random.number(0, N_LOG - 1);
        std::int32_t r = random.number(l, N_LOG - 1);

        std::int32_t j = l;
        std::size_t expected = 0;
        while (j <= r) expected ^= data[j++];

        EXPECT_EQ(st.cquery(l, r), expected);
    }
}

TEST(SparseTable, MaxQuery) {
    std::vector<std::int32_t> data = generate_random_array(N_LOG, N_ROOT);

    std::function<std::int32_t(std::int32_t, std::int32_t)> operation = 
        [] (std::int32_t x, std::int32_t y) -> std::int32_t {
                return std::max(x, y);
            };
    
    nm::Random random;
    nm::Sparse st(data, operation);
    for (std::size_t i = 0; i < N_FACT; i++) {
        std::int32_t l = random.number(0, N_LOG - 1);
        std::int32_t r = random.number(l, N_LOG - 1);

        std::int32_t j = l;
        std::int32_t expected = 0;
        while (j <= r) expected = std::max(expected, data[j++]);

        EXPECT_EQ(st.cquery(l, r), expected);
    }
}

int main(int argc, char *argv[]) {
    // GTest //
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
