#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef int64_t ll;

const ll INF = 1e17;

struct Graph {
    vector<vector<pair<ll,ll>>> adj; //{weight, node}
    void add_edge (int u, int v, int w) {
        adj[u].push_back({w, v});
    }
    vector<ll> dijk(int src){
        vector<ll> dist;
        vector<bool> mark;
        dist.resize(adj.size()), mark.resize(adj.size());
        for(int i = 0; i < adj.size(); i++){
            dist[i] = INF;
            mark[i] = false;
        }
        dist[src] = 0;
        priority_queue<pair<ll,ll>> pq;
        pq.push({0,src});
        while(!pq.empty()){
            int u = pq.top().second; //node
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

ll read () {
    ll x;
    cin >> x;
    return x;
}

int main() {
    ll N = read();
    vector<pair<ll,ll>> vec(N);
    for (int i = 0; i < N; i++) {
        vec[i] = {read(), read()};
    }
    sort(vec.begin(), vec.end());
    Graph g;
    g.adj.resize(N);
    for (int i = 1; i < N; i++) {
        g.add_edge(i, i - 1, 0);
    }
    for (int i = 0; i < N; i++) {
        int l = 0;
        int r = N - 1;
        while (l != r) {
            int mid = (l + r + 1)/2;
            if (vec[mid].first - (vec[i].first + vec[i].second) <= 0) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        if (vec[l].first - (vec[i].first + vec[i].second) <= 0) {
            g.add_edge(i, l, 0);
            if (l + 1 < N) {
                g.add_edge(i, l + 1, vec[l + 1].first - (vec[i].first + vec[i].second));
            }
        }
    }
    ll ans = g.dijk(0).back();
    for (auto& p: vec) {
        ans += p.second;
    }
    cout << ans;
}
