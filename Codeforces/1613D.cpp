#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bit>
#include <bitset>
#include <map>
#include <algorithm>
#define ll long long
using namespace std;
const int MOD = 998244353;
void solve() {
    int n;
    cin >> n;
    ll dp[n + 2][3]; //0 means that we haven't reached
    for (int i = 0; i <= n + 1; i++) {
        dp[i][0] = dp[i][1] = dp[i][2] = 0;
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]++;
    }
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        dp[a[i]][0] += dp[a[i]][0];
        dp[a[i]][0] += dp[a[i] - 1][0];
        dp[a[i]][1] += dp[a[i]][1];
        dp[a[i]][2] += dp[a[i]][2];
        if (a[i] - 2 >= 0) dp[a[i]][2] += dp[a[i] - 2][0];
        if (a[i] + 2 <= n + 1) dp[a[i]][1] += dp[a[i] + 2][2];
        if (a[i] - 2 >= 0) dp[a[i]][2] += dp[a[i] - 2][1];
        dp[a[i]][1] %= MOD, dp[a[i]][0] %= MOD, dp[a[i]][2] %= MOD;
    }
    ll ans = 0;
    for (int i = 0; i <= n + 1; i++) {
        ans += dp[i][0] + dp[i][1] + dp[i][2];
        //cout << dp[i][0] << " " << dp[i][1] << '\n';
        ans %= MOD;
    }
    cout << (ans + MOD - 1) % MOD << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
