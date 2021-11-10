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

struct Tree{
    vector<vector<ll>> adj;
    vector<ll> last, first;
    vector<ll> euler;
    ll counter = 0;
    void pre_euler(){
        euler.resize( 2 * adj.size()), first.resize(adj.size()), last.resize(adj.size());
        dfs(0, -1, 0);
        for (int i = 0; i < adj.size(); i++) {
            euler[first[i]] = i;
            euler[last[i]] = i;
        }
    }
    bool isAncestor (int u, int v) {
        return (first[u] <= first[v] && last[u] >= last[v]);
    }
    void dfs(int node, int parent, int h){
        first[node] = counter++;
        for(int i: adj[node]){
            if(i != parent){
                dfs(i, node, h + 1);
            }
        }
        last[node] = counter++;
    }
};
int main() {
    //freopen("snowcow.in", "r", stdin);
    //freopen("snowcow.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    Seg<ll> st;
    st.init(2 * N + 1);
    vector<int> val(N);
    for (int i = 0; i < N; i++) {
        cin >> val[i];
    }
    Tree t;
    t.adj.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.adj[u].push_back(v);
        t.adj[v].push_back(u);
    }
    t.pre_euler();
    for (int i = 0; i < N; i++) {
        st.upd(t.first[i], val[i]);
        st.upd(t.last[i], -val[i]);
    }
    while (Q--) {
        int tc;
        cin >> tc;
        if (tc == 2) {
            int u;
            cin >> u;
            u--;
            cout << st.query(0, t.first[u]) << '\n';
        } else {
            int u, x;
            cin >> u >> x;
            u--;
            st.upd(t.first[u], x);
            st.upd(t.last[u], -x);
        }
    }

}
