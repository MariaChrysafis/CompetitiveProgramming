#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <set>
#include <chrono>

#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>

#pragma GCC optimize("O3")

#define ll long long
using namespace std;
struct Tree {
    vector<vector<ll>> adj;
    vector<ll> val;
    vector<ll> sub;
    vector<vector<ll>> dp;
    vector<ll> enter;
    vector<ll> exit;
    vector<ll> depth;
    ll cntr = 1;
    ll lg2;
    ll n, k;
    void dfs(int u, int prev){
        cntr++;
        enter[u] = cntr;
        dp[u][0] = prev;
        for(int i = 1; i <= lg2; i++){
            dp[u][i] = dp[dp[u][i - 1]][i - 1];
        }
        for(int v: adj[u]){
            if(v != prev){
                dfs(v, u);
            }
        }
        cntr++;
        exit[u] = cntr;
    }
    bool isAncestor(int u, int v){
        return (enter[u] <= enter[v] && exit[u] >= exit[v]);
    }
    int leastCommonAncestor(int u, int v){
        if(isAncestor(u, v)){
            return u;
        }
        if(isAncestor(v, u)){
            return v;
        }
        for(int i = lg2; i >= 0; i--){
            if(!isAncestor(dp[u][i], v)){
                u = dp[u][i];
            }
        }
        return dp[u][0];
    }
    ll dfs3(ll curNode, ll prevNode) {
        sub[curNode] = val[curNode];
        for (ll i: adj[curNode]) {
            if (i != prevNode) {
                sub[curNode] ^= dfs3(i, curNode);
            }
        }
        return sub[curNode];
    }
    bool read() {
        cin >> n >> k;
        val.resize(n);
        adj.resize(n);
        sub.resize(n);
        lg2 = ceil(log2(n)) + 1;
        enter.resize(n);
        exit.resize(n);
        adj.resize(n);
        dp.resize(n);
        depth.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> val[i];
            enter[i] = exit[i] = -1;
            dp[i].resize(lg2 + 1);
        }
        for (int i = 0; i < n - 1; i++) {
            ll u, v;
            cin >> u >> v;
            adj[u - 1].push_back(v - 1);
            adj[v - 1].push_back(u - 1);
        }
        dfs(0, 0);
        dfs3(0, -1);
        if(sub[0] == 0) {
            return true;
        }
        if (k == 2) {
            return false;
        }
        vector<int> v1;
        for (int i = 1; i < n; i++) {
            if(sub[i] == sub[0]) {
                v1.push_back(i);
            }
        }
        vector<int> v2;
        for(int i = 1; i < n; i++) {
            if(sub[i] == 0) {
                v2.push_back(i);
            }
        }
        for (int i: v1) {
            for(int j: v2) {
                if(isAncestor(j, i)) {
                    return true;
                }
            }
        }
        for (int i: v1) {
            for (int j: v1) {
                if (!isAncestor(i, j) && !isAncestor(j, i)) {
                    return true;
                }
            }
        }
        return false;
    }
};
bool solve () {
    Tree t;
    return t.read();
}

int main() {
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        bool b = solve();
        if(b) cout << "YES\n";
        else cout << "NO\n";
    }
}
