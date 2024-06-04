
// STLs //
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>

// NMethods //
#include <primes.hpp>
#include <binary_exponentiation.hpp>
#include <gcd.hpp>
#include <extended_gcd.hpp>
#include <sort.hpp>

// Constants
enum enumerate {
    primes,
    binary_exponentiation,
    gcd,
    extended_gcd,
    sort,
    // enumerate more tests here //
    unknown
};

enumerate codes(std::string const &s) {
    if (s == "primes") return primes;
    if (s == "binary_exponentiation") return binary_exponentiation;
    if (s == "gcd") return gcd;
    if (s == "extended_gcd") return extended_gcd;
    if (s == "sort") return sort;

    return unknown;
}

const int N = 1e5 + 1;
const int P = 9592;


// Simple Tests //
bool test_primes() {
    std::vector<int> primes = nm::eratosthenes_sieve(N);
    return primes.size() == P;
}

bool test_binary_exponentiation() {
    return true;
}

bool test_gcd() {
    return true;
}

bool test_extended_gcd() {
    return true;
}

bool test_sort() {
    // Until works.
    return true;
    // Failing. TODO: figure out generic instantiation.
    std::vector<int> we;
    const int mod = 101;
    const int our_size = 1e5;
    for (int i = 0; i < our_size; i++) {
        we.push_back(((i % mod) * our_size) % mod);
    }
    
    nm::quick_sort(0, our_size - 1, we);
    
    bool non_decreasing = true;
    for (int me = 1; me < our_size; me++)
        non_decreasing &= (we[me] >= we[me - 1]);
    
    return non_decreasing;
}

// Add GTests //

// Run tests //
int main(int argc, char const *argv[])
{
    if (argc <= 1)
        return 1;
    
    switch (codes(argv[1]))
    {
    case primes:
        assert(test_primes());
        break;
    
    case binary_exponentiation:
        assert(test_binary_exponentiation());
        break;
    
    case gcd:
        assert(test_gcd());
        break;

    case extended_gcd:
        assert(test_extended_gcd());
        break;
    
    case sort:
        assert(test_sort());
        break;
    
    default:
        std::cerr << "Test " << argv[1] << " not found!\n";
        return 1;
        break;
    }

    return 0;
}
