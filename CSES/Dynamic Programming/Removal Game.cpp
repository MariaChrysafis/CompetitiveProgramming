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
vector<vector<int64_t>> dp;
vector<int64_t> arr;
int64_t rec (int i, int j) {
    if (dp[i][j] != -INT_MAX) return dp[i][j];
    return dp[i][j] = max(arr[i] - rec(i + 1, j), arr[j] - rec(i, j - 1));
}
int main() {
    int n; cin >> n;
    dp.assign(n, vector<int64_t>(n)), arr.resize(n);
    int64_t sum = 0;
    for (int i = 0; i < n; i++) {
        dp[i].assign(n, -INT_MAX);
        cin >> arr[i];
        dp[i][i] = arr[i], sum += arr[i];
    }
    cout << (sum + rec(0, n - 1))/2;
}
