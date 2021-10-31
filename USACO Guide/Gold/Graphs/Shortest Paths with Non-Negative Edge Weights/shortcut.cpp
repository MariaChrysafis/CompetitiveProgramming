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
            ll u = -pq.top().second; //node
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
                    pq.push({-dist[v], -v});
                    parent[v] = u;
                }
                if (dist[v] == dist[u] + w && parent[v] > u) {
                    dist[v] = dist[u] + w;
                    pq.push({-dist[v], -v});
                    parent[v] = u;
                }
            }
        }
        return dist;
    }
    vector<ll> path (ll a) {
        //from a to 1
        vector<ll> v = {a};
        while (v.back() != 0) {
            v.push_back(parent[v.back()]);
        }
        return v;
    }
};
int main() {
    freopen("shortcut.in", "r", stdin);
    freopen("shortcut.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, T;
    cin >> N >> M >> T;
    graph g;
    vector<ll> v(N);
    for (int i = 0; i < v.size(); i++) {
        cin >> v[i];
    }
    g.adj.resize(N);
    set<pair<int,int>> myMap[N];
    for (int i = 0; i < M; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        a--, b--;
        g.adj[a].emplace_back(t, b);
        g.adj[b].emplace_back(t, a);
        //myMap[{a, b}] = t;
        //myMap[{b, a}] = t;
        myMap[a].insert({b, t});
        myMap[b].insert({a, t});
    }
    vector<ll> dist = g.dijk(0);
    ll cur = 0;
    for (int i = 0; i < dist.size(); i++) {
        cur += dist[i] * v[i];
    }
    vector<ll> cost(N);
    for (int i = 0; i < N; i++) {
        cost[i] = 0;
    }
    for (int i = 1; i < N; i++) {
        vector<ll> vec = g.path(i);
        ll dist_i_j = 0;
        for (int j = 0; j < vec.size(); j++) {
            // we try having a time travel ticket position j
            // we are currently at i
            if (dist_i_j + T < dist[i]) {
                cost[vec[j]] += (dist[i] - (dist_i_j + T)) * v[i];
            }
            if (j + 1 != vec.size()) {
                auto it = myMap[vec[j]].upper_bound({vec[j + 1], 0});
                pair<int,int> p = *it;
                dist_i_j += p.second;
            }
        }
    }
    ll myMax = 0;
    for (int i = 0; i < cost.size(); i++) {
        //cout << cost[i] << " ";
        myMax = max(myMax, cost[i]);
    }
    //cout << '\n';
    cout << myMax;
}
