#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#define ll long long
#pragma GCC optimize("Ofast")
const int MOD = 998244353;
using namespace std;
ll binPow (ll x, ll y) {
    ll ans = 1;
    ll res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res;
            ans %= MOD;
        }
        res *= res;
        res %= MOD;
        y >>= 1;
    }
    return ans;
}
vector<vector<ll>> ch;
ll chose (int i, int j) {
    if (ch[i][j] != -1) {
        return ch[i][j];
    }
    if (j == 0) {
        return (ch[i][j] = 1);
    }
    if (i == 0) {
        return (ch[i][j] = 0);
    }
    return (ch[i][j] = (chose(i - 1, j) + chose(i - 1, j - 1)) % MOD);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, x;
    cin >> n >> x;
    vector<vector<ll>> dp(n + 1);
    ch.resize(n + 1);
    for (int i = 0; i < ch.size(); i++) {
        ch[i].resize(n + 1);
        for (int j = 0; j < ch[i].size(); j++) {
            ch[i][j] = -1;
        }
    }
    for (int i = 0; i < dp.size(); i++) {
        dp[i].resize(x + 1); //all of them are <= x
        for (int j = 0; j <= x; j++) {
            dp[i][j] = 0;
        }
    }
    for (int i = 1; i < dp.size(); i++) {
        for (int j = 1; j < dp[i].size(); j++) {
            dp[i][j] = binPow(min(j, i - 1), i);
        }
    }
    for (int i = 0; i < dp.size(); i++) {
        for (int j = 0; j < dp[i].size(); j++) {
            for (int d = 0; d <= i; d++) {
                if (i - d < 0 || j - (i - 1) < 0) {
                    continue;
                }
                dp[i][j] += ((dp[i - d][j - (i - 1)] * chose(i, d)) % MOD * binPow(i - 1, d)) % MOD;
                dp[i][j] %= MOD;
            }
        }
    }
    cout << dp[n][x];
}
