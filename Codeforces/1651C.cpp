#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <complex>
#include <cmath>
#include <set>
using namespace std;
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int64_t> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        int64_t myMin = abs(a[0] - b.back()) + abs(a.back() - b[0]);
        myMin = min(myMin, abs(a[0] - b[0]) + abs(a.back() - b.back()));
        int64_t a0, b0, a1, b1;
        a0 = b0 = a1 = b1 = INT_MAX;
        for (int i = 0; i < n; i++) a0 = min(a0, abs(a[0] - b[i]));
        for (int i = 0; i < n; i++) a1 = min(a1, abs(a.back() - b[i]));
        for (int i = 0; i < n; i++) b0 = min(b0, abs(a[i] - b[0]));
        for (int i = 0; i < n; i++) b1 = min(b1, abs(a[i] - b.back()));
        myMin = min(myMin, abs(a.back() - b[0]) + a0 + b1);
        myMin = min(myMin, abs(b.back() - a[0]) + b0 + a1);
        myMin = min(myMin, abs(a[0] - b[0]) + a1 + b1);
        myMin = min(myMin, abs(b.back() - a.back()) + b0 + a0);
        myMin = min(myMin, a0 + a1 + b0 + b1);
        cout << myMin << '\n';
    }
}
