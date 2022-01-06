#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>

using namespace std;
typedef long long ll;
struct Grid {
    vector<vector<ll>> grid;
    vector<vector<ll>> sums;
    ll find_sum (int l1, int r1, int l2, int r2) {
        return sums[l2 + 1][r2 + 1] - sums[l2 + 1][r1] - sums[l1][r2 + 1] + sums[l1][r1];
    }
    void fill () {
        sums.resize(grid.size() + 1);
        for (int i = 0; i < sums.size(); i++) {
            sums[i].resize(grid[0].size() + 1);
        }
        sums[0][0] = 0;
        for (int i = 1; i < sums.size(); i++) {
            sums[i][0] = 0;
        }
        for (int i = 1; i < sums[0].size(); i++) {
            sums[0][i] = 0;
        }
        for (int i = 1; i < sums.size(); i++) {
            for (int j = 1; j < sums[0].size(); j++) {
                sums[i][j] = sums[i][j - 1] + sums[i - 1][j] - sums[i - 1][j - 1] + grid[i - 1][j - 1];
            }
        }
    }
    void resz (int n, int m) {
        grid.resize(n);
        for (int i = 0; i < n; i++) {
            grid[i].resize(m);
        }
    }
};
Grid myGrid;
int dp[50][50][50][50];
int memoize (int x1, int y1, int x2, int y2) {
    if (dp[x1][y1][x2][y2] != 1e9) {
        return dp[x1][y1][x2][y2];
    }
    if (myGrid.find_sum(x1, y1, x2, y2) == 0) {
        return (dp[x1][y1][x2][y2] = 0);
    }
    dp[x1][y1][x2][y2] = max(x2 - x1 + 1, y2 - y1 + 1);
    for (int i = x1 + 1; i <= x2; i++) {
        dp[x1][y1][x2][y2] = min(dp[x1][y1][x2][y2], memoize(x1, y1, i - 1, y2) + memoize(i, y1, x2, y2));
    }
    for (int i = y1 + 1; i <= y2; i++) {
        dp[x1][y1][x2][y2] = min(dp[x1][y1][x2][y2], memoize(x1, y1, x2, i - 1) + memoize(x1, i, x2, y2));
    }
    return dp[x1][y1][x2][y2];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    myGrid.resz(n, n);
    vector<string> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        for (int j = 0; j < n; j++) {
            myGrid.grid[i][j] = (arr[i][j] == '#');
        }
    }
    myGrid.fill();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    dp[i][j][k][l] = 1e9;
                }
            }
        }
    }
    cout << memoize(0, 0, n - 1, n - 1);
}
