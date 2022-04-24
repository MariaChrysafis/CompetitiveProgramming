#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>
#include <climits>
#include <cmath>
#include <set>
using namespace std;
const int64_t MOD = 1e9 + 7;
int main() {
    int64_t n = 1e6 + 1;
    vector<int64_t> powr = {1};
    while (powr.size() != n + 10) {
        powr.push_back(powr.back() * 3);
        powr.back() %= MOD;
    }
    int64_t dp[n + 1];
    dp[0] = 1;
    dp[1] = 2;
    int64_t sum = 0;
    for (int64_t i = 2; i <= n; i++) {
        dp[i] = (5 * dp[i - 1]) % MOD - (2 + 2 * sum) % MOD + MOD;
        dp[i] %= MOD;
        sum += dp[i - 1], sum %= MOD;
    }
    int t;
    cin >> t;
    while (t--) {
        int x;
        cin >> x;
        cout << dp[x] << '\n';
    }
}
