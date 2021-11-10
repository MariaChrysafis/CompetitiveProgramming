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
int N, T;
int convert (pair<int,int> p) {
    return p.first * N + p.second;
}
int main() {
    freopen("visitfj.in", "r", stdin);
    freopen("visitfj.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> T;
    Graph g;
    g.adj.resize(N * N);
    int arr[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int dx = -3; dx <= 3; dx++) {
                for (int dy = -3; dy <= 3; dy++) {
                    if (abs(dx) + abs(dy) == 3 || abs(dx) + abs(dy) == 1) {
                        if (i + dx < 0 || i + dx >= N) continue;
                        if (j + dy < 0 || j + dy >= N) continue;
                        pair<int,int> cur = {i, j};
                        pair<int,int> nxt = {i + dx, j + dy};
                        g.adj[convert(cur)].emplace_back(arr[i + dx][j + dy] + 3 * T, convert(nxt));
                        //cout << cur.first << " " << cur.second << "-->" << nxt.first << " " << nxt.second << "|" << arr[i + dx][j + dy] << endl;
                    }
                }
            }
            if (abs(i - (N - 1)) + abs(j - (N - 1)) <= 2) {
                g.adj[convert({i, j})].emplace_back(T * (abs(i - (N - 1)) + abs(j - (N - 1))), convert({N - 1, N - 1}));
            }
        }
    }
    cout << g.dijk(convert({0, 0}));
}
