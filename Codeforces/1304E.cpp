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
struct tree{
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    vector<int> depth, parent;
    vector<int> enter;
    vector<int> exit;
    int cntr = 1;
    int lg2;
    void dfs(int u, int prev){
        parent[u] = prev;
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
        //is u an ancestor of v
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
    int memoize (int curNode) {
        if (depth[curNode] != 0) return depth[curNode];
        if (curNode == 0) return (depth[curNode] = 0);
        else return depth[curNode] = memoize(parent[curNode]) + 1;
    }
    int dist (int u, int v) {
        return depth[u] + depth[v] - 2 * depth[leastCommonAncestor(u, v)];
    }
    void read (int n){
        lg2 = ceil(log2(n)) + 1;
        enter.resize(n);
        exit.resize(n);
        adj.resize(n);
        dp.resize(n), parent.resize(n);
        depth.assign(n, 0);
        for(int i = 0; i < n; i++){
            dp[i].resize(lg2 + 1);
            enter[i] = exit[i] = -1;
        }
        dfs(0, 0);
        for (int i = 0; i < n; i++) {
            depth[i] = memoize(i);
        }
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    tree t;
    t.adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.adj[u].push_back(v), t.adj[v].push_back(u);
    }
    t.read(n);
    int q;
    cin >> q;
    while (q--) {
        int x, y, a, b, k;
        cin >> x >> y >> a >> b >> k;
        x--, y--, a--, b--;
        if (t.dist(a, b) % 2 == k % 2 && t.dist(a, b) <= k) {
            cout << "YES\n";
            continue;
        }
        int new_dist = t.dist(a, x) + 1 + t.dist(y, b);
        if (new_dist % 2 == k % 2 && new_dist <= k) {
            cout << "YES\n";
            continue;
        }
        new_dist = t.dist(a, y) + 1 + t.dist(x, b);
        if (new_dist % 2 == k % 2 && new_dist <= k) {
            cout << "YES\n";
            continue;
        }
        cout << "NO\n";
    }
}
