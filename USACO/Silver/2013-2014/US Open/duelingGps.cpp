#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <queue>
#include <map>
#define ll signed long long
const ll INF = 1e18;
using namespace std;
struct graph{
    vector<vector<pair<ll,ll>>> adj; //{weight, node}
    vector<ll> parent;
    vector<ll> dijk(ll src){
        vector<ll> dist;
        vector<bool> mark;
        parent.resize(adj.size());
        dist.resize(adj.size()), mark.resize(adj.size());
        for(int i = 0; i < adj.size(); i++){
            dist[i] = INF;
            mark[i] = false;
        }
        dist[src] = 0;
        parent[src] = -1;
        priority_queue<pair<ll,ll>> pq;
        pq.push({0,src});
        while(!pq.empty()){
            ll u = pq.top().second; //node
            pq.pop();
            if(mark[u]){
                continue;
            }
            mark[u] = true;
            for(auto p: adj[u]){
                ll v = p.second;
                ll w = p.first;
                if(dist[v] > dist[u] + w){
                    dist[v] = dist[u] + w;
                    pq.push({-dist[v], v});
                    parent[v] = u;
                }
            }
        }
        return dist;
    }
};
int main() {
    freopen("gpsduel.in", "r", stdin);
    freopen("gpsduel.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    graph gps1, gps2;
    graph gps1_rev, gps2_rev;
    int n, m;
    cin >> n >> m;
    gps1.adj.resize(n), gps1_rev.adj.resize(n);
    gps2.adj.resize(n), gps2_rev.adj.resize(n);
    vector<pair<int,int>> edge;
    map<pair<int,int>, int> myMap1, myMap2;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int a, b;
        cin >> a >> b;
        gps1.adj[u].push_back({a, v});
        gps1_rev.adj[v].push_back({a, u});
        gps2_rev.adj[v].push_back({b, u});
        gps2.adj[u].push_back({b, v});
        edge.push_back({u, v});
        //edge.push_back({v, u});
        if (myMap1[make_pair(u, v)] == 0 || myMap1[make_pair(u, v)] > a) {
            myMap1[{u, v}] = a;
            myMap2[{u, v}] = b;
        }
    }
    vector<ll> dist1_end = gps1_rev.dijk(n - 1);
    vector<ll> dist2_end = gps2_rev.dijk(n - 1);
    graph g;
    g.adj.resize(n);
    for (auto p: edge) {
        int cntr = 0;
        if (dist1_end[p.second] + myMap1[p] != dist1_end[p.first]) {
            cntr++;
        }
        if (dist2_end[p.second] + myMap2[p] != dist2_end[p.first]) {
            cntr++;
        }
        g.adj[p.first].push_back({cntr, p.second});
    }
    vector<ll> v = g.dijk(0);
    cout << v.back();
}
