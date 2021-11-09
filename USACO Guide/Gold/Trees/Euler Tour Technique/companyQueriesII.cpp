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
#define ll long long
#include <map>
 
using namespace std;
struct Tree {
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    vector<int> parent;
    vector<int> start, end;
    int cntr = 0;
    void memoize (int curNode, int prevNode) {
        start[curNode] = cntr++;
        parent[curNode] = prevNode;
        for (int i: adj[curNode]) {
            if (i == prevNode) {
                continue;
            }
            memoize(i, curNode);
        }
        end[curNode] = cntr++;
    }
    int isAncestor (int u, int v) {
        return (start[u] <= start[v] && end[u] >= end[v]);
    }
    int lca (int u, int v) {
        if (isAncestor(u, v)) {
            return u;
        }
        if (isAncestor(v, u)) {
            return v;
        }
        for (int i = 19; i >= 0; i--) {
            if (!isAncestor(dp[u][i], v)) {
                u = dp[u][i];
            }
        }
        return dp[u][0];
    }
    void read() {
        dp.resize(adj.size());
        parent.resize(adj.size());
        start.resize(adj.size()), end.resize(adj.size());
        for (int i = 0; i < adj.size(); i++) {
            dp[i].resize(20);
            for (int j = 0; j < dp[i].size(); j++) {
                dp[i][j] = 0;
            }
        }
        memoize(0, -1);
        for (int j = 0; j < 20; j++) {
            for (int i = 0; i < adj.size(); i++) {
                if (j == 0) {
                    dp[i][j] = parent[i];
                    if (dp[i][j] == -1) dp[i][j] = 0;
                } else {
                    dp[i][j] = dp[dp[i][j - 1]][j - 1];
                }
            }
        }
    }
};
int main() {
    Tree t;
    int n;
    cin >> n;
    int q;
    cin >> q;
    t.adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int x;
        cin >> x;
        x--;
        t.adj[i + 1].push_back(x);
        t.adj[x].push_back(i + 1);
    }
    t.read();
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << t.lca(--a, --b) + 1 << '\n';
    }
 
 
}
