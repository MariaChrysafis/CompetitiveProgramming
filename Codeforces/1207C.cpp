#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <climits>
#include <vector>
 
#define ll int
 
using namespace std;
 
void solve() {
    unsigned long long n, a, b;
    cin >> n >> a >> b;
    string s;
    cin >> s;
    unsigned long long dp[n + 1][3];
    dp[0][1] = b;
    dp[0][2] = LLONG_MAX;
    for (int i = 1; i <= n; i++) {
        dp[i][1] = dp[i][2] = LLONG_MAX;
        if (s[i - 1] == '0') {
            dp[i][1] = min(dp[i][1], dp[i - 1][1] + a + b);
            dp[i][1] = min(dp[i][1], dp[i - 1][2] + 2 * a + b);
            dp[i][2] = min(dp[i][2], dp[i - 1][2] + a + 2 * b);
            dp[i][2] = min(dp[i][2], dp[i - 1][1] + 2 * (a + b));
        } else {
            dp[i][2] = min(dp[i][2], dp[i - 1][2] + a + 2 * b);
        }
    }
    cout << dp[n][1] << endl;
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
