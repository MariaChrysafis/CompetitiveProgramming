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

#define ll long long
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
using namespace std;
ll MOD = 998244353;

ll mult(ll x, ll y) {
    return (x * y) % MOD;
}

ll binPow(ll x, ll y) {
    ll res = x;
    ll ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans = mult(res, ans);
        }
        res = mult(res, res);
        y /= 2;
    }
    return ans;
}

ll inv(ll x) {
    return binPow(x, MOD - 2);
}

vector<ll> fact = {1};

ll combo(ll x, ll y) {
    if (x < y || x < 0 || y < 0) {
        return 0;
    }
    return mult(fact[x], inv(mult(fact[x - y], fact[y])));
}

int isolate(vector<string> vec, string des) {
    for (auto &s: vec) {
        if (s[0] != '?' && s[0] != des[0]) {
            return 0;
        }
        if (s[1] != '?' && s[1] != des[1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (fact.size() != 2e5 + 1) {
        fact.push_back(mult(fact.back(), fact.size()));
    }
    int n;
    cin >> n;
    vector<string> vec(n);
    map<string, int> oc;
    int q = 0;
    int w = 0;
    int b = 0;
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
        oc["BW/WB"] += (vec[i] == "??");
        oc["BW"] += (vec[i] == "?W" || vec[i] == "B?" || vec[i] == "BW");
        oc["WB"] += (vec[i] == "W?" || vec[i] == "?B" || vec[i] == "WB");
        q += (vec[i][0] == '?');
        q += (vec[i][1] == '?');
        w += (vec[i][0] == 'W');
        w += (vec[i][1] == 'W');
        b += (vec[i][0] == 'B');
        b += (vec[i][1] == 'B');
    }
    ll ans = combo(q, n - w);
    for (auto &s: vec) {
        if (s == "BB" || s == "WW" || n == 1) {
            cout << ans;
            return 0;
        }
    }
    ans = (ans - binPow(2, oc["BW/WB"]) + MOD) % MOD;
    ans += isolate(vec, "WB");
    ans += isolate(vec, "BW");
    cout << ans;

}
