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
    void read(){
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
Tree t;
vector<int> val, cnt;
int memoize (int curNode, int prevNode) {
    val[curNode] = cnt[curNode];
    for (int i: t.adj[curNode]) {
        if (i == prevNode) {
            continue;
        }
        val[curNode] += memoize(i, curNode);
    }
    return val[curNode];
}
int main() {
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    t.adj.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.adj[u].push_back(v), t.adj[v].push_back(u);
    }
    t.read();
    vector<pair<int,int>> queries;
    while (M--) {
        int st, en;
        cin >> st >> en;
        st--, en--;
        if (st == 0 || en == 0) {
            queries.emplace_back(max(st, en), 1);
        } else if (t.isAncestor(st, en)) {
            queries.emplace_back(en, 1);
            queries.emplace_back(t.parent[st], -1);
        } else if (t.isAncestor(en, st)) {
            queries.emplace_back(st, 1);
            queries.emplace_back(t.parent[en], -1);
        } else {
            queries.emplace_back(st, 1);
            queries.emplace_back(en, 1);
            if (t.parent[t.lca(st,en)] != -1) queries.emplace_back(t.parent[t.lca(en, st)], -1);
            queries.emplace_back(t.lca(en, st), -1);
        }
    }
    cnt.assign(N, 0), val.assign(N, 0);
    for (pair<int,int> p: queries) {
        cnt[p.first] += p.second;
    }
    memoize(0, -1);
    int myMax = 0;
    for (int i: val) {
        myMax = max(myMax, i);
    }
    cout << myMax;

}
