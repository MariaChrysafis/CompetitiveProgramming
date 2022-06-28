#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
 
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
 
using namespace std;
const int MOD = 1e9;
 
template<class T>
struct Seg {
    const T ID = 0;
 
    T comb(T a, T b) { return max(a, b); }
 
    int n;
    vector<T> seg;
 
    void init(int _n) {
        n = _n;
        seg.assign(2 * n, ID);
    }
 
    void pull(int p) { seg[p] = comb(seg[2 * p], seg[2 * p + 1]); }
 
    void upd(int p, T val) {
        seg[p += n] = val;
        for (p /= 2; p; p /= 2) pull(p);
    }
 
    T query(int l, int r) {
        T ra = ID, rb = ID;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) ra = comb(ra, seg[l++]);
            if (r & 1) rb = comb(seg[--r], rb);
        }
        return comb(ra, rb);
    }
};
 
class HeavyLightDecomposition {
public:
    vector<vector<int>> adj;
    vector<int> sub;
    vector<int> id;
    vector<int> topchain;
    vector<int> depth;
    vector<int> parent;
    Seg<int64_t> st;
    vector<vector<int>> dp;
    vector<int> en;
    vector<int> ex;
    int cntr = 0;
    const int lg2 = 30;
 
    void add_edge(int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
 
    void rec(int curNode, int prevNode) {
        parent[curNode] = prevNode;
        en[curNode] = cntr++;
        if (prevNode != -1) {
            depth[curNode] = depth[prevNode] + 1;
        } else {
            depth[curNode] = 0;
        }
        sub[curNode] = 1;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                rec(i, curNode);
                sub[curNode] += sub[i];
            }
        }
        ex[curNode] = cntr++;
    }
 
    HeavyLightDecomposition(int n) {
        adj.resize(n);
        sub.resize(n);
        id.resize(n);
        topchain.assign(n, -1);
        parent.resize(n);
        st.init(n + 1);
        ex.resize(n), en.resize(n);
    }
 
    void dfs(int curNode, int prevNode) {
        id[curNode] = cntr++;
        vector<pair<int, int>> vec;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                vec.push_back({sub[i], i});
            }
        }
        dp[curNode].resize(32);
        dp[curNode][0] = max(prevNode, 0);
        for (int i = 1; i < dp[curNode].size(); i++) {
            dp[curNode][i] = dp[dp[curNode][i - 1]][i - 1];
        }
        if (!vec.empty()) {
            sort(vec.begin(), vec.end());
            reverse(vec.begin(), vec.end());
            topchain[vec[0].second] = topchain[curNode];
            for (int i = 1; i < vec.size(); i++) {
                topchain[vec[i].second] = vec[i].second;
            }
            for (auto &p: vec) {
                dfs(p.second, curNode);
            }
        }
    }
 
    int64_t f (int a, int b) {
        if (topchain[a] == topchain[b]) {
            return st.query(id[b], id[a]);
        }
        if (topchain[a] != a) {
            return max(f(parent[topchain[a]], b), st.query(id[topchain[a]], id[a]));
        } else {
            return max(f(parent[a], b), st.query(id[a], id[a]));
        }
    }
 
    bool isAncestor(int u, int v) {
        return (en[u] <= en[v] && ex[u] >= ex[v]);
    }
 
    int leastCommonAncestor(int u, int v) {
        if (isAncestor(u, v)) {
            return u;
        }
        if (isAncestor(v, u)) {
            return v;
        }
        for (int i = lg2; i >= 0; i--) {
            if (!isAncestor(dp[u][i], v)) {
                u = dp[u][i];
            }
        }
        return dp[u][0];
    }
 
    void upd(int ind, int x) {
        st.upd(id[ind], x);
    }
 
    void read(vector<int> arr) {
        depth.resize(adj.size());
        dp.resize(adj.size());
        rec(0, -1); //fill in all of the subtrees
        topchain[0] = 0;
        cntr = 0;
        dfs(0, -1); //fill in all of the ids and stuff
        for (int i = 0; i < arr.size(); i++) {
            upd(i, arr[i]);
        }
    }
};
int main() {
    //freopen("inp.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    vector<pair<int, int>> vec;
    HeavyLightDecomposition hld(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        hld.add_edge(--u, --v);
    }
    hld.read(arr);
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int s, x;
            cin >> s >> x;
            s--;
            hld.upd(s, x);
        } else {
            int x, y;
            cin >> x >> y;
            x--, y--;
            cout << max(hld.f(x, hld.leastCommonAncestor(x, y)), hld.f(y, hld.leastCommonAncestor(x, y))) << ' ';
        }
    }
}
