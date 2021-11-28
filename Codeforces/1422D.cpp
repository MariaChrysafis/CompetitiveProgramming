#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;
struct graph{
    vector<vector<pair<ll,ll>>> adj; //{-weight, node}
    vector<ll> dijk(ll src){
        vector<ll> dist;
        vector<bool> mark;
        dist.resize(adj.size()), mark.resize(adj.size());
        for(int i = 0; i < adj.size(); i++){
            dist[i] = (ll)1e12;
            mark[i] = false;
        }
        dist[src] = 0;
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
                }
            }
        }
        return dist;
    }
};
ll distance (pair<ll,ll> p1, pair<ll,ll> p2) {
    return min(abs(p1.first - p2.first), abs(p1.second - p2.second));
}
ll manhattan (pair<ll,ll> p1, pair<ll,ll> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, m;
    cin >> n >> m;
    ll sx, sy, fx, fy;
    cin >> sx >> sy >> fx >> fy;
    vector<pair<pair<ll,ll>,ll>> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i].first.first >> a[i].first.second;
        a[i].second = i;
    }
    graph g;
    g.adj.resize(m + 2);
    for (int t = 0; t < 2; t++){
        sort(a.begin(), a.end());
        for (int i = 1; i < a.size(); i++) {
            ll dist = distance(a[i].first, a[i - 1].first);
            g.adj[a[i].second].emplace_back(dist, a[i - 1].second);
            g.adj[a[i - 1].second].emplace_back(dist, a[i].second);
        }
        for (int i = 0; i < a.size(); i++) {
            swap(a[i].first.first, a[i].first.second);
        }
    }
    for (int i = 0; i < a.size(); i++) {
        ll dist = manhattan(a[i].first, {fx, fy});
        g.adj[a[i].second].emplace_back(dist, m + 1);
    }
    for (int i = 0; i < a.size(); i++) {
        ll dist = distance(a[i].first, {sx, sy});
        g.adj[m].emplace_back(dist, a[i].second);
    }
    vector<ll> v = g.dijk(m);
    cout << min(v[m + 1], abs(sx - fx) + abs(sy - fy)) << '\n';
}
