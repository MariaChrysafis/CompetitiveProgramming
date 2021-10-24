#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
int solver (long long a, long long b, long long c) {
    long long sum = (a + 2 * b + 3 * c);
    if (b == 0 && a == 1) {
        if (c % 2 == 1) {
            return 2;
        }
    }
    if (a == 0 && b == 1) {
        if (c % 2 == 0) {
            return 2;
        }
    }
    if (a == 0 && c == 0) {
        if (b % 2 == 0) {
            return 2;
        }
    }
    if (sum % 2 == 0) {
        return 0;
    } else {
        return 1;
    }
}
void solve() {
    long long a, b, c;
    cin >> a >> b >> c;
    cout << solver(a, b, c) << '\n';
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
