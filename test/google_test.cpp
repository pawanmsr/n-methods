// STLs //
#include <vector>
#include <numeric>
#include <functional>

// NMethods //
#include <primes.hpp>
#include <binary_exponentiation.hpp>
#include <gcd.hpp>
#include <extended_gcd.hpp>
#include <sort.hpp>
#include <modulo_operations.hpp>
#include <search.hpp>
#include <combinatorics.hpp>

// GTest //
#include <gtest/gtest.h>

const int N_LOG = 1e5 + 1;
const int N_ROOT = 1e3 + 1;
const int N_CROOT = 1e2 + 1;
const int N_FACT = 10;
const int P = 9592;
const int E = 31;
const long long M = 1e9 + 7;

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
        std::vector<int> auxillary(permutation.begin(), permutation.end());
        nm::merge_sort<int, int, int>(0, N - 1, auxillary);
        
        bool sorted = true;
        for (int i = 1; i < N; i++)
            if (auxillary[i] < auxillary[i - 1])
                sorted = false;
        ASSERT_TRUE(sorted);
        
        count++;
    } while (nm::next_permutation(permutation));

    nm::PnC<int> c{int(N_FACT), int(M)};
    ASSERT_EQ(c.get_factorial(int(N)), count);
}

TEST(BoundSearch, DistinctElements) {
    std::vector<int> space(N_FACT);
    std::iota(space.begin(), space.end(), 1);
    for (int i = 1; i <= N_FACT; i++) {
        int idx = nm::bound_search(i, 0, N_FACT - 1, space);
        // ASSERT_GE(space[idx], i); // FIXME
    }
}

TEST(BoundSearch, DistinctPrimes) {
    std::vector<int> primes = nm::eratosthenes_sieve(N_LOG);
    for (int i = 2; i < N_LOG; i++) {
        int idx = nm::bound_search(i, 0, P - 1, primes);
        ASSERT_GE(primes[idx], i); // FIXME
        
        std::function<bool(int& a, int& b)> compare =  [](int& a, int& b) {
            return not (b < a);
        }; idx = nm::bound_search(i, 0, P - 1, primes, compare);
        ASSERT_LE(primes[idx], i); // FIXME
    }
}

int main(int argc, char *argv[])
{
    // GTest //
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
