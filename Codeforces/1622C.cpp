#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
using namespace std;

int64_t floor(int64_t a, int64_t b) {
    if (a < 0) {
        return -(-a + b - 1) / b;
    }
    return a / b;
}

void solve(int tc) {
    int64_t n, k;
    cin >> n >> k;
    vector<int64_t> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    vector<int64_t> pref(n + 1);
    pref[0] = 0;
    for (int i = 1; i <= v.size(); i++) {
        pref[i] = pref[i - 1] + v[i - 1];
    }
    if (pref.back() <= k) {
        cout << 0 << '\n';
        return;
    }
    if (n == 1) {
        cout << pref.back() - k << '\n';
        return;
    }
    vector<int64_t> pos;
    int64_t myMin = pref.back() - k;

    for (int i = 1; i < n; i++) {
        int64_t left = pref[i] - v[0]; // 0...i - 1 | i ... n - 1
        int64_t range_set = floor(k - left, n - i + 1); // set everything to be range_set
        int64_t cur;
        if (range_set >= v[0]) {
            cur = n - i;
        } else {
            cur = v[0] - range_set + (n - i);
        }
        myMin = min(myMin, cur);
    }
    cout << myMin << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

}
