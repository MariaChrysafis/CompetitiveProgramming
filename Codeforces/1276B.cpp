#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
#include <array>
 
#define ll long long
#define endl '\n'
 
using namespace std;
const int INF = 1e9;
struct graph{
    vector<vector<pair<int,int>>> adj; //{-weight, node}
    vector<ll> dijk(int src){
        vector<ll> dist;
        vector<bool> mark;
        dist.resize(adj.size()), mark.resize(adj.size());
        for(int i = 0; i < adj.size(); i++){
            dist[i] = INF;
            mark[i] = false;
        }
        dist[src] = 0;
        priority_queue<pair<int,int>> pq;
        pq.push({0,src});
        while(!pq.empty()){
            int u = pq.top().second; //node
            pq.pop();
            if(mark[u]){
                continue;
            }
            mark[u] = true;
            for(auto p: adj[u]){
                int v = p.second;
                int w = p.first;
                if(dist[v] > dist[u] + w){
                    dist[v] = dist[u] + w;
                    pq.push({-dist[v], v});
                }
            }
        }
        return dist;
    }
};
void print(vector<ll> v){
    for(ll i: v){
        cout << i << " ";
    }
    cout << endl;
}
void solve() {
    graph g;
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    a--, b--;
    g.adj.resize(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        g.adj[u].push_back({1, v});
        g.adj[v].push_back({1, u});
    }
    vector<ll> da = g.dijk(a);
    vector<ll> db = g.dijk(b);
    vector<vector<pair<int,int>>> adj1(n), adj2(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < g.adj[i].size(); j++){
            if(i != a && g.adj[i][j].second != a) adj1[i].push_back(g.adj[i][j]);
            if(i != b && g.adj[i][j].second != b) adj2[i].push_back(g.adj[i][j]);
        }
    }
    g.adj = adj1;
    vector<ll> woA = g.dijk(b);
    //print(woA);
    g.adj = adj2;
    vector<ll> woB = g.dijk(a);
    //print(woB);
    ll fromA = 0;
    ll fromB = 0;
    for(int i = 0; i < n; i++){
        if(da[i] + db[i] == da[b]) continue;
        if(woA[i] != INF && woB[i] != INF) continue;
        //cout << i << " ";
        if(da[i] + da[b] == db[i]) fromA++;
        else if(db[i] + db[a] == da[i]) fromB++;
    }
    cout << fromA * fromB << endl;
 
}
 
int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
