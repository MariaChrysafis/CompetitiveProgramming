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
vector<int> v;
vector<vector<int>> dp;
int memoize (int x, int y) {
    if (dp[x][y] != -1) {
        return dp[x][y];
    }
    if (x == y) {
        return v[x];
    }
    if (x > y) {
        return 0;
    }
    dp[x][y] = 0;
    for (int i = x; i <= y - 1; i++) {
        int a = memoize(x, i);
        int b = memoize(i + 1, y);
        if (a == b && a != 0) {
            dp[x][y] = max(dp[x][y], a + 1);
        }
    }
    return dp[x][y];
}
int main() {
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    int n;
    cin >> n;
    v.resize(n);
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        dp[i].resize(n);
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }
    int myMax = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = memoize(i, j);
            myMax = max(myMax, dp[i][j]);
        }
    }
    cout << myMax;
}
