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
vector<vector<ll>> dp;
vector<int> arr;
const int MOD = 1e9 + 7;
ll memoize (int i, int j) {
    if (dp[i][j] != (int)1e9) {
        return dp[i][j];
    }
    if (i == j) {
        return (dp[i][j] = 1);
    }
    if (i > j) {
        return (dp[i][j] = (int)1e9);
    }
    if (j - i == 1 && arr[i] == arr[j]) {
        return (dp[i][j] = 1);
    } else if (j - i == 1) {
        return (dp[i][j] = 2);
    }
    dp[i][j] = memoize(i + 1, j) + 1;
    if (arr[i] == arr[j]) {
        dp[i][j] = min(dp[i][j], memoize(i + 1, j - 1));
    }
    if (i + 1 != arr.size() && arr[i] == arr[i + 1]) {
        dp[i][j] = min(memoize(i + 2, j) + 1, dp[i][j]);
    }
    for (int k = i + 2; k <= j - 1; k++) {
        if (arr[k] == arr[i]) {
            dp[i][j] = min(dp[i][j], memoize(i + 1, k - 1) + memoize(k + 1, j));
        }
    }
    return dp[i][j];
}
int main() {
    int n;
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(n);
        for (int j = 0; j < n; j++) {
            dp[i][j] = (int)1e9;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = memoize(i, j);
        }
    }
    cout << dp[0][n - 1];
}
