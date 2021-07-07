#include <vector>
#include <iostream>
#include <cmath>
using namespace std;
const int MOD = 1e9 + 7;
const int N = 200;
long long binpow(long long a, long long b){
    a %= MOD;
    long long res = 1;
    while(b > 0){
        if(b & 1){
            res *= a;
            res %= MOD;
        }
        a *= a;
        a %= MOD;
        b >>= 1;
    }
    return res;
}
long long inv(long long x){
    return binpow(x, MOD - 2);
}
long long mult(long long a, long long b){
    return (a * b) % MOD;
}
long long add(long long a, long long b){
    return (a + b) % MOD;
}
vector<vector<int>> adj;
int n;
long long f[2 * N][2 * N];
struct tree{
    vector<vector<int>> dp;
    vector<int> enter;
    vector<int> exit;
    vector<int> depth;
    int cntr = 1;
    int lg2;
    void dfs(int u, int prev, int dep){
        depth[u] = dep;
        cntr++;
        enter[u] = cntr;
        dp[u][0] = prev;
        for(int i = 1; i <= lg2; i++){
            dp[u][i] = dp[dp[u][i - 1]][i - 1];
        }
        for(int v: adj[u]){
            if(v != prev){
                dfs(v, u, dep + 1);
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
    long long read(int root){
        depth.resize(n);
        lg2 = ceil(log2(n)) + 1;
        enter.resize(n);
        exit.resize(n);
        adj.resize(n);
        dp.resize(n);
        for(int i = 0; i < n; i++){
            dp[i].resize(lg2 + 1);
            enter[i] = exit[i] = -1;
            depth[i] = 0;
        }
        dfs(root, root, 0);
        long long ans = 0;
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                int d = depth[leastCommonAncestor(i, j)];
                ans = add(f[depth[i]-d][depth[j]-d], ans);
            }
        }
        return ans;
    }
};
int main(){
    cin >> n;
    adj.resize(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    tree myTree;
    for(int i = 0; i < 2 * n; i++){
        for(int j = 0; j < 2 * n; j++){
            if(i == 0 || j == 0){
                if(i == 0) f[i][j] = 0;
                else f[i][j] = 1;
                continue;
            }
            f[i][j] = mult(add(f[i - 1][j],f[i][j - 1]), inv(2));
        }
    }
    long long ans = 0;
    for(int i = 0; i < n; i++){
        long long x = myTree.read(i);
        //cout << x << endl;
        ans = add(x, ans);
    }
    //cout << ans << endl;
    cout << mult(ans, inv(n)) << endl;
 
}
