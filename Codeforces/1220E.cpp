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
struct TECC { // 0 indexed
    ll n, k;
    vector<vector<ll>> g, t;
    vector<bool> used;
    vector<ll> comp, ord, low;
    set<pair<ll, ll>> br;

    void dfs(ll x, ll prv, ll &c) {
        used[x] = 1;
        ord[x] = c++;
        low[x] = n;
        bool mul = 0;
        for (auto y:g[x]) {
            if (used[y]) {
                if (y != prv || mul) low[x] = min(low[x], ord[y]);
                else mul = 1;
                continue;
            }
            dfs(y, x, c);
            low[x] = min(low[x], low[y]);
        }
    }

    void dfs2(ll x, ll num) {
        comp[x] = num;
        for (auto y: g[x]) {
            if (comp[y] != -1) continue;
            if (ord[x] < low[y]) {
                br.insert({x, y});
                k++;
                dfs2(y, k);
            } else dfs2(y, num);
        }
    }

    TECC(const vector<vector<ll>> &g) : g(g), n(g.size()), used(n), comp(n, -1), ord(n), low(n), k(0) {
        ll c = 0;
        for (ll i = 0; i < n; i++) {
            if (used[i]) continue;
            dfs(i, -1, c);
            dfs2(i, k);
            k++;
        }
    }

    void build_tree() {
        t.resize(k);
        for (auto e: br) {
            ll x = comp[e.first], y = comp[e.second];
            t[x].push_back(y);
            t[y].push_back(x);
        }
    }
};
struct dsu{
    vector<int> parent;
    vector<int> compSize;
    int n;
    void fill(){
        parent.resize(n), compSize.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i, compSize[i] = 1;
        }
    }
    int find_head(int x){
        if(x == parent[x]){
            return x;
        }
        return find_head(parent[x]);
    }
    void join(int x, int y){
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
    bool comp(int x, int y){
        return (find_head(x) == find_head(y));
    }
};
vector<vector<ll>> adj;
vector<ll> val;
int src;
set<ll> bounces;
void compress () {
    TECC t(adj);
    int n = adj.size();
    vector<ll> deg(n);
    for (ll i = 0; i < n; i++) {
        deg[i] = adj[i].size();
    }
    for (auto& p: t.br) {
        deg[p.first]--, deg[p.second]--;
    }
    dsu d; d.n = n; d.fill();
    for (int i = 0; i < n; i++) {
        if (!deg[i]) continue;
        for (int j: adj[i]) {
            if (!t.br.count({i, j}) && !t.br.count({j, i})) {
                d.join(i, j);
            }
        }
    }
    vector<vector<ll>> new_adj(n);
    for (int i = 0; i < n; i++) {
        for (int j: adj[i]) {
            if (d.find_head(i) == d.find_head(j)) continue;
            new_adj[d.find_head(i)].push_back(d.find_head(j));
        }
        if (i != d.find_head(i)) {
            val[d.find_head(i)] += val[i];
            val[i] = 0;
        }
        if (d.compSize[d.find_head(i)] >= 2) {
            bounces.insert(d.find_head(i));
        }
    }
    adj = new_adj;
    src = d.find_head(src);
}
vector<ll> sub;
vector<ll> parent;
ll dfs (ll curNode, ll prevNode) {
    parent[curNode] = prevNode;
    sub[curNode] = bounces.count(curNode);
    for (ll i: adj[curNode]) {
        if (i == prevNode) continue;
        sub[curNode] += dfs(i, curNode);
    }
    return sub[curNode];
}
vector<ll> sum;
ll memoize (ll curNode) {
    //cout << curNode << '\n';
    if (sum[curNode] != -1) return sum[curNode];
    if (sub[curNode]) return (sum[curNode] = 0);
    if (parent[curNode] == -1) return (sum[curNode] = val[curNode]);
    return (sum[curNode] = memoize(parent[curNode]) + val[curNode]);
}
int main() {
    ll n, m;
    cin >> n >> m;
    val.resize(n);
    parent.assign(n, -1);
    sum.assign(n, -1);
    sub.assign(n, -1);
    for (ll i = 0; i < n; i++) {
        cin >> val[i];
    }
    adj.resize(n);
    for (ll i = 0; i < m; i++) {
        ll u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    cin >> src;
    src--;
    compress();
    dfs(src, -1);
    ll VAL = 0;
    for (ll i = 0; i < n; i++) {
        if (sub[i]) {
            VAL += val[i];
        }
    }
    ll myMax = 0;
    for (ll i = 0; i < n; i++) {
        myMax = max(myMax, memoize(i));
    }
    cout << VAL + myMax;
}
