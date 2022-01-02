#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;
const int MOD = 998244353 ;
ll reduce (ll &x) {
    if (x >= 0) {
        return (x %= MOD);
    } else {
        return (x = (MOD - (-x) % MOD) % MOD);
    }
}
ll mult (ll x, ll y) {
    reduce(x), reduce(y);
    return (x * y) % MOD;
}
ll binPow (ll x, ll y) {
    ll ans = 1;
    ll res = x;
    while (y > 0) {
        if (y & 1) {
            ans = mult(ans, res);
        }
        res = mult(res, res);
        y /= 2;
    }
    return ans;
}
ll inv (ll x) {
    return binPow(x, MOD - 2);
}
vector<ll> fact;
ll chose (ll x, ll y) {
    return mult(fact[x], inv(mult(fact[y], fact[x - y])));
}
void pre (ll N) {
    fact = {1};
    while (fact.size() != N + 1) {
        fact.push_back(mult(fact.size(), fact.back()));
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll N, K;
    cin >> N >> K;
    pre(N);
    ll C = N - K;
    if (C < 0) {
        cout << 0;
        return 0;
    }
    ll ans = 0;
    for (int i = 0; i <= C; i++) {
        if ((C - i) % 2 == 0) {
            ans += mult(chose(C, i), binPow(i, N));
        } else {
            ans -= mult(chose(C, i), binPow(i, N));
        }
        reduce(ans);
    }
    ans = mult(ans, chose(N, C));
    if (K != 0) {
        ans = mult(ans, 2);
    }
    cout << ans;
}
