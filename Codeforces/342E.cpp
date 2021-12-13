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
    vector<int> enter;
    vector<int> exit;
    vector<int> depth, parent;
    int cntr = 1;
    int lg2;
    int memoize (int u) {
        if (depth[u] != -1) return depth[u];
        if (u == 0) return 0;
        return (depth[u] = memoize(parent[u]) + 1);
    }
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
    int dist (int u, int v) {
        return (memoize(u) + memoize(v) - 2 * memoize(leastCommonAncestor(u, v)));
    }
    void read (){
        int n = adj.size();
        lg2 = ceil(log2(n)) + 1;
        enter.resize(n);
        exit.resize(n);
        adj.resize(n);
        dp.resize(n);
        parent.resize(n);
        depth.assign(n, -1);
        for(int i = 0; i < n; i++){
            dp[i].resize(lg2 + 1);
            enter[i] = exit[i] = -1;
        }
        dfs(0, 0);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int N, Q;
    cin >> N >> Q;
    tree t;
    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    t.adj = adj;
    t.read();
    vector<int> dist;
    dist.assign(N, 1e9);
    vector<pair<int,int>> queries = {{1, 0}};
    for (int i = 0; i < Q; i++) {
        int t, v;
        cin >> t >> v;
        v--;
        queries.emplace_back(t, v);
    }
    vector<int> q;
    for (auto& p: queries) {
        if (p.first == 2) {
            int ans = dist[p.second];
            for (int i: q) {
                ans = min(ans, t.dist(i, p.second));
            }
            cout << ans << '\n';
        } else {
            dist[p.second] = 0;
            q.push_back(p.second);
            if (q.size() >= sqrt(N)) {
                while (!q.empty()) {
                    int curNode = q.back();
                    q.pop_back();
                    for (int i: adj[curNode]) {
                        if (dist[i] > dist[curNode] + 1) {
                            dist[i] = dist[curNode] + 1;
                            q.push_back(i);
                        }
                    }
                }
            }
        }
    }


}
