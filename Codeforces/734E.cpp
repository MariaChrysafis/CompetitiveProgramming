#include <iostream>
#include <cmath>
#include <cassert>
#include <map>
#include <vector>
#include <functional>
#include <queue>
#include <list>
#include <set>
#define ll long long
using namespace std;
vector<vector<int>> adj;
vector<int> connectedComponent;
vector<int> color;
vector<int> depth;
void rec (int curNode, int cntr) {
    connectedComponent[curNode] = cntr;
    for (int i: adj[curNode]) {
        if (color[i] == color[curNode] && connectedComponent[i] == -1) {
            rec(i, cntr);
        }
    }
}
int dfs_for_depth (int curNode, int prevNode) {
    depth[curNode] = -1;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            depth[curNode] = max(dfs_for_depth(i, curNode), depth[curNode]);
        }
    }
    depth[curNode]++;
    return depth[curNode];
}
struct Tree {
    vector<vector<int>> adj;
    int dist[200001];
    pair<int,int> BFS(int rt){
        bool hasVisited[200000];
        for(int i = 0; i < 200000; i++) hasVisited[i] = false;
        priority_queue<pair<int,int>> pq;
        pq.push(make_pair(0,rt));
        while(!pq.empty()){
            int curNode = pq.top().second;
            int curDist = pq.top().first;
            dist[curNode] = curDist;
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
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    color.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> color[i];
    }
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    connectedComponent.assign(n, -1);
    int cntr = 0;
    for (int i = 0; i < n; i++) {
        if (connectedComponent[i] == -1) {
            rec(i, cntr++);
        }
    }
    vector<set<int>> adj1(cntr);
    for (int i = 0; i < n; i++) {
        for (int j: adj[i]) {
            if (connectedComponent[i] != connectedComponent[j]) {
                adj1[connectedComponent[i]].insert(connectedComponent[j]);
            }
        }
    }
    vector<vector<int>> new_adj(cntr);
    for (int i = 0; i < cntr; i++) {
        for (int j: adj1[i]) {
            new_adj[i].push_back(j);
        }
    }
    Tree t;
    t.adj = new_adj;
    pair<int,int> pi = t.BFS(0);
    pair<int,int> pi1 = t.BFS(pi.second);
    cout << (-t.dist[pi1.second] + 1)/2 << endl;
}
