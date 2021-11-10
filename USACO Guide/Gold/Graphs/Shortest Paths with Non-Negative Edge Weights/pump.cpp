#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#define ll long long
#include <map>

using namespace std;
struct Graph {
    vector<vector<pair<ll,ll>>> adj;
    vector<ll> path;
    ll dijk(ll src){
        vector<ll> dist;
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
                ll v = p.second;
                ll w = p.first;
                if(dist[v] > dist[u] + w){
                    dist[v] = dist[u] + w;
                    pq.push({-dist[v], v});
                }
            }
        }
        return dist[adj.size() - 1];
    }
};
struct Node {
    int cost;
    int flow;
    int u;
};
int main() {
    freopen("pump.in", "r", stdin);
    freopen("pump.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    vector<vector<Node>> vec(N);
    for (int i = 0; i < M; i++) {
        int u, v, c, f;
        cin >> u >> v >> c >> f;
        u--, v--;
        vec[u].push_back({c, f, v});
        vec[v].push_back({c, f, u});
    }
    double myMax = 0;
    for (int flow = 1; flow <= 1000; flow++) {
        Graph g;
        g.adj.resize(N);
        for (int i = 0; i < N; i++) {
            for (Node myNode: vec[i]) {
                if (myNode.flow >= flow) {
                    g.adj[i].push_back({myNode.cost, myNode.u});
                }
            }
        }
        //cout << flow << " " << g.dijk(0) << endl;
        myMax = max(myMax, (1.0 * flow)/(1.0 * g.dijk(0)));
    }
    cout << floor(myMax * 1e6);

}
