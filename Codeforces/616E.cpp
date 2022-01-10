#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <set>
#include <map>
#include <algorithm>
#include <ctime>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long ll;

const ll MOD = 1e9 + 7;

using namespace std;

ll mult (ll x, ll y) {
    return (x * y) % MOD;
}

ll binPow (ll x, ll y) {
    ll res = x;
    ll ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res, res %= MOD;
        y /= 2;
    }
    return ans;
}

ll inv (ll x) {
    return binPow(x, MOD - 2);
}

ll frac (ll a, ll b) {
    return mult(a, inv(b));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, m;
    cin >> n >> m;
    ll ans = ((n % MOD) * (m % MOD)) % MOD;
    vector<ll> mySet;
    for (ll i = 1; i * i <= n; i++) {
        mySet.push_back(n/i);
        if (i != n/i) mySet.push_back(i);
    }
    for (ll x: mySet) {
        ll l = (n + x + 1)/(x + 1);
        ll r = n/x;
        r = min(r, m);
        if (l > r) continue;
        l %= MOD, r %= MOD;
        ans -= mult(x, mult(r + l, frac(r - l + 1, 2)));
        ans += MOD, ans %= MOD;
    }
    cout << ans;

}
