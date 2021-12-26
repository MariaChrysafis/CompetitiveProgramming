#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

typedef long long ll;
using namespace std;
const ll MOD = 1e9 + 7;
struct graph{
    const int INF = 1e9;
    vector<vector<pair<int,int>>> adj; //{-weight, node}
    vector<int> dijk(int src){
        vector<int> dist;
        vector<bool> mark;
        dist.resize(adj.size()), mark.resize(adj.size());
        for(int i = 0; i < adj.size(); i++){
            dist[i] = INF;
            mark[i] = false;
        }
        dist[src] = 0;
        priority_queue<pair<int,int>> pq;
        pq.push({0,src});
        while(!pq.empty()){
            int u = pq.top().second; //node
            pq.pop();
            if(mark[u]){
                continue;
            }
            mark[u] = true;
            for(auto p: adj[u]){
                int v = p.second;
                int w = p.first;
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
    freopen("vacation.in", "r", stdin);
    freopen("vacation.out", "w", stdout);
    int N, M, K, Q;
    cin >> N >> M >> K >> Q;
    graph g;
    g.adj.resize(N);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g.adj[u].push_back({w, v});
    }
    vector<vector<int>> dist;
    for (int i = 0; i < N; i++) {
        dist.push_back(g.dijk(i));
    }
    ll sum = 0;
    ll cnt = 0;
    while (Q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int myMin = 1e9;
        for (int i = 0; i < K; i++) {
            myMin = min(myMin, dist[u][i] + dist[i][v]);
        }
        if (myMin != 1e9) {
            cnt++;
            sum += myMin;
        }
        //cout << myMin << " " << dist[u][v] << '\n';
    }
    cout << cnt << '\n' << sum;

}
