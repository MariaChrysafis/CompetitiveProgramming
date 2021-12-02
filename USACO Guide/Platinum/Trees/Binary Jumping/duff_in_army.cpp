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
#pragma GCC optimize("Ofast")

#define ll int
using namespace std;

vector<ll> remove (vector<ll> v) {
    int prev = -1;
    sort(v.begin(), v.end());
    vector<int> vec;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] != prev) {
            vec.push_back(v[i]);
            prev = v[i];
        }
    }
    return vec;
}
vector<ll> merge (vector<ll> v1, vector<ll> v2) {
    for (int i: v1) {
        v2.push_back(i);
    }
    v2 = remove(v2);
    vector<ll> ans;
    for (int i = 0; i < min((int)v2.size(), 10); i++) {
        ans.push_back(v2[i]);
    }
    return ans;
}

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
    vector<vector<ll>> adj; //first comes node, then comes edge weight
    vector<vector<vector<ll>>> dp;
    vector<vector<ll>> cities;
    vector<ll> parent;
    vector<ll> depth;
    tree t;
    void dfs (ll curNode, ll prevNode) {
        parent[curNode] = prevNode;
        if (curNode != 0) depth[curNode] = depth[prevNode] + 1;
        else depth[curNode] = 0;
        for (auto p: adj[curNode]) {
            if (p != prevNode) {
                dfs(p, curNode);
            }
        }
    }
    vector<ll> rec (ll curNode, ll up) {
        if (up == 0) return cities[curNode];
        ll lg2 = log2(up);
        return merge(dp[curNode][lg2], rec(t.nxt[curNode][lg2], up - (1 << lg2)));
    }
    vector<ll> qu (ll u, ll v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        return rec(u, depth[u] - depth[v]);
    }
    vector<ll> query (int u, int v) {
        return merge(qu(u, t.leastCommonAncestor(u, v)), qu(v, t.leastCommonAncestor(u, v)));
    }
    void read() {
        int n = adj.size();
        t.adj = adj, t.read();
        dp.resize(n), parent.resize(n), depth.resize(n);
        for (int i = 0; i < n; i++) {
            dp[i].resize(18);
        }
        dfs(0, -1);
        for (int i = 1; i < n; i++) {
            dp[i][0] = merge(cities[parent[i]], cities[i]);
        }
        for (int j = 1; j < dp[0].size(); j++) {
            for (int i = 0; i < n; i++) {
                dp[i][j] = merge(dp[i][j - 1], dp[t.nxt[i][j - 1]][j - 1]);
            }
        }
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, q;
    cin >> n >> m >> q;
    Tree t;
    t.adj.resize(n), t.cities.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.adj[u].push_back(v), t.adj[v].push_back(u);
    }
    for (int i = 0; i < m; i++) {
        int x; cin >> x; x--;
        if (t.cities[x].size() <= 10) t.cities[x].push_back(i);
    }
    t.read();
    while (q--) {
        ll u, v, a;
        cin >> u >> v >> a;
        u--, v--;
        vector<ll> ans = t.query(u, v);
        int sz = min((ll)ans.size(), a);
        cout << sz << ' ';
        for (int i = 0; i < sz; i++) {
            cout << ans[i] + 1 << ' ';
        }
        cout << '\n';
    }
}
