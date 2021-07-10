#include <iostream>
#include <vector>
using namespace std;
struct Graph{
    vector<vector<int>> adj;
    vector<vector<int>> adj_rev;
    vector<int> color;
    vector<bool> head;
    vector<bool> isInf;
    vector<bool> hasVisited;
    vector<bool> mult;
    void dfs1(int cur){
        isInf[cur] = true;
        for(int u: adj[cur]){
            if(!isInf[u]){
                dfs1(u);
            }
        }
    }
    void dfs(int cur){
        color[cur] = 1;
        for(int u: adj[cur]){
            if(color[u] == 0){
                dfs(u);
            }else if(color[u] == 1){
                head[u] = true;
            }
        }
        color[cur] = 2;
    }
    void dfs2(int cur){
        if(isInf[cur]){
            return;
        }
        hasVisited[cur] = true;
        for(int u: adj[cur]){
            if(!hasVisited[u]){
                mult[u] = mult[cur];
                dfs2(u);
            }else{
                mult[u] = true;
            }
        }
    }
    void dfs3(int cur){
        if(isInf[cur]){
            return;
        }
        mult[cur] = true;
        for(int i: adj[cur]){
            if(!mult[i]) {
                mult[i] = true;
                dfs3(i);
            }
        }
    }
    void read(){
        int n, m;
        cin >> n >> m;
        color.resize(n);
        adj.resize(n);
        adj_rev.resize(n);
        head.resize(n);
        isInf.resize(n);
        hasVisited.resize(n);
        mult.resize(n);
        for(int i = 0; i < n; i++){
            color[i] = 0;
            head[i] = isInf[i] = false;
        }
        for(int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj_rev[v].push_back(u);
        }
        dfs(0);
        for(int i = 0; i < n; i++){
            if(head[i]){
                dfs1(i);
            }
        }
        dfs2(0);
        for(int i = 0; i < n; i++){
            if(mult[i]){
                dfs3(i);
            }
        }
        int ans[n];
        for(int i = 0; i < n; i++){
            if(color[i] == 0){
                ans[i] = 0;
            }else if(isInf[i]){
                ans[i] = -1;
            }else if(mult[i]){
                ans[i] = 2;
            }else{
                ans[i] = 1;
            }
        }
        for(int i: ans){
            cout << i << " ";
        }
        cout << endl;
        //cout << endl;
    }
};
int main(){
    int t;
    cin >> t;
    while(t--){
        Graph g;
        g.read();
    }
}
