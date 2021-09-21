#include <iostream>
#include <vector>
#include <cmath>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;

void solve() {
    vector<int> ans;
    vector<int> v;
    int n;
    cin >> n;
    v.resize(n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        sum ^= v[i];
    }
    if (sum != 0) {
        cout << "NO\n";
        return;
    }
    auto process = [&](int x) {
        if (x + 2 >= v.size()) {
            return;
        }
        ans.push_back(x + 1);
        v[x] = v[x + 1] = v[x + 2] = (v[x] + v[x + 1] + v[x + 2]) % 2;
    };
    auto odd = [&](int l, int r) {
        for (int i = l; i <= r - 2; i += 2) {
            process(i);
        }
        for (int i = r - 2; i >= l; i -= 2) {
            process(i);
        }
    };
    sum = 0;
    int prev = -1;
    for (int i = 0; i < n; i++) {
        sum ^= v[i];
        if (!sum && !(i % 2)) {
            prev = i;
        }
    }
    if (prev == -1) {
        cout << "NO\n";
        return;
    }
    odd(0, prev);
    odd(prev + 1, n - 1);
    cout << "YES\n";
    cout << ans.size() << '\n';
    for (int i: ans) {
        cout << i << " ";
    }
    cout << '\n';
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
