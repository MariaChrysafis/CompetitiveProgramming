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
struct graph{
    vector<vector<pair<ll,ll>>> adj;
    pair<ll,ll> dijk(ll src){
        vector<ll> dist;
        vector<ll> ways;
        vector<bool> mark;
        dist.resize(adj.size()), mark.resize(adj.size());
        ways.assign(adj.size(), 0);
        for(int i = 0; i < adj.size(); i++){
            dist[i] = -1;
            mark[i] = false;
        }
        dist[src] = 0;
        priority_queue<pair<ll,ll>> pq;
        pq.push({0,src});
        ways[0] = 1;
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
                if(dist[v] > dist[u] + w || dist[v] == -1){
                    dist[v] = dist[u] + w;
                    ways[v] = ways[u];
                    pq.push({-dist[v], v});
                } else if (dist[v] == dist[u] + w) {
                    ways[v] += ways[u];
                    ways[v] %= (int)1e9 + 7;
                }
            }
        }
        return {dist.back(), ways.back()};
    }
};
const ll delta = 2e5;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    graph g1, g2, g3;
    g1.adj.resize(N), g2.adj.resize(N), g3.adj.resize(N);
    while (M--) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        g1.adj[a].push_back({delta * c, b});
        g2.adj[a].push_back({delta * c - 1, b});
        g3.adj[a].push_back({delta * c + 1, b});
    }
    ll minDist = g1.dijk(0).first/delta;
    ll paths = g1.dijk(0).second;
    cout << minDist << " " << paths << " " << g3.dijk(0).first - minDist * delta << " " << -g2.dijk(0).first + minDist * delta << " " << '\n';
}
