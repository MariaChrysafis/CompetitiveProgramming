#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#define ll signed long long
#pragma GCC optimize("Ofast")
using namespace std;
ll powr (ll x) {
    ll ans = 1;
    while (x--) {
        ans *= 10ll;
    }
    return ans;
}
void solve() {
    ll n, k;
    cin >> n >> k;
    k++;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] = powr(a[i]);
    }
    ll res = 0;
    for (int i = 0; i < n; i++) {
        ll cnt = k;
        if (i + 1 < n) {
            cnt = min(cnt, a[i + 1]/a[i] - 1);
        }
        res += a[i] * cnt;
        k -= cnt;
    }
    cout << res << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
