#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bit>
#include <bitset>
#include <map>
#include <algorithm>
#define ll long long
using namespace std;
struct dsu {
    vector<ll> parent;
    vector<ll> compSize;
    ll n;
    void fill(){
        parent.resize(n), compSize.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i, compSize[i] = 1;
        }
    }
    ll find_head(ll x){
        if(x == parent[x]){
            return x;
        }
        return find_head(parent[x]);
    }
    void join(ll x, ll y){
        x = find_head(x);
        y = find_head(y);
        if(x == y){
            return;
        }
        if(compSize[x] > compSize[y]){
            swap(x,y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
    }
    bool comp(ll x, ll y){
        return (find_head(x) == find_head(y));
    }
};
struct tree{
    vector<vector<ll>> adj;
    vector<vector<ll>> nxt;
    vector<ll> enter;
    vector<ll> exit;
    ll cntr = 1;
    ll lg2;
    void dfs(ll u, ll prev){
        cntr++;
        enter[u] = cntr;
        nxt[u][0] = prev;
        for(int i = 1; i <= lg2; i++){
            nxt[u][i] = nxt[nxt[u][i - 1]][i - 1];
        }
        for(int v: adj[u]){
            if(v != prev){
                dfs(v, u);
            }
        }
        cntr++;
        exit[u] = cntr;
    }
    bool isAncestor(ll u, ll v){
        //is u an ancestor of v
        return (enter[u] <= enter[v] && exit[u] >= exit[v]);
    }
    ll leastCommonAncestor(ll u, ll v){
        if(isAncestor(u, v)){
            return u;
        }
        if(isAncestor(v, u)){
            return v;
        }
        for(ll i = lg2; i >= 0; i--){
            if(!isAncestor(nxt[u][i], v)){
                u = nxt[u][i];
            }
        }
        return nxt[u][0];
    }
    void read(){
        ll n = adj.size();
        lg2 = 20;
        enter.resize(n);
        exit.resize(n);
        adj.resize(n);
        nxt.resize(n);
        for(ll i = 0; i < n; i++){
            nxt[i].resize(lg2 + 1);
            enter[i] = exit[i] = -1;
        }
        dfs(0, 0);
    }
};
struct Tree {
    vector<vector<pair<ll,ll>>> adj; //first comes node, then comes edge weight
    vector<vector<ll>> dp;
    vector<ll> parent;
    vector<ll> depth;
    tree t;
    void dfs (ll curNode, ll prevNode) {
        parent[curNode] = prevNode;
        if (curNode != 0) depth[curNode] = depth[prevNode] + 1;
        else depth[curNode] = 0;
        for (auto p: adj[curNode]) {
            if (p.first != prevNode) {
                dfs(p.first, curNode);
            }
        }
    }
    ll rec (ll curNode, ll up) {
        //we go up curNode times from up
        if (up == 0) return 0;
        ll lg2 = log2(up);
        ll pos1 = dp[curNode][lg2];
        ll pos2 = rec(t.nxt[curNode][lg2], up - (1 << lg2));
        return max(pos1, pos2);
    }
    ll qu (ll u, ll v) {
        //u is in v's subtree
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        return rec(u, depth[u] - depth[v]);
    }
    ll query (int u, int v) {
        return max(qu(u, t.leastCommonAncestor(u, v)), qu(v, t.leastCommonAncestor(u, v)));
    }
    void read() {
        ll n = adj.size();
        t.adj.resize(n);
        depth.resize(n);
        for (int i = 0; i < n; i++) for (auto& p: adj[i]) t.adj[i].push_back(p.first);
        t.read();
        dp.resize(n), parent.resize(n);
        for (int i = 0; i < n; i++) {
            dp[i].resize(18);
            for (int j = 0; j < dp[i].size(); j++) {
                dp[i][j] = 0;
            }
        }
        dfs(0, -1);
        for (ll i = 0; i < n; i++) {
            for (auto p: adj[i]) {
                ll x = p.first; ll y = i;
                if (parent[x] == y) swap(x, y); //y is the child of x OR x is the parent of y
                dp[y][0] = p.second;
            }
        }
        for (ll j = 1; j < 18; j++) {
            for (ll i = 0; i < n; i++) {
                dp[i][j] = max(dp[i][j - 1], dp[t.nxt[i][j - 1]][j - 1]);
            }
        }
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, m;
    cin >> n >> m;
    vector<pair<ll,pair<ll,ll>>> edges, inp;
    while (m--) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        edges.push_back({w, {u, v}});
    }
    inp = edges;
    dsu d; d.n = n; d.fill();
    sort(edges.begin(), edges.end());
    vector<pair<ll,pair<ll,ll>>> new_edges;
    for (auto& p: edges) {
        if (d.comp(p.second.first, p.second.second)) continue;
        d.join(p.second.first, p.second.second);
        new_edges.push_back(p);
    }
    edges = new_edges;
    Tree t;
    t.adj.resize(n);
    ll ans = 0;
    for (auto &p: edges) {
        t.adj[p.second.first].push_back({p.second.second, p.first});
        t.adj[p.second.second].push_back({p.second.first, p.first});
        ans += p.first;
    }
    t.read();
    for (auto& p: inp) {
        cout << ans + p.first - t.query(p.second.first, p.second.second) << '\n';
    }
}
