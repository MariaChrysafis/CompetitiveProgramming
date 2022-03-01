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
#include <stack>

using namespace std;
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long ll;
const int INF = 1e9 + 1;
int solve (vector<vector<int>> adj, int k) {
    vector<int> flag(adj.size());
    for (int i = 0; i < adj.size(); i++) {
        flag[i] = rand() % 2;
    }
    int dp[adj.size()][11];
    for (int i = 0; i < adj.size(); i++) {
        for (int j = 0; j < 11; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;
    for (int j = 1; j < 11; j++) {
        for (int i = 0; i < adj.size(); i++) {
            for (int prev = 0; prev < adj.size(); prev++) {
                if (flag[prev] == flag[i]) {
                    continue;
                }
                dp[i][j] = min(dp[i][j], dp[prev][j - 1] + adj[prev][i]);
            }
        }
    }
    return dp[0][k];
}
int main() {
    srand(time(NULL));
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        adj[i].resize(n);
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }
    int t = 10000;
    int ans = INF;
    while (t--) {
        ans = min(ans, solve(adj, k));
    }
    cout << ans;
}
