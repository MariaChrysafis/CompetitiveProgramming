#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <ctime>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

class DisjointSetUnion {
protected:
    vector<int> parent;
    vector<int> compSize;
    const int n;
    int connectedComponents;
public:
    int getConnectedComponents() const {
        return connectedComponents;
    }

public:
    DisjointSetUnion(int sz) : n(sz), connectedComponents(sz) {
        parent.resize(sz), compSize.resize(sz);
        for (int i = 0; i < n; i++) {
            parent[i] = i, compSize[i] = 1;
        }
    }

    int find_head(int x) const {
        int cur = x;
        while (cur != parent[cur]) {
            cur = parent[cur];
        }
        return cur;
    }

    void join(int x, int y) {
        x = find_head(x);
        y = find_head(y);
        if (x == y) {
            return;
        }
        if (compSize[x] > compSize[y]) {
            swap(x, y);
        }
        parent[x] = y;
        compSize[y] += compSize[x];
        connectedComponents--;
    }

    bool comp(int x, int y) {
        return (find_head(x) == find_head(y));
    }
};

struct Edge {
    int u, v, w;
};

struct Graph {
    vector<vector<Edge>> adj;

    void add_edge(int u, int v, int w) {
        adj[u].push_back({u, v, w});
        adj[v].push_back({v, u, w});
    }

    void resz(int n) {
        adj.resize(n);
    }
};

void print(Graph g) {
    for (int i = 0; i < g.adj.size(); i++) {
        for (auto &e: g.adj[i]) {
            cout << e.u << " " << e.v << " " << e.w << '\n';
        }
    }
}

bool isValid(Graph& g, int highestBit) {
    DisjointSetUnion dsu(g.adj.size());
    for (int i = 0; i < g.adj.size(); i++) {
        for (auto &e: g.adj[i]) {
            if (e.w < (1 << (highestBit + 1))) {
                dsu.join(e.u, e.v);
                if (dsu.getConnectedComponents() == 1) {
                    return true;
                }
            }
        }
    }
    return false;
}

void remove_bit(Graph& g, int bit) {
    for (int i = 0; i < g.adj.size(); i++) {
        for (int j = 0; j < g.adj[i].size(); j++) {
            if (g.adj[i][j].w & (1 << bit)) {
                g.adj[i][j].w ^= (1 << bit);
            }
        }
    }
}

int rec(Graph& g) {
    if (isValid(g, -1)) {
        return 0;
    }
    int l = 0;
    int r = 31;
    while (l != r) {
        int m = (l + r) / 2;
        if (isValid(g, m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    remove_bit(g, l);
    return rec(g) + (1 << l);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        Graph g;
        int n, m;
        cin >> n >> m;
        g.resz(n);
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            g.add_edge(u, v, w);
        }
        cout << rec(g) << '\n';
    }
}
