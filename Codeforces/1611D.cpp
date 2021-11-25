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
struct Graph {
    vector<vector<int>> adj;
    vector<int> parent;
    vector<int> p;
    vector<int> edgeWeight, path;
    void read() {
        edgeWeight.assign(adj.size(), -(int)1e8);
        path.assign(adj.size(), -(int)1e8);
        edgeWeight[p[0]] = 0;
        path[p[0]] = 0;
        for (int i = 1; i < p.size(); i++) {
            if (edgeWeight[parent[p[i]]] < 0) {
                edgeWeight = {};
                break;
            }
            edgeWeight[p[i]] = i - path[parent[p[i]]];
            path[p[i]] = i;
        }
    }
};
void solve () {
    int n;
    cin >> n;
    Graph g;
    g.adj.resize(n);
    g.parent.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> g.parent[i];
        g.parent[i]--;
        if (g.parent[i] != i) {
            g.adj[i].push_back(g.parent[i]);
            g.adj[g.parent[i]].push_back(i);
        } else {
            g.parent[i] = -1;
        }
    }
    g.p.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> g.p[i];
        g.p[i]--;
    }
    g.read();
    if (g.edgeWeight.empty()) {
        cout << "-1\n";
        return;
    }
    for (int i: g.edgeWeight) {
        assert(i >= 0);
        cout << i << ' ';
    }
    cout << '\n';

}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
