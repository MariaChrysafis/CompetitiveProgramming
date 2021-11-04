#include <iostream>
#include <vector>
#include <map>
#define pb push_back
using namespace std;
int n,m;
map<int,vector<int>> adj;
map<int,vector<int>> myMap;
int cntr = 0;
bool hasVisited[200000];
void DFS(int x){
    hasVisited[x] = true;
    myMap[cntr].pb(x);
    for(int i: adj[x]){
        if(hasVisited[i]) continue;
        DFS(i);
    }
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u,v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for(int i = 1; i <= n; i++){
        if(hasVisited[i]) continue;
        DFS(i);
        cntr++;
    }
    cout << cntr - 1 << endl;
    for(int i = 0; i < cntr - 1; i++){
        cout << myMap[i][0] << " " << myMap[i + 1][0] << endl;
    }
}
