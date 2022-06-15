#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int64_t dp[n + 1][3];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            dp[i][j] = -(int64_t)1e16;
        }
    }
    int64_t arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    dp[0][1] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - arr[i - 1]);
        dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + arr[i - 1]);
        dp[i][1] = max(dp[i - 1][1], max(dp[i - 1][0] + arr[i - 1], dp[i - 1][2] - arr[i - 1]));
    }
    cout << dp[n][1];
}
