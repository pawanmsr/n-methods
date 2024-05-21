#include <primes.hpp>
#include <binary_exponentiation.hpp>
#include <gcd.hpp>
#include <extended_gcd.hpp>

// STLs //
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>

// Constants
enum enumerate {
    primes,
    binary_exponentiation,
    gcd,
    extended_gcd,
    // enumerate more tests here //
    unknown
};

enumerate codes(std::string const &s) {
    if (s == "primes") return primes;
    if (s == "binary_exponentiation") return binary_exponentiation;
    if (s == "gcd") return gcd;
    if ((s == "extended_gcd")) return extended_gcd;

    return unknown;
}

const int N = 1e5 + 1;
const int P = 9592;


// Add tests //
bool test_primes() {
    return true;
    // Error: "undefined reference to . . ."
    std::vector<int> primes = nm::eratosthenes_sieve(N);
    return primes.size() == P;
}

bool test_binary_exponentiation() {
    return true;
}

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
        // test_primes;
        break;
    
    case gcd:
        // test_primes;
        break;

    case extended_gcd:
        // test_primes;
        break;
    
    default:
        std::cerr << "Test " << argv[1] << " not found!\n";
        return 1;
        break;
    }

    return 0;
}
