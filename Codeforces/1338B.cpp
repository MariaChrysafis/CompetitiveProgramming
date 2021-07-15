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
    vector<int> depth;
    void dfs(int u, int prev){
        if(prev != -1) depth[u] = depth[prev] + 1;
        else depth[u] = 0;
        for(int i: adj[u]){
            if(i == prev) continue;
            dfs(i, u);
        }
    }
    void read(){
        int n;
        cin >> n;
        adj.resize(n), depth.resize(n);
        for(int i = 0; i < n - 1; i++){
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        bool marked[n];
        for(int i = 0; i < n; i++){
            marked[i] = false;
        }
        int ans = n - 1;
        for(int i = 0; i < n; i++){
            if(marked[i]) continue;
            int cntr = 0;
            for(int j: adj[i]){
                if(!marked[j] && adj[j].size() == 1){
                    cntr++;
                }
            }
            if(cntr == 0) continue;
            ans -= cntr - 1;
        }
        int leaf = 0;
        for(int i = 0; i < n; i++){
            if(adj[i].size() == 1){
                leaf = i;
            }
        }
        dfs(leaf, -1);
        int cntr = 1;
        for(int i = 0; i < n; i++){
            if(adj[i].size() == 1 && depth[i] % 2 == 1){
                cntr = 3;
            }
        }
        cout << cntr << " " << ans << endl;
    }
};
int main(){
    tree t;
    t.read();
}
