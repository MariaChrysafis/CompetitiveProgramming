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
    int n = 501;
    int dp[n][n];
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i == j) {
                dp[i][j] = 0;
                continue;
            }
            dp[i][j] = INT_MAX;
            for (int k = 1; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j - k] + 1);
            }
            for (int k = 1; k < i; k++) {
                dp[i][j] = min(dp[i][j], dp[k][j] + dp[i - k][j] + 1);
            }
        }
    }
    int a, b;
    cin >> a >> b;
    cout << dp[a][b];
}
