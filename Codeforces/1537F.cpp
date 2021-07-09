#include <iostream>
#include <vector>
using namespace std;
struct graph{
    vector<vector<int>> adj;
    vector<int> delta;
    vector<int> color;
    int n, m;
    void dfs(int u, int cntr){
        color[u] = cntr;
        for(int v: adj[u]){
            if(color[v] == -1){
                dfs(v, 1 - cntr);
            }
        }
    }
    void read(){
        cin >> n >> m;
        vector<int> v1, v2;
        v1.resize(n), v2.resize(n), delta.resize(n), color.resize(n), adj.resize(n);
        int c1 = 0;
        int c2 = 0;
        for(int i = 0; i < n; i++){
            cin >> v1[i];
            c1 += abs(v1[i]);
            c1 %= 2;
        }
        for(int i = 0; i < n; i++){
            cin >> v2[i];
            delta[i] = v2[i] - v1[i], color[i] = -1;
            c2 += abs(v2[i]);
            c2 %= 2;
        }
        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v), adj[v].push_back(u);
        }
        if(c1 != c2){
            cout << "NO\n";
            return;
        }
        dfs(0, 0);
        bool bip = true; //bip -> bachelor in paradise, not bipartite
        long long cntr[2];
        cntr[0] = cntr[1] = 0;
        for(int i = 0; i < n; i++){
            cntr[color[i]] += delta[i];
            for(int j: adj[i]){
                if(color[i] == color[j]){
                    bip = false;
                }
            }
        }
        if(!bip || cntr[0] == cntr[1]){
            cout << "YES\n";
            return;
        }else{
            cout << "NO\n";
        }
    }
};
int main(){
    int t;
    cin >> t;
    while(t--){
        graph g;
        g.read();
    }
}
