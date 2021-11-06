#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <climits>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;
const int INF = (int)1e8;
struct Graph{
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
    freopen("piggyback.in", "r", stdin);
    freopen("piggyback.out", "w", stdout);
    Graph g;
    int B, E, P, N, M;
    cin >> B >> E >> P >> N >> M;
    g.adj.resize(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g.adj[u].push_back({1, v });
        g.adj[v].push_back({1,u});
    }
    vector<int> v1 = g.dijk(0);
    vector<int> v2 = g.dijk(1);
    vector<int> vn = g.dijk(N - 1);
    int myMin = INT_MAX;
    for (int i = 0; i < N; i++) {
        //cout << v1[i] * B + v2[i] * E + vn[i] * P << endl;
        myMin = min(myMin, v1[i] * B + v2[i] * E + vn[i] * P);
    }
    cout << myMin;
}
