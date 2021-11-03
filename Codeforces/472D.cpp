#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <set>
#define ll long long
using namespace std;
struct Pair {
    ll neighbor, weight;
};
bool operator<(Pair a, Pair b){
    return a.weight > b.weight;
}
struct Graph {
    ll n;
    ll INF = 1e16;
    ll weight[100000];
    ll mark[100000];
    ll parent[100000];
    vector <Pair> graph[100000];
    priority_queue <Pair> pq;

    vector<pair<ll,ll>> mst() {
        for (ll i = 0; i <= n; i++) {
            weight[i] = INF;
            mark[i] = false;
        }
        weight[0] = 0;
        Pair p = {0, 0};
        parent[0] = -1;
        pq.push(p);
        ll counter = 0;
        while (!pq.empty()) {
            counter++;
            ll x = pq.top().neighbor;
            pq.pop();
            if (mark[x]) {
                continue;
            }
            mark[x] = true;
            for (Pair pr: graph[x]) {
                ll a = pr.neighbor;
                ll b = pr.weight;
                if (!mark[a] && weight[a] > b) {
                    weight[a] = b;
                    parent[a] = x;
                    pq.push(pr);
                }
            }
        }
        vector<pair<ll,ll>> vec;
        for (ll i = 1; i < n; i++) {
            vec.push_back(make_pair(i, parent[i]));
        }
        return vec;
    }
};
struct graph{
    vector<vector<pair<ll,ll>>> adj; //{-weight, node}
    vector<ll> dijk(ll src){
        vector<ll> dist;
        vector<bool> mark;
        dist.resize(adj.size()), mark.resize(adj.size());
        for(ll i = 0; i < adj.size(); i++){
            dist[i] = 1e17;
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
int main() {
    //freopen("walk.in", "r", stdin);
    //freopen("walk.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //int n;
    Graph g;
    cin >> g.n;
    vector<vector<ll>> arr(g.n);
    for (ll i = 0; i < g.n; i++) {
        arr[i].resize(g.n);
        for (ll j = 0; j < g.n; j++) {
            ll x;
            cin >> x;
            arr[i][j] = x;
            if (i != j) {
                g.graph[i].push_back({j,x});
            }
            if (arr[i][j] == 0 && i != j) {
                cout << "NO\n";
                return 0;
            }
        }
    }
    graph g1;
    g1.adj.resize(g.n);
    vector<pair<ll,ll>> a = g.mst();
    for (pair<ll,ll> p: a) {
        g1.adj[p.first].push_back({arr[p.first][p.second], p.second});
        g1.adj[p.second].push_back({arr[p.first][p.second], p.first});
    }
    vector<vector<ll>> distances;
    for (int i = 0; i < g.n; i++) {
        distances.push_back(g1.dijk(i));
        for (int j = 0; j < distances.back().size(); j++) {
            if (distances.back()[j] == 0 && j != i) {
                cout << "NO\n";
                return 0;
            }
        }
    }
    if (arr == distances) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}
