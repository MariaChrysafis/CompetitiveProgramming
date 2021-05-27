#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
const int MOD = 1e9 + 7;
struct tree{
    vector<vector<int>> adj;
    vector<int> parent;
    void dfs(int cur, int prev){
        if(prev != -1){
            parent[cur] = prev;
        }
        for(int i: adj[cur]){
            if(i != prev){
                dfs(i, cur);
            }
        }
    }
    vector<int> find_parent(){
        parent.resize(adj.size());
        dfs(0, -1);
        parent[0] = -1;
        return parent;
    }
};
vector<int> p;
tree t;
vector<long long> dp[2];
long long memoize(int curNode, bool color){
    //color = 1 -> black
    //color = 0 -> white
    if(dp[color][curNode] != -1){
        return dp[color][curNode];
    }
    if(!color) {
        long long ans = 1;
        for (int i: t.adj[curNode]) {
            if (i == p[curNode]) continue;
            ans *= (memoize(i, 0) + memoize(i, 1));
            if(ans > MOD) ans %= MOD;
        }
        dp[color][curNode] = ans;
        return ans;
    }else{
        long long ans = 1;
        for (int i: t.adj[curNode]) {
            if (i == p[curNode]) continue;
            ans *= (memoize(i, 0));
            if(ans > MOD) ans %= MOD;
        }
        dp[color][curNode] = ans;
        return ans;
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    t.adj.resize(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        t.adj[u - 1].push_back(v - 1);
        t.adj[v - 1].push_back(u - 1);
    }
    p = t.find_parent();
    for(int i = 0; i < 2; i++){
        dp[i].resize(n);
        for(int j = 0; j < dp[i].size(); j++){
            dp[i][j] = -1;
        }
    }
    cout << (memoize(0, 0) + memoize(0, 1)) % MOD;
}
