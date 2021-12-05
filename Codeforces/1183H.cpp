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
#include <list>
#include <stack>
#include <algorithm>

#define ll long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    ll dp[n][n + 1]; 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }
    ll ans = 0;
    map<char,vector<int>> lastOc;
    dp[0][0] = 1;
    dp[0][1] = 1;
    lastOc[s[0]].push_back(0);
    for (int i = 1; i < n; i++) {
        for (int len = 1; len <= n; len++) {
            for (int j = 0; j < i; j++) {
                dp[i][len] += dp[j][len - 1];
            }
            for (int in: lastOc[s[i]]) {
                dp[i][len] -= dp[in][len];
            }
            ans += dp[i][len];
        }
        lastOc[s[i]].push_back(i);
    }
    ll sz = 0;
    ll sum = 0;
    for (int len = n; len >= 0; len--) {
        ll cnt = 0;
        for (int j = 0; j < n; j++) {
            cnt += dp[j][len];
        }
        sum += cnt * (n - len);
        sz += cnt;
        if (sz >= k) {
            sz -= cnt;
            sum -= cnt * (n - len);
            cnt = min(cnt, k - sz);
            sum += cnt * (n - len);
            sz += cnt;
            cout << sum;
            return 0;
        }
    }
    cout << "-1\n";

}
