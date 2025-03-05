/* 
 * Author: Canis Lupus Loner
 */


 #pragma GCC optimize("O3", "fast-math", "unroll-loops")

/*
 * Compile and Run
 * g++ -std=c++2a -DLOCAL -Wall -Wextra -pedantic 
 * -g -Wconversion -Wshadow <source> -I . -o <binary>
 * ./<binary>
 * gdb <binary> // on failure.
 */

// All STL
#include <bits/stdc++.h>

// Individual STL Libs
// I/O Libs
#include <cstdio> // printf and scanf
#include <fstream> // files nad buffers
#include <iomanip> // setprecision
#include <iostream> // standard input output, <istream> + <ostream>
// #include <print> // formatting options
#include <sstream>
// Math Libs
#include <bit> // popcount, rotate left/right, bit floor/ceil, etc.
#include <cmath> // abs, trig, log, etc.
#include <complex> // complex numbers
// #include <linalg> // linear algebra
// #include <numbers> // e, pi, phi, etc
#include <numeric> // iota, accumulate, gcd, lcm, midpoint, inner product, etc.
#include <random> // generate random numbers from distributions
// Algo Libs
#include <algorithm> // fill, rotate, sort, swap, search, heap, permutation, etc.
// Limits
// #include <climits> // INT_MIN/MAX, etc.
#include <limits> // numeric limits and functions
// Utility
#include <utility> // pair, tuple, compare, etc.
// #include <tuple>
#include <functional>
#include <any> // like python variable
#include <bitset> // fixed length array of bits
// #include <cstdlib> // abs, rand, sort, search for C
// Containers
#include <array> // like fixed sized arrays in C but with member functions
#include <vector>
#include <queue>
#include <deque> // // double ended queue
#include <list> // doubly linked list
#include <stack>
#include <set> // includes multiset
#include <unordered_set> // hashing and chaining
#include <map> // rb-tree
#include <unordered_map> // hashing and chaining
// String Libs
#include <string>
// #include <cstring> // for C stype operations: strcpy, strcat
// Other Libs
#include <iterator>
#include <regex>

using namespace std;

typedef long double ld;
typedef long long int ll;

// Macro //
#define X first
#define Y second
#define pll pair<ll, ll>
#define pii pair<int, int>
#define all(x) (x).begin(), (x).end()
#define debug(x) cerr << x << endl

// External //

/*
 * Citation
 */

// // // // //

// Global //


// Functions //


// Main //
int main(int argc, char const *argv[]) {
    assert(sizeof(*argv) == sizeof(void*) * argc);

    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    // cout << fixed << setprecision(16);

    #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    #else
    // online submission
    #endif

    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #else
    // online submission
    #endif
    
    /* code */
    cerr << "On a starry moonlit night,\n"
    << "A lonely wolf begins to howl.\n"
    << "Wondering if his solutions are right,\n"
    << "'Do submit; maybe it's not all foul.'" << endl;
    
    return 0;
}


// Definitions //
