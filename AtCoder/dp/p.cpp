#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <queue>
#include <map>
#define ll signed long long
using namespace std;
const int MOD = 1e9 + 7;
vector<vector<ll>> adj;
vector<ll> color[2];
ll dfs1 (int curNode, int prevNode, int col) {
    if (color[col][curNode] != -1) {
        return color[col][curNode];
    }
    //col = 0 -> white
    //col = 1 -> black
    ll ans = 1;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            ll c1 = dfs1(i, curNode, 0);
            ll c2 = dfs1(i, curNode, 1);
            if (col == 0) {
                //white
                ans *= (c1 + c2);
                ans %= MOD;
            }
            if (col == 1) {
                //black
                ans *= c1;
                ans %= MOD;
            }
        }
    }
    color[col][curNode] = ans;
    return ans;
}
int main() {
    int n;
    cin >> n;
    adj.resize(n);
    color[0].resize(n);
    color[1].resize(n);
    for (int i = 0; i < n; i++) {
        color[0][i] = color[1][i] = -1;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        dfs1(i, -1, 0);
        dfs1(i, -1, 1);
    }
    cout << (color[0][0] + color[1][0]) % MOD;
}
