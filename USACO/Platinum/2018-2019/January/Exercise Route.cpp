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
class Tree {
public:
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    vector<int> pre, post;
    int cntr = 0;
    void dfs (int curNode, int prevNode) {
        pre[curNode] = cntr++;
        dp[curNode][0] = prevNode;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs(i, curNode);
            }
        }
        post[curNode] = cntr++;
    }
public:
    vector<int> depth;
    Tree (int n) {
        adj.resize(n), pre.resize(n), post.resize(n), dp.resize(n, (vector<int>(log2(n) + 1)));
    }
    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
    int isAncestor (int u, int v) {
        return (pre[u] <= pre[v] && post[u] >= post[v]);
    }
    int lca (int u, int v) {
        if (isAncestor(u, v)) {
            return u;
        }
        if (isAncestor(v, u)) {
            return v;
        }
        for (int i = dp[u].size() - 1; i >= 0; i--) {
            if (!isAncestor(dp[u][i], v)) {
                u = dp[u][i];
            }
        }
        return dp[u][0];
    }
    int child (int u, int v) {
        if (u == v) return -1;
        assert(isAncestor(u, v));
        for (int i = dp[0].size() - 1; i >= 0; i--) {
            if (!isAncestor(dp[v][i], u)) {
                v = dp[v][i];
            }
        }
        return v;
    }
    void read() {
        dfs(0, 0);
        for (int j = 1; j < dp[0].size(); j++) {
            for (int i = 0; i < dp.size(); i++) {
                dp[i][j] = dp[dp[i][j - 1]][j - 1];
            }
        }
        queue<pair<int,int>> q;
        q.push(make_pair(0, 0));
        depth.assign(adj.size() , -1);
        while (!q.empty()) {
            pair<int,int> p = q.front();
            q.pop();
            depth[p.first] = p.second;
            for (int i: adj[p.first]) {
                if (depth[i] == -1) {
                    depth[i] = p.second + 1;
                    q.push(make_pair(i, p.second + 1));
                }
            }
        }
    }
};
template<class T>
class SegmentTree {
public:

    SegmentTree (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, ID);
    }

    void update (int x, T y) {
        x += N - 1;
        val[x] += y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
        }
    }

    T query (int ind, const int l, const int r, int tl, int tr) {
        if (tl >= l && tr <= r) {
            return val[ind];
        }
        if (tr < l || tl > r) {
            return ID;
        }
        return merge(query(2 * ind + 1, l, r, tl, (tl + tr)/2), query(2 * ind + 2, l, r, (tl + tr)/2 + 1, tr));
    }

    T query (int l, int r) {
        return query(0, l, r, 0, N - 1);
    }
private:
    vector<T> val;
    T ID = 0;
    T merge (T x, T y) {
        return x + y;
    }
    int N;
};
int64_t ans = 0;
void dfs (Tree&t, vector<vector<int>>& edges, SegmentTree<int>&st, int curNode, int prevNode) {
    //edges maps a starting point to the ending point
    map<int,int64_t> cnt;
    for (int i: edges[curNode]) {
        cnt[t.pre[t.child(curNode, i)]]++;
        ans += st.query(t.pre[t.child(curNode, i)], t.post[t.child(curNode, i)]);
    }
    for (auto& p: cnt) {
        ans += p.second * (p.second - 1)/2;
    }
    for (int i: edges[curNode]) {
        st.update(t.pre[i], 1);
    }
    for (int i: t.adj[curNode]) {
        if (i != prevNode) {
            dfs (t, edges, st, i, curNode);
        }
    }
}
int64_t countIntersections (Tree&t, vector<vector<int>> edges) {
    //create an euler tour
    SegmentTree<int> st(2 * (int)t.adj.size());
    dfs(t, edges, st, 0, 0);
    return ans;
}
int main() {
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
    int n;
    cin >> n;
    Tree t(n);
    int m;
    cin >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t.add_edge(--u, --v);
    }
    t.read();
    vector<vector<int>> edges(n);
    map<pair<int,pair<int,int>>,int64_t> cnt;
    for (int i = n - 1; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (t.lca(u, v) != u) edges[t.lca(u, v)].push_back(u);
        if (t.lca(u, v) != v) edges[t.lca(u, v)].push_back(v);
        int x = t.child(t.lca(u, v), u);
        int y = t.child(t.lca(u, v), v);
        if (!t.isAncestor(u, v) && !t.isAncestor(v, u)) cnt[make_pair(t.lca(u, v), make_pair(min(x, y), max(x, y)))]++;
    }
    for (auto& p: cnt) {
        ans -= (p.second - 1) * p.second/2;
    }
    cout << countIntersections(t, edges) << '\n';
}
