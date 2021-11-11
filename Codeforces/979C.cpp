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
const int MOD = 998244353;
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
    void read(int rt) {
        dp.resize(adj.size());
        parent.assign(adj.size(), -1);
        start.resize(adj.size()), end.resize(adj.size());
        for (int i = 0; i < adj.size(); i++) {
            dp[i].resize(20);
            for (int j = 0; j < dp[i].size(); j++) {
                dp[i][j] = 0;
            }
        }
        memoize(rt, -1);
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
vector<ll> sub;
Tree t;
ll memoize (int curNode, int prevNode) {
    sub[curNode] = 1;
    for (int i: t.adj[curNode]) {
        if (i != prevNode) {
            sub[curNode] += memoize(i, curNode);
        }
    }
    return sub[curNode];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, x, y;
    cin >> n >> x >> y;
    x--, y--;
    t.adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.adj[u].push_back(v), t.adj[v].push_back(u);
    }
    sub.assign(n, 0);
    t.read(0);
    memoize(0, -1);
    if (t.isAncestor(x, y) || t.isAncestor(y, x)) {
        if (sub[x] > sub[y]) {
            swap(x,y);
        }
        int cntr = 0;
        for (int i = 0; i < n; i++) {
            if (t.isAncestor(t.lca(x, i), y)) {
                cntr++;
            }
        }
        cout << n * (n - 1) - sub[x] * cntr;
        return 0;
    }
    cout << n * (n - 1) - sub[x] * sub[y];
}
