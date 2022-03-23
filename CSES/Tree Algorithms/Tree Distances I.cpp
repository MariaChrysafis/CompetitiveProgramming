#include <iostream>
#include <map>
#include <vector>
#include <queue>
#define maxN 200000
using namespace std;
map<int,vector<int>> adj;
int dist[maxN + 1];
pair<int,int> BFS(int rt){
    bool hasVisited[maxN];
    for(int i = 0; i < maxN; i++) hasVisited[i] = false;
    priority_queue<pair<int,int>> pq;
    pq.push(make_pair(0,rt));
    while(!pq.empty()){
        int curNode = pq.top().second;
        int curDist = pq.top().first;
        dist[curNode] = max(-curDist,dist[curNode]);
        hasVisited[curNode] = true;
        pq.pop();
        for(int i: adj[curNode]){
            if(hasVisited[i]) continue;
            pq.push(make_pair(curDist - 1,i));
        }
        if(pq.empty()){
            return make_pair(curDist,curNode);
        }
    }
    return make_pair(-1,-1);
}
int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n - 1; i++){
        int u,v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }
    pair<int,int> pi = BFS(0);
    pair<int,int> pi1 = BFS(pi.second);
    BFS(pi1.second);
    
    for(int i = 0; i < n; i++) cout << dist[i] << " ";
}
