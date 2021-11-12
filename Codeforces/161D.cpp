#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

#define ll long long

using namespace std;
vector<vector<int>> adj;
vector<vector<ll>> dp;
vector<int> parent;
void dfs (int curNode, int prevNode) {
    parent[curNode] = prevNode;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            dfs(i, curNode);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K;
    cin >> N >> K;
    adj.resize(N);
    dp.resize(N);
    parent.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    dfs(0, -1);
    for (int i = 0; i < N; i++) {
        dp[i].assign(K + 1, 0);
        dp[i][0] = 1;
    }
    for (int len = 1; len <= K; len++) {
        for (int i = 0; i < N; i++) {
            for (int j: adj[i]) {
                if (j != parent[i]) {
                    dp[i][len] += dp[j][len - 1];
                }
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        for (int x = 0; x <= K; x++) {
            ans += dp[i][x] * dp[i][K - x];
            for (int j: adj[i]) {
                if (x != 0 && x != K && j != parent[i]) {
                    ans -= dp[j][x - 1] * dp[j][K - x - 1];
                }
            }
        }
    }
    cout << ans/2;
}
