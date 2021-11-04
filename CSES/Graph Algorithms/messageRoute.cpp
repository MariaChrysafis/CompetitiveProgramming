#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>
#define maxN 200000
#define pb push_back
using namespace std;
map<int,vector<int>> adj;
int n,m;
bool hasVisited[maxN];
bool flag = true;
int parent[maxN];
void BFS(int src){
    priority_queue<pair<int,int>> pq;
    pq.push(make_pair(0,0));
    while(!pq.empty()){
        int curNode = pq.top().second;
        int curDist = pq.top().first;
        pq.pop();
        for(int i: adj[curNode]){
            if(hasVisited[i]) continue;
            parent[i] = curNode;
            hasVisited[i] = true;
            pq.push(make_pair(curDist - 1,i));
        }
    }
    if(!hasVisited[n - 1]){cout << "IMPOSSIBLE" << endl; return;}
    int a = n - 1;
    vector<int> v;
    v.pb(a);
    while(a != 0){
        a = parent[a];
        v.pb(a);
    }
    cout << v.size() << endl;
    for(int i = v.size() - 1; i >= 0; i--) cout << v[i] + 1 << " ";
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u,v;
        cin >> u >> v;
        adj[u - 1].pb(v - 1);
        adj[v - 1].pb(u - 1);
    }
    BFS(0);
 
 
}
