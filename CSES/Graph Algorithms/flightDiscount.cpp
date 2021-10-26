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
#define ll long long
struct Graph {
    vector<vector<pair<ll,ll>>> adj;
    vector<ll> path;
    vector<ll> distances;
    ll dijk(ll src, ll f1, ll f2){
        //forbidden edge from f1 to f2
        vector<ll> dist;
        vector<ll> parent(adj.size());
        vector<bool> mark;
        dist.resize(adj.size()), mark.resize(adj.size());
        for(int i = 0; i < adj.size(); i++){
            dist[i] = (ll)1e15;
            mark[i] = false;
        }
        dist[src] = 0;
        priority_queue<pair<ll,ll>> pq;
        pq.push({0,src});
        while(!pq.empty()){
            ll u = pq.top().second;
            pq.pop();
            if(mark[u]){
                continue;
            }
            mark[u] = true;
            for(auto p: adj[u]){
                if (p.second == f1 && u == f2) continue;
                if (p.second == f2 && u == f1) continue;
                ll v = p.second;
                ll w = p.first;
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
        distances = dist;
        return dist[adj.size() - 1];
    }
};
Graph pref, suf;
int main() {
    //freopen("hamming.in", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    pref.adj.resize(n);
    suf.adj.resize(n);
    map<pair<ll,ll>,ll> weight;
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        pref.adj[u].push_back({w, v});
        suf.adj[v].push_back({w, u});
        weight[{u, v}] = w;
    }
    pref.dijk(0, -1, -1);
    suf.dijk(n - 1, -1, -1);
    vector<ll> v = pref.path;
    ll myMin = (long long)1e15;
    for (int i = 0; i < n; i++) {
        for (auto p: pref.adj[i]) {
            int j = p.second;
            //cout << i << " " << j << " " << pref.distances[i] << " " << suf.distances[j]  << '\n';
            myMin = min(pref.distances[i] + suf.distances[j] + weight[{i, j}] / 2, myMin);
        }
    }
    cout << myMin << endl;
}
