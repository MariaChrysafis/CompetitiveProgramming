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
    int U, desDist, D, ind;
};
bool comp (Query q1, Query q2) {
    return (q1.desDist < q2.desDist);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    t.adj.resize(n);
    val.resize(n);
    for (int i = 1; i < n; i++) {
        int u;
        cin >> u;
        u--;
        t.adj[u].push_back(i);
        t.adj[i].push_back(u);
    }
    t.read();
    Seg<ll> st;
    st.init(2 * n + 1);
    vector<vector<int>> myMap(n + 2);
    for (int i = 0; i < n; i++) {
        myMap[t.depth[i]].push_back(i);
    }
    int Q;
    cin >> Q;
    vector<Query> queries(Q);
    for (int i = 0; i < Q; i++) {
        cin >> queries[i].U >> queries[i].D;
        queries[i].U--;
        queries[i].desDist = queries[i].D + st.query(t.start[queries[i].U], t.start[queries[i].U]);
        queries[i].ind = i;
    }
    sort(queries.begin(), queries.end(), comp);
    int prev = -1;
    vector<int> nodes;
    vector<int> ans(Q);
    for (int i = 0; i < Q; i++) {
        if (queries[i].desDist != prev) {
            prev = queries[i].desDist;
            for (int node: nodes) {
                st.upd(t.start[node], 0);
            }
            nodes.clear();
            nodes = myMap[queries[i].desDist];
            for (int node: nodes) {
                st.upd(t.start[node], 1);
            }
        }
        ans[queries[i].ind] = st.query(t.start[queries[i].U], t.end[queries[i].U]);
    }
    for (int i: ans) {
        cout << i << '\n';
    }
}
