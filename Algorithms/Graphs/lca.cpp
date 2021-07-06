#include <vector>
#include <iostream>
#include <cmath>
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
struct tree{
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    vector<int> enter;
    vector<int> exit;
    int cntr = 1;
    int lg2;
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
    void read(){
        int n;
        cin >> n;
        lg2 = ceil(log2(n)) + 1;
        enter.resize(n);
        exit.resize(n);
        adj.resize(n);
        dp.resize(n);
        for(int i = 0; i < n; i++){
            dp[i].resize(lg2 + 1);
            enter[i] = exit[i] = -1;
            int x;
            cin >> x;
            while(x--){
                int u;
                cin >> u;
                u--;
                adj[u].push_back(i);
                adj[i].push_back(u);
            }
        }
        dfs(0, 0);
        int q;
        cin >> q;
        while(q--){
            int u, v;
            cin >> u >> v;
            u--, v--;
            cout << leastCommonAncestor(u, v) + 1 << '\n';
        }
    }
};
int main(){
    int t;
    cin >> t;
    for(int i = 1; i <= t; i++){
        cout << "Case " << i << ":" << endl;
        tree myTree;
        myTree.read();
    }
}
