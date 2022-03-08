#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <ctime>
#include <cstdlib>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;
struct Graph {
private:
    vector<vector<int>> adj;
    vector<vector<int>> adj_rev;
    vector<bool> vis;
    vector<int> order;
    vector<int> id;
    void dfs (int curNode) {
        vis[curNode] = true;
        for (int i: adj[curNode]) {
            if (!vis[i]) {
                dfs (i);
            }
        }
        order.push_back(curNode);
    }
    void rev_dfs (int curNode, int cntr) {
        id[curNode] = cntr;
        vis[curNode] = true;
        for (int i: adj_rev[curNode]) {
            if (!vis[i]) {
                rev_dfs (i, cntr);
            }
        }
    }
public:
    void resz (int n) {
        adj.resize(n);
        adj_rev.resize(n);
    }
    void add_edge (int u, int v) {
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }
    vector<int> read () {
        id.resize(adj.size());
        vis.assign(adj.size(), false);
        for (int i = 0; i < adj.size(); i++) {
            if (!vis[i]) {
                dfs(i);
            }
        }
        vis.assign(adj.size(), false);
        reverse(order.begin(), order.end());
        int cntr = 0;
        for (int i: order) {
            if (!vis[i]) {
                cntr++;
                rev_dfs(i, cntr);
            }
        }
        return id;
    }
};
struct TwoSat {
    Graph g;
    int n;
    TwoSat (int N) {
        g.resz(2 * (N + 2));
        n = N;
    }
    int rec (int x) {
        if (x < 0) {
            return abs(x) + n;
        }
        return x;
    }
    void implies (int x, int y) {
        g.add_edge(rec(x), rec(y));
    }
    void add_or (int x, int y) {
        implies(-x, y);
        implies(-y, x);
    }
    void read () {
        vector<int> id = g.read();
        for (int i = 1; i <= n; i++) {
            if (id[rec(i)] == id[rec(-i)]) {
                cout << "s UNSATISFIABLE\n";
                exit(0);
            }
        }
        cout << "s SATISFIABLE\nv ";
        for (int i = 1; i <= n; i++) {
            if (id[rec(i)] > id[rec(-i)]) {
                cout << i << ' ';
            } else {
                cout << -i << ' ';
            }
        }
        cout << 0 << ' ';
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s1, s2; cin >> s1 >> s2;
    int N, M;
    cin >> N >> M;
    TwoSat ts(N);
    while (M--) {
        int u, v, w;
        cin >> u >> v >> w;
        ts.add_or(u, v);
    }
    ts.read();
}
