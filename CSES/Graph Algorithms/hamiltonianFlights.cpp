#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <queue>
#include <map>
#define ll signed long long
using namespace std;
const int MOD = 1e9 + 7;
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[v].push_back(u);
    }
    int dp[(1 << n)][n];
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }
    dp[1][0] = 1;
    for (int i = 2; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
            if ((1 << j) & i) {
                for (int k: adj[j]) {
                    dp[i][j] += dp[(i - (1 << j))][k];
                    if (dp[i][j] > MOD) dp[i][j] -= MOD;
                }
            }
        }
    }
    cout << dp[(1 << n) - 1][n - 1];
}
