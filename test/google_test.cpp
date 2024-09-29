// STLs //
#include <vector>
#include <numeric>
#include <functional>
#include <chrono>

// NMethods //
#include <primes.hpp>
#include <binary_exponentiation.hpp>
#include <gcd.hpp>
#include <extended_gcd.hpp>
#include <sort.hpp>
#include <modulo_operations.hpp>
#include <search.hpp>
#include <combinatorics.hpp>
#include <segment_tree.hpp>
#include <union_find.hpp>
#include <utility.hpp>

// GTest //
#include <gtest/gtest.h>

const int N_LOG = 1e5 + 1;
const int N_ROOT = 1e3 + 1;
const int N_CROOT = 1e2 + 1;
const int N_FACT = 10;
const int P = 9592;
const int E = 31;
const long long M = 1e9 + 7;

const char ASSERTION_REGEX[] = "Assertion.*failed";

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
        std::vector<int> auxillary(permutation.begin(), permutation.end());
        
        auto start = std::chrono::steady_clock::now();
        nm::merge_sort<int, int, int>(0, N - 1, auxillary);
        auto finish = std::chrono::steady_clock::now();
        
        std::chrono::duration<double> elapsed = finish - start;
        worst_time = std::max(worst_time, elapsed.count());
        total_time += elapsed.count();
        count++;

        bool sorted = true;
        for (int i = 1; i < N; i++)
            if (auxillary[i - 1] > auxillary[i])
                sorted = false;
        EXPECT_TRUE(sorted);
    } while (nm::next_permutation(permutation));

    std::cout << "Total runtime: " << total_time << '\t'
    << "Average runtime: " << total_time / count << '\t'
    << "Worst runtime: " << worst_time << '\n';
}

TEST(SortTest, AverageRunTimeHeapSort) {
    const int N = N_FACT - 1;

    std::vector<int> permutation(N);
    std::iota(permutation.begin(), permutation.end(), 1);

    int count = 0;
    double total_time = 0.0;
    double worst_time = 0.0;

    do {
        std::vector<int> auxillary(permutation.begin(), permutation.end());
        
        auto start = std::chrono::steady_clock::now();
        nm::heap_sort<int, int>(0, N - 1, auxillary);
        auto finish = std::chrono::steady_clock::now();
        
        std::chrono::duration<double> elapsed = finish - start;
        worst_time = std::max(worst_time, elapsed.count());
        total_time += elapsed.count();
        count++;

        bool sorted = true;
        for (int i = 1; i < N; i++)
            if (auxillary[i - 1] > auxillary[i])
                sorted = false;
        EXPECT_TRUE(sorted);
    } while (nm::next_permutation(permutation));

    std::cout << "Total runtime: " << total_time << '\t'
    << "Average runtime: " << total_time / count << '\t'
    << "Worst runtime: " << worst_time << '\n';
}

TEST(SortTest, AverageRunTimeQuickSort) {
    const int N = N_FACT - 1;

    std::vector<int> permutation(N);
    std::iota(permutation.begin(), permutation.end(), 1);

    int count = 0;
    double total_time = 0.0;
    double worst_time = 0.0;

    do {
        std::vector<int> auxillary(permutation.begin(), permutation.end());
        
        auto start = std::chrono::steady_clock::now();
        nm::quick_sort<int, int>(0, N - 1, auxillary);
        auto finish = std::chrono::steady_clock::now();
        
        std::chrono::duration<double> elapsed = finish - start;
        worst_time = std::max(worst_time, elapsed.count());
        total_time += elapsed.count();
        count++;

        bool sorted = true;
        for (int i = 1; i < N; i++)
            if (auxillary[i - 1] > auxillary[i])
                sorted = false;
        EXPECT_TRUE(sorted);
    } while (nm::next_permutation(permutation));

    std::cout << "Total runtime: " << total_time << '\t'
    << "Average runtime: " << total_time / count << '\t'
    << "Worst runtime: " << worst_time << '\n';
}

TEST(SortTest, AverageRunTimeHybridSort) {
    const int N = N_FACT - 1;

    std::vector<int> permutation(N);
    std::iota(permutation.begin(), permutation.end(), 1);

    int count = 0;
    double total_time = 0.0;
    double worst_time = 0.0;

    do {
        std::vector<int> auxillary(permutation.begin(), permutation.end());
        
        auto start = std::chrono::steady_clock::now();
        nm::hybrid_sort<int, int>(0, N - 1, auxillary);
        auto finish = std::chrono::steady_clock::now();
        
        std::chrono::duration<double> elapsed = finish - start;
        worst_time = std::max(worst_time, elapsed.count());
        total_time += elapsed.count();
        count++;

        bool sorted = true;
        for (int i = 1; i < N; i++)
            if (auxillary[i - 1] > auxillary[i])
                sorted = false;
        EXPECT_TRUE(sorted);
    } while (nm::next_permutation(permutation));

    std::cout << "Total runtime: " << total_time << '\t'
    << "Average runtime: " << total_time / count << '\t'
    << "Worst runtime: " << worst_time << '\n';
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
        ASSERT_LE(primes[idx], i);
        
        std::function<bool(int& a, int& b)> compare =  [](int& a, int& b) {
            return not (b < a);
        }; idx = nm::bound_search(i, 0, P - 1, primes, compare);

        GTEST_SKIP() << "fixme";
        ASSERT_GT(primes[idx], i); // FIXME
    }
}

TEST(SegmentTree, OutOfBounds) {
    std::vector<int> data(N_LOG, 1);
    nm::Integrator<int> *integrator = new nm::Integrator<int>(0);
    GTEST_SKIP() << "undefined reference even after explicit instantiation";
    nm::SegmentTree<int, nm::Integrator<int> > st(data); // FIXME

    ASSERT_NO_FATAL_FAILURE(st.query(0, N_LOG - 1) == 0);
    ASSERT_NO_FATAL_FAILURE(st.update(1, 0, N_LOG - 1));
    
    ASSERT_NO_FATAL_FAILURE(st.update(1, P));
    EXPECT_EQ(st.query(P, P), 1);
    
    EXPECT_DEATH(st.update(0, N_LOG), "failed"); // FIXME
}

TEST(UnionFind, OutOfBounds) {
    nm::UnionFind<int> uf(N_LOG);
    ASSERT_NO_FATAL_FAILURE(uf.find(N_LOG));
    EXPECT_TRUE(uf.united(N_FACT, N_FACT));
    EXPECT_EQ(uf.unite(N_ROOT, N_ROOT), N_ROOT);

    EXPECT_DEATH(uf.find(0), ASSERTION_REGEX);
    EXPECT_DEATH(uf.find(N_LOG + 1), ASSERTION_REGEX);
}

int main(int argc, char *argv[])
{
    // GTest //
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
