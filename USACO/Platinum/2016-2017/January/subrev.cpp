#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

using namespace std;
const int INF = 100000;

vector<vector<vector<vector<int>>>> dp;
vector<int> arr;

int rec (int i, int j, int x, int y) {
    if (i < 0 || j < 0 || i == dp.size() || j == dp.size() || i > j || x > y) {
        return 0;
    }
    if (dp[i][j][x][y] != -1) {
        return dp[i][j][x][y];
    }
    if (i == j) {
        return (dp[i][j][x][y] = (arr[i] >= x && arr[i] <= y));
    }
    dp[i][j][x][y] = 0;
    dp[i][j][x][y] = max(dp[i][j][x][y], rec(i + 1, j, x, y));
    dp[i][j][x][y] = max(dp[i][j][x][y], rec(i, j - 1, x, y));
    bool bi = (arr[i] >= x && arr[i] <= y);
    bool bj = (arr[j] >= x && arr[j] <= y);
    if (bi) {
        dp[i][j][x][y] = max(dp[i][j][x][y], rec(i + 1, j, arr[i], y) + 1);
        dp[i][j][x][y] = max(dp[i][j][x][y], rec(i + 1, j - 1, x, arr[i]) + 1);
    }
    if (bj) {
        dp[i][j][x][y] = max(dp[i][j][x][y], rec(i, j - 1, x, arr[j]) + 1);
        dp[i][j][x][y] = max(dp[i][j][x][y], rec(i + 1, j - 1, arr[j], y) + 1);
    }
    if (bi && bj && arr[i] >= arr[j]) {
        dp[i][j][x][y] = max(dp[i][j][x][y], rec(i + 1, j - 1, arr[j], arr[i]) + 2);
    }
    return dp[i][j][x][y];
}

int main() {
    freopen("subrev.in", "r", stdin);
    freopen("subrev.out", "w", stdout);
    int N;
    cin >> N;
    arr.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    dp.resize(N);
    for (int i = 0; i < N; i++) {
        dp[i].resize(N);
        for (int j = 0; j < N; j++) {
            dp[i][j].resize(51);
            for (int k = 0; k < dp[i][j].size(); k++) {
                dp[i][j][k].assign(51, -1);
            }
        }
    }
    int myMax = 0;
    for (int i = 0; i < dp.size(); i++) {
        for (int j = 0; j < dp[i].size(); j++) {
            for (int k = 0; k < dp[i][j].size(); k++) {
                for (int l = 0; l < dp[i][j][k].size(); l++) {
                    dp[i][j][k][l] = rec(i, j, k, l);
                    myMax = max(myMax, dp[i][j][k][l]);
                }
            }
        }
    }
    cout << myMax;
}
