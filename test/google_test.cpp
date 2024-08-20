// STLs //
#include <vector>
#include <numeric>

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

TEST(PermutationSortTest, SmallBruteForce) {
    std::vector<int> permutation(N_FACT);
    std::iota(permutation.begin(), permutation.end(), 1);
    
    int count = 0;
    do
    {
        // TODO: add sort test
        count++;
    } while (nm::next_permutation(permutation));

    nm::PnC<int> C{int(N_FACT), int(M)};
    ASSERT_EQ(C.get_factorial(int(N_FACT)), count);
}

int main(int argc, char *argv[])
{
    // GTest //
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
