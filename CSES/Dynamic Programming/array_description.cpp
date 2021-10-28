#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
#define ll long long
const int MOD = 1e9 + 7;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    long long dp[n][m + 1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 0;
            if (i == 0) {
                if (arr[0] == 0) {
                    dp[i][j] = 1;
                } else if (j == arr[0] && j != 0) {
                    dp[i][j] = 1;
                }
            }
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] != 0) {
            dp[i][arr[i]] += dp[i - 1][arr[i] - 1] + dp[i - 1][arr[i]];
            if (arr[i] + 1 <= m) dp[i][arr[i]] += dp[i - 1][arr[i] + 1];
            dp[i][arr[i]] %= MOD;
            continue;
        }
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 0;
            if (j != 0) dp[i][j] += dp[i - 1][j - 1];
            dp[i][j] += dp[i - 1][j];
            if (j + 1 <= m) dp[i][j] += dp[i - 1][j + 1];
            dp[i][j] %= MOD;
        }
        dp[i][0] = 0;
    }
    long long ans = 0;
    for (int j = 0; j <= m; j++) {
        //cout << dp[n - 1][j] << " ";
        ans += dp[n - 1][j];
        ans %= MOD;
    }
    cout << ans << endl;
}
