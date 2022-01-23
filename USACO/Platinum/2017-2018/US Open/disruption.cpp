#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <climits>
#include <cstring>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;

struct Tree {
public:
    vector<vector<int>> adj;
    vector<int> parent;
    vector<int> depth;
public:
    vector<int> weight;

    Tree(int n) {
        adj.resize(n);
        weight.assign(n, (int) 1e9 + 1);
        parent.resize(n);
        depth.resize(n);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }

    void dfs(int curNode, int prevNode) {
        if (prevNode == -1) depth[curNode] = 0;
        else depth[curNode] = depth[prevNode] + 1;
        //cout << "parent of " << curNode << " is " << prevNode << '\n';
        parent[curNode] = prevNode;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs(i, curNode);
            }
        }
    }

    void query(int u, int v, int w) {
        //find the least common ancestor of u and v
        vector<int> nodes;
        while (u != v) {
            if (depth[u] > depth[v]) {
                nodes.push_back(u);
                u = parent[u];
            } else if (depth[u] < depth[v]) {
                nodes.push_back(v);
                v = parent[v];
            } else {
                nodes.push_back(u), nodes.push_back(v);
                v = parent[v], u = parent[u];
            }
        }
        int lca = u;
        for (int i: nodes) {
            weight[i] = min(weight[i], w);
            parent[i] = lca;
            depth[i] = depth[lca] + 1;
        }
    }
};

int main() {
    freopen("disrupt.in", "r", stdin);
    freopen("disrupt.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    Tree t(n);
    vector<pair<int, int>> edges;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t.add_edge(u - 1, v - 1);
        edges.emplace_back(u - 1, v - 1);
    }
    vector<pair<int, pair<int, int>>> vec;
    for (int i = 0; i < m; i++) {
        int u, v, r;
        cin >> u >> v >> r;
        u--, v--;
        vec.push_back({r, {u, v}});
    }
    sort(vec.begin(), vec.end());
    t.dfs(0, -1);
    for (int i = 0; i < edges.size(); i++) {
        if (t.parent[edges[i].second] == edges[i].first) {
            swap(edges[i].second, edges[i].first);
        }
    }
    for (auto &p: vec) {
        t.query(p.second.first, p.second.second, p.first);
    }
    for (auto &p: edges) {
        //cout << p.first << '\n';
        if (t.weight[p.first] > (int) 1e9) {
            t.weight[p.first] = -1;
        }
        cout << t.weight[p.first] << '\n';
    }
}
