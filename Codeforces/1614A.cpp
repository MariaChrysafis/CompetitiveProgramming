#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;

void solve() {
    ll n, l, r, k;
    cin >> n >> l >> r >> k;
    vector<ll> a(n);
    vector<ll> chocolates;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] >= l && a[i] <= r) {
            chocolates.push_back(a[i]);
        }
    }
    sort(chocolates.begin(), chocolates.end());
    ll cnt = 0;
    ll cur = 0;
    for (int i = 0; i < chocolates.size(); i++) {
        if (chocolates[i] + cur <= k) {
            cur += chocolates[i], cnt++;
        } else {
            break;
        }
    }
    cout << cnt << '\n';
}

int main()  {
        int t;
        cin >> t;
        while (t--) {
            solve();
        }
}
