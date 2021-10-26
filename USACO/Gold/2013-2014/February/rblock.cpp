#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
#define ll int
struct Graph {
    vector<vector<pair<int,int>>> adj;
    vector<int> path;
    int dijk(int src, int f1, int f2){
        //forbidden edge from f1 to f2
        vector<int> dist;
        vector<int> parent(adj.size());
        vector<bool> mark;
        dist.resize(adj.size()), mark.resize(adj.size());
        for(int i = 0; i < adj.size(); i++){
            dist[i] = (int)1e9;
            mark[i] = false;
        }
        dist[src] = 0;
        priority_queue<pair<int,int>> pq;
        pq.push({0,src});
        while(!pq.empty()){
            int u = pq.top().second; 
            pq.pop();
            if(mark[u]){
                continue;
            }
            mark[u] = true;
            for(auto p: adj[u]){
                if (p.second == f1 && u == f2) continue;
                if (p.second == f2 && u == f1) continue;
                int v = p.second;
                int w = p.first;
                if(dist[v] > dist[u] + w){
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({-dist[v], v});
                }
            }
        }
        int cur = adj.size() - 1;
        while (cur != 0) {
            path.push_back(cur);
            cur = parent[cur];
        }
        path.push_back(0);
        return dist[adj.size() - 1];
    }
};
Graph tot;
int main() {
    freopen("rblock.in", "r", stdin);
    freopen("rblock.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    tot.adj.resize(n);
    map<pair<int,int>,int> weight;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        tot.adj[u].push_back({w, v});
        tot.adj[v].push_back({w, u});
        weight[{u, v}] = weight[{v, u}] = w;
    }
    int sum = tot.dijk(0, -1, -1);
    vector<int> v = tot.path;
    int myMax = 0;
    for (int i = 0; i < v.size() - 1; i++) {
        int p = tot.dijk(0, v[i], v[i + 1]);
        tot.path.clear();
        myMax = max(min(p, sum + weight[{v[i], v[i + 1]}]), myMax);
    }
    cout << myMax - sum << endl;
}
