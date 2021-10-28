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
    int n;
    cin >> n;
    char arr[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    ll dp[n][n];
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = (arr[i][j] == '.');
                continue;
            }
            if (arr[i][j] == '*') {
                dp[i][j] = 0;
                continue;
            }
            dp[i][j] = 0;
            if (i != 0) dp[i][j] += dp[i - 1][j];
            if (j != 0) dp[i][j] += dp[i][j - 1];
            dp[i][j] %= MOD;
        }
    }
    cout << dp[n - 1][n - 1];
}
