#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <set>

#define ll long long
using namespace std;

const int MOD = 998244353;

void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}

ll mult(ll a, ll b){
    return (a * b) % MOD;
}

ll binpow(ll a, ll b){
    ll ans = 1;
    ll res = a;
    while(b > 0){
        if(b & 1){
            ans = mult(ans, res);
        }
        res = mult(res, res);
        b /= 2;
    }
    return ans;
}

struct tree{
    vector<vector<int>> adj;
    vector<int> parents;
    void dfs(int cur, int prev){
        parents[cur] = prev;
        for(int i: adj[cur]){
            if(i != prev){
                dfs(i, cur);
            }
        }
    }
    bool bfs(int k){
        vector<int> hasVisited(adj.size());
        vector<int> inDegree(adj.size());
        for(int i = 0; i < adj.size(); i++){
            hasVisited[i] = false;
            inDegree[i] = 0;
        }
        queue<int> q;
        for(int i = 0; i < adj.size(); i++){
            if(adj[i].size() == 1){
                q.push(i);
            }
        }
        while(!q.empty()){
            int x = q.front();
            q.pop();
            if(hasVisited[x]){
                continue;
            }
            hasVisited[x] = true;
            if(inDegree[x] % k == 0){
                if(x == 0) {
                    return true;
                }
                inDegree[parents[x]]++;
            }else if(inDegree[x] % k == k - 1){
                if(x == 0) {
                    return false;
                }
                inDegree[x]++;
                q.push(parents[x]);
            }else{
                return false;
            }
        }
        for(int i = 0; i < inDegree.size(); i++){
            if(inDegree[i] % k != 0){
                return false;
            }
        }
        return true;
    }
};

void solve(){
    tree t;
    int n;
    cin >> n;
    t.adj.resize(n), t.parents.resize(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.adj[u].push_back(v), t.adj[v].push_back(u);
    }
    t.dfs(0, -1);
    vector<int> ans(2);
    ans[1] = 1;
    for(int k = 1; k <= n - 1; k++){
        ans[1] = 2 * ans[1];
        ans[1] %= MOD;
    }
    for(int i = 2; i <= n; i++){
        if((n - 1) % i != 0){
            ans.push_back(0);
        }
        ans.push_back(t.bfs(i));
    }
    //print(ans);
    for (int i = n; i >= 1; i--) {
        for (int j = i + i; j <= n; j += i) {
            ans[i] = (ans[i] - ans[j] + MOD) % MOD;
        }
    }
    for(int i = 1; i < ans.size() - 1; i++){
        cout << ans[i] << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
