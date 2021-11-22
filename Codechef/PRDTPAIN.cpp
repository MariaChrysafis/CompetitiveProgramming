#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#define ll __uint128_t
using namespace std;
void solve () {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        set<long long> s = {a[i + 1] * 2};
        for (int j = i + 2; j < n; j++) {
            auto it = s.upper_bound((a[i] + a[j]));
            if (it == s.begin()) {
                ans += (a[i] - *it/2) * (*it/2 - a[j]);
                s.insert(2 * a[j]);
                continue;
            }
            long long best1 = *it/2;
            it--;
            long long best2 = *it/2;
            ans += max((a[i] - best1) * (best1 - a[j]), (a[i] - best2) * (best2 - a[j]));
            s.insert(2 * a[j]);
        }
    }
    cout << ans << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
