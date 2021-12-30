#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
#include <deque>


using namespace std;

typedef int64_t ll;

struct Graph {
    vector<vector<pair<int,int>>> adj; //node, weight
    void resz (int n) {
        adj.resize(n);
    }
    void add_edge (int u, int v, int w) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    vector<int> distances (int src) {
        deque<pair<int,int>> d;
        d.push_back({src, 0});
        vector<int> dist;
        dist.assign(adj.size(), -1);
        while (!d.empty()) {
            int curNode = d.front().first;
            int curDist = d.front().second;
            d.pop_front();
            if (dist[curNode] != -1) {
                continue;
            }
            dist[curNode] = curDist;
            for (pair<int,int> p: adj[curNode]) {
                if (p.second == 0) {
                    d.push_front({p.first, curDist});
                } else {
                    d.push_back({p.first, curDist + 1});
                }
            }
        }
        return dist;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    Graph g;
    g.resz(n + 1);
    vector<pair<int,int>> vec(m);
    for (int i = 0; i < m; i++) {
        cin >> vec[i].first >> vec[i].second;
        g.add_edge(vec[i].first - 1, vec[i].second, 0);
    }
    for (int i = 0; i < n; i++) {
        g.add_edge(i, i + 1, 1);
    }
    vector<int> v = g.distances(0);
    for (int i = 0; i < v.size() - 1; i++) {
        int dif = v[i] - v[i + 1];
        if (dif == -1) {
            cout << 0;
        } else {
            cout << 1;
        }
    }

}
