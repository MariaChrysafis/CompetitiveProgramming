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
const int MOD = 1e9 + 7;

void reduce (ll &x) {
    if (x >= 0) {
        x %= MOD;
        return;
    }
    x = (MOD - abs(x) % MOD) % MOD;
}

ll mult (ll x, ll y) {
    reduce(x), reduce(y);
    ll alpha = x * y;
    reduce(alpha);
    return alpha;
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

//vector<pair<int,int>> will contain the exponent followed by the coefficient
void multiply_polynomial (vector<pair<ll,ll>> &v1, vector<pair<ll,ll>> &v2) {
    map<ll,ll> poly;
    for (auto& p1: v1) {
        for (auto& p2: v2) {
            poly[p1.first + p2.first] += p1.second * p2.second;
            reduce(poly[p1.first + p2.first]);
        }
    }
    v1.clear();
    for (auto& p: poly) {
        v1.push_back(p);
    }
}

ll binom (ll x, ll y) {
    assert(abs(x - y) <= 20 && x >= y);
    ll ans = 1;
    for (ll i = y + 1; i <= x; i++) {
        ans = mult(ans, i);
    }
    ll fact = 1;
    for (ll i = 1; i <= x - y; i++) {
        fact *= i;
    }
    ans = mult(ans, inv(fact));
    return ans;
}

ll get (ll exp, ll i) {
    return binom(i + exp - 1, i);
}

int main() {
    ll n, s;
    cin >> n >> s;
    vector<ll> f(n);
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }
    vector<pair<ll,ll>> poly = {{0, 1}};
    for (ll i: f) {
        vector<pair<ll,ll>> v1 = {{i + 1, -1}, {0, 1}};
        multiply_polynomial(poly, v1);
    }
    ll ans = 0;
    for (auto& p: poly) {
        if (s - p.first >= 0) {
            ans += mult(get(n, s - p.first), p.second);
        }
        reduce(ans);
    }
    cout << ans;
}
