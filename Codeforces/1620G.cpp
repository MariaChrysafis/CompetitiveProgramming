#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
typedef long long ll;
const int MOD = 998244353;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    vector<string> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    ll f[(1 << n)];
    ll g[(1 << n)];
    for (int i = 0; i < (1 << n); i++) {
        f[i] = g[i] = 0;
    }
    ll oc[n][26];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 26; j++) {
            oc[i][j] = 0;
        }
        for (char c: v[i]) {
            oc[i][c - 'a']++;
        }
    }
    for (int i = 1; i < (1 << n); i++) {
        vector<ll> min_oc;
        min_oc.assign(26, 1e9);
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                for (int k = 0; k < 26; k++) {
                    min_oc[k] = min(min_oc[k], oc[j][k]);
                }
            }
        }
        ll ans = 1;
        for (int j: min_oc) {
            ans *= (j + 1);
            ans %= MOD;
        }
        f[i] = ans * pow(-1, __builtin_popcount(i) + 1);
        if (f[i] < 0) {
            f[i] = MOD + f[i];
        }
        f[i] %= MOD;
    }
    for (int i = 0; i < (1 << n); ++i) {
        g[i] = f[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int mask = 0; mask < (1 << n); ++mask) {
            if (mask & (1 << i)) {
                g[mask] += g[mask ^ (1 << i)];
                g[mask] %= MOD;
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < (1 << n); i++) {
        ll res = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                res += __builtin_popcount(i) * (j + 1);
            }
        }
        ans ^= (res * g[i]);
    }
    cout << ans << '\n';
}
