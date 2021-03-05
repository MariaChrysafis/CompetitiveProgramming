#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <fstream>
using namespace std;
vector<bool> marked;
struct edge{
  int u, v, weight;  
};
bool comp(edge e1, edge e2){
    return (e1.weight > e2.weight);
}
struct DSU {
    vector<int> parent;
    vector<int> rank;
    vector<int> connectedComponent;
    int n;
    void init() {
        parent.resize(n);
        rank.resize(n);
        marked.resize(n);
        connectedComponent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
            marked[i] = false;
            connectedComponent[i] = 1;
        }
        //marked.resize(n);
    }
    int find_set(int v) {
        if (v == parent[v]) {
            return v;
        }
        return find_set(parent[v]);
    }
    void unite(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b]) {
                swap(a, b);
            }
            parent[b] = a;
            //connectedComponent[b] = 0;
            connectedComponent[a] += connectedComponent[b];
            connectedComponent[b] = 0;
            if (rank[a] == rank[b]) {
                rank[a]++;
            }
        }
    }
};
int main() {
    std::ifstream in("mootube.in");
	std::ofstream out("mootube.out");
    int n, q;
    in >> n >> q;
    vector<vector<int>> adj(n);
    vector<edge> edges;
    for(int i = 0; i < n - 1; i++){
        int u, v, w;
        in >> u >> v >> w;
        u--;
        v--;
        edges.push_back({u,v,w});
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    DSU dsu;
    dsu.n = n, dsu.init();
    vector<pair<int,int>> queries;
    vector<pair<int,int>> sortedQueries;
    for(int i = 0; i < q; i++){
        int k, v;
        in >> k >> v;
        v--;
        queries.push_back(make_pair(k, v));
        sortedQueries.push_back(make_pair(k, v));
    }
    sort(sortedQueries.begin(), sortedQueries.end());
    reverse(sortedQueries.begin(), sortedQueries.end());
    sort(edges.begin(), edges.end(), comp);
    map<pair<int,int>,int> myMap;
    int ind = 0;
    for(int i = 0; i < sortedQueries.size(); i++){
        int k = sortedQueries[i].first;
        int v = sortedQueries[i].second;
        while(ind < n && edges[ind].weight >= k){
            dsu.unite(edges[ind].u, edges[ind].v);
            ind++;
        }
        int x = dsu.connectedComponent[dsu.find_set(v)] - 1;
        myMap[{k,v}] = x;
    }
    for(pair<int,int> p: queries){
        out << myMap[p] << endl;
    }
}
