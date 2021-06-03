#include <bitset>
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <map>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;
struct tree{
    int n;
    vector<vector<int>> adj;
    vector<vector<long long>> cost;
    vector<int> parents;
    vector<vector<long long>> dp;
    void dfs(int cur, int prev) {
        parents[cur] = prev;
        for(int x: adj[cur]){
            if(x != prev){
                dfs(x, cur);
            }
        }
    }
    void fill_parents(){
        parents.resize(n);
        dfs(0, -1); //root the tree at 0
    }
    void fill_dp(){
        dp.resize(n);
        for(int i = 0; i < n; i++) dp[i].resize(2);
        for(int i = 0; i < n; i++){
            dp[i][0] = dp[i][1] = -1;
        }
    }
    void fill(){
        cin >> n;
        adj.resize(n);
        for(int i = 0; i < n; i++){
            int l, w;
            cin >> l >> w;
            cost.push_back({l, w});
        }
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    long long memoize(int cur_node, int b){
        /*
         * b = 0 -> color it with our left
         * b = 1 - > color it with our right
         */
        if(dp[cur_node][b] != -1){
            return dp[cur_node][b];
        }
        long long ans = 0;
        for(long long x: adj[cur_node]){
            if(x == parents[cur_node]) continue;
            long long right = abs(cost[x][1] - cost[cur_node][b]) + memoize(x, 1);
            long long left = abs(cost[x][0] - cost[cur_node][b]) + memoize(x, 0);
            ans += max(left, right);
        }
        dp[cur_node][b] = ans;
        return dp[cur_node][b];
    }
};
void solve(){
    tree t;
    t.fill();
    t.fill_parents();
    t.fill_dp();
    long long ans = max(t.memoize(0, 0), t.memoize(0, 1));
    cout << ans << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
