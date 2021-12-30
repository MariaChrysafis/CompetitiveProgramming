#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;

ll binPow (ll x, ll y, const int mod) {
    ll ans = 1;
    ll res = x;
    ans %= mod, res %= mod;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= mod;
        }
        res *= res, res %= mod;
        y /= 2;
    }
    return ans;
}

const int MOD = 998244353;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll N, K, M;
    cin >> N >> K >> M;
    if (M % MOD == 0) {
        cout << 0;
        return 0;
    }
    cout << binPow(M, binPow(K, N, MOD - 1), MOD);
}
