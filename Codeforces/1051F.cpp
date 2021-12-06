#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>

#define ll long long
using namespace std;
struct Graph {
    const ll INF = 1e12;
    vector<vector<pair<ll, ll>>> adj;  //{-weight, node}
    vector<ll> dijk(ll src) {
        vector<ll> dist;
        vector<bool> mark;
        dist.resize(adj.size()), mark.resize(adj.size());
        for (ll i = 0; i < adj.size(); i++) {
            dist[i] = INF;
            mark[i] = false;
        }
        dist[src] = 0;
        priority_queue<pair<ll, ll>> pq;
        pq.push({0, src});
        while (!pq.empty()) {
            ll u = pq.top().second;  // node
            pq.pop();
            if (mark[u]) {
                continue;
            }
            mark[u] = true;
            for (auto p : adj[u]) {
                ll v = p.second;
                ll w = p.first;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({-dist[v], v});
                }
            }
        }
        return dist;
    }
};
struct dsu{
    vector<ll> parent;
    vector<ll> compSize;
    ll n;
    void fill(){
        parent.resize(n), compSize.resize(n);
        for(ll i = 0; i < n; i++){
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
    vector<vector<ll>> dp;
    vector<ll> enter;
    vector<ll> exit;
    ll cntr = 1;
    ll lg2;
    void dfs(ll u, ll prev){
        cntr++;
        enter[u] = cntr;
        dp[u][0] = prev;
        for(ll i = 1; i <= lg2; i++){
            dp[u][i] = dp[dp[u][i - 1]][i - 1];
        }
        for(ll v: adj[u]){
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
            if(!isAncestor(dp[u][i], v)){
                u = dp[u][i];
            }
        }
        return dp[u][0];
    }
    void read(){
        ll n = adj.size();
        lg2 = ceil(log2(n)) + 1;
        enter.resize(n);
        exit.resize(n);
        adj.resize(n);
        dp.resize(n);
        for(ll i = 0; i < n; i++){
            dp[i].resize(lg2 + 1);
            enter[i] = exit[i] = -1;
        }
        dfs(0, 0);
    }
};
struct Tree {
    vector<vector<pair<ll,ll>>> adj; //[node, weight]
    map<pair<ll,ll>,ll> myMap;
    tree t;
    vector<ll> depth, parent;
    void dfs (ll curNode, ll prevNode) {
        parent[curNode] = prevNode;
        for (ll i: t.adj[curNode]) {
            if (i != prevNode) {
                dfs(i, curNode);
            }
        }
    }
    ll memoize (ll curNode) {
        if (curNode == 0) return 0;
        if (depth[curNode] != 0) return depth[curNode];
        return (depth[curNode] = memoize(parent[curNode]) + myMap[{curNode, parent[curNode]}]);
    }
    ll query (ll u, ll v) {
        return depth[u] + depth[v] - 2 * depth[t.leastCommonAncestor(u, v)];
    }
    void read() {
        depth.assign(adj.size(), 0);
        parent.assign(adj.size(), 0);
        t.adj.resize(adj.size());
        for (ll i = 0; i < adj.size(); i++) {
            for (pair<ll,ll> p: adj[i]) {
                t.adj[i].push_back(p.first);
                myMap[{i, p.first}] = myMap[{p.first, i}] = p.second;
            }
        }
        t.read();
        dfs(0, -1);
        for (int i = 0; i < adj.size(); i++) {
            depth[i] = memoize(i);
        }
    }

};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, m;
    cin >> n >> m;
    Graph g;
    g.adj.resize(n);
    vector<pair<ll, pair<ll, ll>>> edges, not_edges;
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g.adj[u].push_back({w, v});
        g.adj[v].push_back({w, u});
        edges.push_back({w, {u, v}});
    }
    dsu d;
    d.n = n;
    d.fill();
    Tree t; t.adj.resize(n);
    sort(edges.begin(), edges.end());
    for (auto& p: edges) {
        if (!d.comp(p.second.first, p.second.second)) {
            d.join(p.second.first, p.second.second);
            t.adj[p.second.first].push_back({p.second.second, p.first});
            t.adj[p.second.second].push_back({p.second.first, p.first});
            //cout << p.second.second << " " << p.second.first << " " << p.first << endl;
        } else {
            not_edges.push_back(p);
        }
    }
    vector<vector<ll>> distances(n);
    for (auto& p: not_edges) {
        distances[p.second.first] = g.dijk(p.second.first);
        distances[p.second.second] = g.dijk(p.second.second);
    }
    t.read();
    ll q;
    cin >> q;
    while (q--) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        ll ans = t.query(u, v);
        for (auto& p: not_edges) {
            ans = min(ans, distances[p.second.second][u] + distances[p.second.first][v] + p.first);
            ans = min(ans, distances[p.second.first][u] + distances[p.second.second][v] + p.first);
            if (p.second.second == u) {
                ans = min(ans, distances[p.second.second][v]);
            }
            if (p.second.first == v) {
                ans = min(ans, distances[p.second.first][u]);
            }
        }
        cout << ans << '\n';
    }

}
