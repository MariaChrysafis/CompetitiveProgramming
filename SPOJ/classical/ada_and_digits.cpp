#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

ll mult (ll x, ll y) {
    x %= MOD, y %= MOD;
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

vector<vector<int>> factorize (int ans, int st) {
    if (ans == 1) {
        vector<int> dum(10);
        return {dum};
    }
    vector<vector<int>> res;
    for (int i = st; i < 10; i++) {
        if (ans % i == 0) {
            vector<vector<int>> vec = factorize(ans/i, i);
            for (vector<int> v: vec) {
                v[i]++;
                res.push_back(v);
            }
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<ll> fact = {1};
    while (fact.size() != 3e5 + 10) {
        fact.push_back(mult(fact.back(), fact.size()));
    }
    vector<ll> fact_inv(fact.size());
    fact_inv[fact_inv.size() - 1] = inv(fact[fact.size() - 1]);
    for (int i = fact_inv.size() - 2; i >= 0; i--) {
        fact_inv[i] = mult(fact_inv[i + 1], i + 1);
    }
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<vector<int>> vec = factorize(N,2);
        for (vector<int> &v: vec) {
            int sum = 0;
            for (int x = 0; x < v.size(); x++) {
                sum += x * v[x];
            }
            while (sum != N) {
                v[1]++;
                sum++;
            }
        }
        ll ans = 0;
        for (vector<int> oc: vec) {
            int tot = 0;
            for (int x: oc) {
                tot += x;
            }
            ll res = fact[tot];
            for (int i = 0; i < oc.size(); i++) {
                res = mult(res, fact_inv[oc[i]]);
            }
            ans += res, ans %= MOD;
        }
        cout << ans << '\n';
    }
}
