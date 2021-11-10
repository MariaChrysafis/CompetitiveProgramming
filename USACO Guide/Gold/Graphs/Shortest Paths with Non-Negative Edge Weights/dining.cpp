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
    vector<ll> dijk(ll src){
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
            ll w = pq.top().first;
            pq.pop();
            if(mark[u]){
                if (u != src || w < dist[u]) {
                    continue;
                }
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
        return dist;
    }
};
int main() {
    freopen("dining.in", "r", stdin);
    freopen("dining.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, K;
    cin >> N >> M >> K;
    Graph g;
    g.adj.resize(N);
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        g.adj[a].push_back({c, b});
        g.adj[b].push_back({c, a});
    }
    vector<ll> dist = g.dijk(N - 1);
    for (int i = 0; i < K; i++) {
        int ind, y;
        cin >> ind >> y;
        ind--;
        int weight = dist[ind] - y - 1;
        g.adj[N - 1].push_back({weight, ind});
    }
    vector<ll> dist1 = g.dijk(N - 1);
    for (int i = 0; i < dist.size() - 1; i++) {
        cout << (dist[i] > dist1[i]) << endl;
        //cout << dist[i] << " " << dist1[i] << '\n';
    }
    //cout << ans;

}
