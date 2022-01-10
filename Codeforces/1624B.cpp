#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <ctime>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        long long a, b, c;
        cin >> a >> b >> c;
        if (abs(2 * b - c) % a == 0 && 2 * b - c > 0) {
            cout << "YES\n";
            continue;
        }
        if ((a + c) % 2 == 0 && a + c >= 0 && (a + c) % (2 * b) == 0) {
            cout << "YES\n";
            continue;
        }
        if (abs(2 * b - a) % c == 0 && 2 * b - a > 0) {
            cout << "YES\n";
            continue;
        }
        cout << "NO\n";
    }
}
