#include <iostream>
using namespace std;

/* T is expected to be any integer data type */
/* time complexity O(log min (a, b)) */

template <typename T>
T gcd(T a, T b) {
    return b ? gcd(b, a % b) : a;
}

template <typename T>
T gcd_nr(T a, T b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main(int argc, char const *argv[])
{
    long long int t, a, b;
    cin >> t;
    while (t--) {
        cin >> a >> b;
        cout << gcd(a, b) << " " << a / gcd(a, b) * b << endl;
    }
    return 0;
}
