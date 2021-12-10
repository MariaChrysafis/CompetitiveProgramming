#include <iostream>
#include <map>
#include <vector>
#define maxN 200001
#define pb push_back
using namespace std;
map<int,vector<int>> adj;
int depth[maxN];
 
int DFS(int curNode, int prevNode){
    int cntr = 1;
    for(int i: adj[curNode]){
        if(i == prevNode) continue;
        cntr += DFS(i,curNode);
    }
    depth[curNode] = cntr;
    return cntr;
}
int main(){
    int n;
    cin >> n;
    for(int i = 2; i <= n; i++){
        int a;
        cin >> a;
        adj[i].pb(a);
        adj[a].pb(i);
    }
    DFS(1,0);
    for(int i = 1; i <= n; i++){
        cout << depth[i] - 1 << " ";
    }
    
}
