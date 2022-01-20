#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <map>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;
typedef long long ll;

struct Tuple {
    int src;
    int cur;
    ll path_length;
    bool operator < (const Tuple& t1) const {
        if (path_length != t1.path_length) return (path_length > t1.path_length);
        if (src != t1.src) return (src > t1.src);
        return (cur > t1.cur);
    }
};

const ll INF = 1e18;

struct Graph {
    vector<vector<pair<ll, int>>> adj; //{weight, node}
    vector<ll> soFar;
    void dijk () {
        map<pair<int,int>,ll> dist;
        map<pair<int,int>,bool> hasVisited;
        priority_queue <Tuple> pq;
        vector<pair<int,pair<int,int>>> edges;
        for (int i = 0; i < adj.size(); i++) {
            for (auto& p: adj[i]) {
                edges.push_back({p.first, {p.second, i}});
            }
            hasVisited[{i, i}] = true;
        }
        sort(edges.begin(), edges.end());
        int n = adj.size();
        adj.clear();
        adj.resize(n);
        for (int i = 0; i < min((int)edges.size(), 800); i++) {
            adj[edges[i].second.first].push_back({edges[i].first, edges[i].second.second});
            pq.push({edges[i].second.first, edges[i].second.second, edges[i].first});
        }
        while (!pq.empty()) {
            Tuple myTuple = pq.top();
            pq.pop();
            if (hasVisited[{myTuple.src, myTuple.cur}]) {
                continue;
            }
            soFar.push_back(myTuple.path_length);
            if (soFar.size() == 800) {
                break;
            }
            hasVisited[{myTuple.src, myTuple.cur}] = true;
            for (auto& p: adj[myTuple.cur]) {
                int v = p.second;
                ll w = p.first;
                if (myTuple.path_length + w < dist[{myTuple.src, v}] || dist[{myTuple.src, v}] == 0) {
                    dist[{myTuple.src, v}] = myTuple.path_length + w;
                    pq.push({myTuple.src, v, dist[{myTuple.src, v}]});
                }
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, K;
    cin >> N >> M >> K;
    Graph g;
    g.adj.resize(N);
    while (M--) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        //cout << u << "-> " << v << ": " << w << '\n';
        g.adj[u].push_back({w, v});
        g.adj[v].push_back({w, u});
    }
    g.dijk();
    cout << g.soFar[(K - 1) * 2] << '\n';
}
