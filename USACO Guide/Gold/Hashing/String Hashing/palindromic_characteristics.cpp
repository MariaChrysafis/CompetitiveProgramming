#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

#define ll long long

using namespace std;
const int MOD = (int) 1e9 + 7;

ll add(ll x, ll y) {
    return (x + y) % MOD;
}

ll mult(ll x, ll y) {
    return (x * y) % MOD;
}

ll binPow(ll x, ll y) {
    ll ans = 1;
    ll res = x;
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

vector<ll> pref, suf;

ll f(ll x, ll y) {
    //find the answer from x to y
    ll ans = pref[y + 1] - mult(pref[x], binPow(27, y - x + 1)) + MOD;
    ans %= MOD;
    return ans;
}

ll g(ll x, ll y) {
    ll ans = suf[x] - mult(suf[y + 1], binPow(27, y - x + 1)) + MOD;
    ans %= MOD;
    return ans;
}

vector<vector<ll>> dp;

ll memoize(int i, int j) {
    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    if (i > j) {
        return (dp[i][j] = 0);
    }
    if (i == j) {
        return (dp[i][j] = 1);
    }
    int sz = (j - i - 1)/2;
    int left = f(i, i + sz);
    int right = g(j - sz, j);
    if (left != right) {
        return (dp[i][j] = 0);
    }
    left = memoize(i, i + sz);
    right = memoize(j - sz, j);
    return (dp[i][j] = min(left, right) + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    //hashing
    pref.push_back(0);
    for (int i = 0; i < s.length(); i++) {
        pref.push_back(add(mult(pref.back(), 27), s[i] - 'a' + 1));
    }
    reverse(s.begin(), s.end());
    suf.push_back(0);
    for (int i = 0; i < s.length(); i++) {
        suf.push_back(add(mult(suf.back(), 27), s[i] - 'a' + 1));
    }
    reverse(s.begin(), s.end()), reverse(suf.begin(), suf.end());
    dp.resize(s.length());
    for (int i = 0; i < s.length(); i++) {
        dp[i].assign(s.length(), -1);
    }
    vector<int> cnt(dp.size() + 1);
    cnt.assign(dp.size() + 1, 0);
    for (int i = 0; i < dp.size(); i++) {
        for (int j = 0; j < dp[i].size(); j++) {
            memoize(i, j);
            cnt[dp[i][j]]++;
        }
    }
    reverse(cnt.begin(), cnt.end());
    vector<int> pref = {0};
    for (int i = 0; i < cnt.size(); i++) {
        pref.push_back(pref.back() + cnt[i]);
    }
    reverse(pref.begin(), pref.end());
    for (int i = 1; i < pref.size() - 1; i++) {
        cout << pref[i] << ' ';
    }
}
