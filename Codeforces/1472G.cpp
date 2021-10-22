#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <vector>
#include <queue>
#include <map>
using namespace std;
struct Graph {
    vector<vector<int>> adj;
    vector<int> bfs() {
        int strt = 0;
        vector<int> hasVisited(adj.size());
        for (int i = 0; i < adj.size(); i++) {
            hasVisited[i] = 0;
        }
        queue<pair<int,int>> q;
        q.push({strt, 1});
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            if (hasVisited[p.first]) {
                continue;
            }
            hasVisited[p.first] = p.second;
            for (int i: adj[p.first]) {
                q.push(make_pair(i, p.second + 1));
            }
        }
        for (int i = 0; i < hasVisited.size(); i++) {
            hasVisited[i]--;
        }
        return hasVisited;
    }
};
Graph g;
vector<int> dp;
vector<int> d;
int memoize (int curNode) {
    if (dp[curNode] != (int)1e9) {
        return dp[curNode];
    }
    dp[curNode] = d[curNode];
    for (int i: g.adj[curNode]) {
        if (d[i] > d[curNode]) {
            dp[curNode] = min(memoize(i), dp[curNode]);
        } else {
            dp[curNode] = min(dp[curNode], d[i]);
        }
    }
    return dp[curNode];
}
void solve() {
    int n;
    cin >> n;
    int m;
    cin >> m;
    g.adj.clear();
    g.adj.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g.adj[u].push_back(v);
    }
    d = g.bfs();
    dp.resize(n);
    for (int i = 1; i < n; i++) {
        dp[i] = (int)1e9;
    }
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        cout << memoize(i) << " ";
    }
    cout << endl;
}
int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
