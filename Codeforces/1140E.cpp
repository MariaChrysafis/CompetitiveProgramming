#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#define ll long long
using namespace std;

const int MOD = 998244353;
ll mult (ll x, ll y) {
    return (x * y) % MOD;
}
ll add (ll x, ll y) {
    return (x * y) % MOD;
}
ll binPow (ll x, ll y) {
    ll ans = 1;
    ll res = x;
    while (y > 0) {
        if (y % 2 == 1) {
            ans *= res; ans %= MOD;
        }
        res *= res; res %= MOD;
        y /= 2;
    }
    return ans;
}
ll inv (ll x) {
    return binPow(x, MOD - 2);
}
pair<ll,ll> solve (int len, int k) {
    //len occurences of -1, starts and ends at
    ll dp[len + 2][2];
    for (int i = 0; i <= len + 1; i++) {
        for (int j = 0; j < 2; j++) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;
    for (int i = 1; i <= len + 1; i++) {
        dp[i][0] = dp[i - 1][1];
        dp[i][1] = dp[i - 1][0] * (k - 1) + dp[i - 1][1] * (k - 2);
        dp[i][1] %= MOD;
    }
    return {dp[len + 1][0], dp[len + 1][1]};
}

int solve (int len, int k, int start, int end) {
    if (start == -1 && end == -1) {
        return mult(k, binPow(k - 1, len - 1));
    }
    if (start == -1 || end == -1) {
        return binPow(k - 1, len);
    }
    if (start == end) {
        return solve(len, k).first;
    }
    ll x = solve(len, k).second;
    return mult(x, inv(k - 1));
}

int solve (vector<ll> v, int k) {
    for (int i = 0; i < v.size() - 1; i++) {
        if (v[i] == v[i + 1] && v[i] != -1) {
            return 0;
        }
    }
    vector<int> stagnant = {-1};
    for (int i = 0; i < v.size(); i++) {
        if (v[i] != -1) {
            stagnant.push_back(i);
        }
    }
    stagnant.push_back(v.size());
    ll ans = 1;
    for (int i = 1; i < stagnant.size(); i++) {
        int l = stagnant[i - 1] + 1;
        int r = stagnant[i] - 1;
        if (l > r) continue;
        int st = -1;
        if (l != 0) st = v[stagnant[i - 1]];
        int en = -1;
        if (r != v.size() - 1) en = v[stagnant[i]];
        ans = mult(solve(r - l + 1, k, st, en), ans);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<ll> a(n);
    vector<ll> v1, v2;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i % 2 == 0) {
            v1.push_back(a[i]);
        } else {
            v2.push_back(a[i]);
        }
    }
    cout << mult(solve(v2, k), solve(v1, k));
}
