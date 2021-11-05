#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <ctime>
#include <set>
#include <algorithm>
#include <iomanip>
#define ll long long
using namespace std;
struct Edge {
    int weight;
    int neighbor;
};
vector<vector<Edge>> adj, inv_adj;
vector<bool> hasVisited;
vector<int> dp;
int memoize (int curNode) {
    if (hasVisited[curNode]) {
        return dp[curNode];
    }
    for (Edge e: inv_adj[curNode]) {
        dp[curNode] = max(dp[curNode], memoize(e.neighbor) + e.weight);
    }
    hasVisited[curNode] = true;
    return dp[curNode];
}
int main() {
    freopen("timeline.in", "r", stdin);
    freopen("timeline.out", "w", stdout);
    int N, M, C;
    cin >> N >> M >> C;
    inv_adj.resize(N), adj.resize(N), dp.resize(N);
    hasVisited.assign(N, false);
    for (int i = 0; i < N; i++) {
        cin >> dp[i];
    }
    for (int i = 0; i < C; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back({w, v});
        inv_adj[v].push_back({w, u});
    }
    for (int i = 0; i < N; i++) {
        dp[i] = memoize(i);
        cout << dp[i] << '\n';
    }
}
