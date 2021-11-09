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
#define ll int
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
void distinctValues(vector<int>& v, vector<vector<pair<int,int>>> &queries, int &q) {
    int n = v.size();
    map<int,set<int>> myMap;
    for (int i = 0; i < n; i++) {
        myMap[v[i]].insert(i);
    }
    vector<vector<int>> oc(n + 1);
    for (int i = 0; i < n; i++) {
        if (myMap[v[i]].upper_bound(i) == myMap[v[i]].end()) {
            v[i] = n;
        } else {
            v[i] = *myMap[v[i]].upper_bound(i);
        }
        oc[v[i]].push_back(i);
    }
    Seg<int> st;
    st.init(n + 10);
    vector<int> ans(q);
    for (int i = n; i >= 0; i--) {
        for (auto& p: queries[i]) {
            ans[p.second] = st.query(p.first, i);
        }
        for (auto &j: oc[i]) {
            st.upd(j, 1);
        }
    }
    for (auto& i: ans) {
        cout << i << " ";
    }
    cout << '\n';
}
struct Tree{
    vector<vector<int>> adj;
    vector<ll> first, last;
    vector<ll> dist;
    vector<ll> sub;
    ll counter = 0;
    void pre_euler(){
        first.resize(adj.size());
        last.resize(adj.size());
        dist.assign(adj.size(), -1);
        sub.resize(adj.size());
        dfs(0, -1);
    }
    void dfs(ll node, ll parent){
        first[node] = counter++;
        for(int i: adj[node]){
            if(i != parent){
                dfs(i, node);
            }
        }
        last[node] = counter++;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    Tree t;
    vector<int> val(n);
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }
    t.adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.adj[u].push_back(v), t.adj[v].push_back(u);
    }
    t.pre_euler();
    vector<int> euler(2 * n);
    for (int i = 0; i < n; i++) {
        euler[t.first[i]] = val[i];
        euler[t.last[i]] = val[i];
    }
    vector<vector<pair<int,int>>> queries(2 * n + 1);
    for (int i = 0; i < n; i++) {
        queries[t.last[i]].push_back({t.first[i], i});
    }
    distinctValues(euler, queries, n);
}
