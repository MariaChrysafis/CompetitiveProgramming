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
vector<int> val;
struct Tree {
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    vector<int> parent;
    vector<int> start, end, depth;
    vector<int> howFar;
    int cntr = 0;
    void memoize (int curNode, int prevNode) {
        start[curNode] = cntr++;
        parent[curNode] = prevNode;
        if (curNode == 0) {
            depth[curNode] = 0;
        } else {
            depth[curNode] = depth[prevNode] + 1;
        }
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
    int memoize1 (int curNode) {
        if (howFar[curNode] != -1) {
            return howFar[curNode];
        }
        if (curNode == 0 || val[parent[curNode]] != val[curNode]) {
            return (howFar[curNode] = 0);
        }
        return memoize1(parent[curNode]) + 1;
    }
    void read(){
        depth.resize(adj.size());
        dp.resize(adj.size());
        parent.resize(adj.size());
        start.resize(adj.size()), end.resize(adj.size());
        howFar.assign(adj.size(), -1);
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
        for (int i = 0; i < adj.size(); i++) {
            howFar[i] = memoize1(i);
        }
    }
};
template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 0; T comb(T a, T b) { return a+b; }
    int n; vector<T> seg;
    void init(int _n) { n = _n; seg.assign(2*n,ID); }
    void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
    void upd(int p, T val) { // set val at position p
        seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
    T query(int l, int r) {	// sum on interval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l&1) ra = comb(ra,seg[l++]);
            if (r&1) rb = comb(seg[--r],rb);
        }
        return comb(ra,rb);
    }
};
Tree t;
struct Query {
    int l, r, ind, c;
};
bool comp (Query q1, Query q2) {
    return (q1.c < q2.c);
}
int main() {
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    t.adj.resize(n);
    val.resize(n);
    vector<vector<int>> myMap(n + 2);
    for (int i = 0; i < n; i++) {
        cin >> val[i];
        val[i]--;
        myMap[val[i]].push_back(i);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.adj[u].push_back(v);
        t.adj[v].push_back(u);
    }
    t.read();
    vector<int> euler(2 * n);
    for (int i = 0; i < n; i++) {
        euler[t.start[i]] = euler[t.end[i]] = i;
    }
    vector<Query> v(q);
    for (int i = 0; i < q; i++) {
        v[i].ind = i;
        cin >> v[i].l >> v[i].r >> v[i].c;
        v[i].l--, v[i].r--, v[i].c--;
    }
    Seg<int> st;
    st.init(2 * n);
    sort(v.begin(), v.end(), comp);
    int prev = -1;
    vector<pair<int,int>> s;
    int ans[q];
    for (int i = 0; i < q; i++) {
        if (v[i].c != prev) {
            prev = v[i].c;
            for (auto p: s) {
                st.upd(p.first, 0);
                st.upd(p.second, 0);
            }
            s.clear();
            for (int j: myMap[v[i].c]) {
                st.upd(t.start[j], 1);
                st.upd(t.end[j], -1);
                s.push_back({t.start[j], t.end[j]});
            }
        }
        int lca = t.lca(v[i].l, v[i].r);
        ans[v[i].ind] = st.query(t.start[lca], t.start[v[i].r]) + st.query(t.start[lca], t.start[v[i].l]);
    }
    for (int i: ans) {
        cout << (bool)i;
    }
}
