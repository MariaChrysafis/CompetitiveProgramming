#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <set>
#include <chrono>

#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>

#pragma GCC optimize("O3")

#define ll long long
const int MOD = 1e9 + 7;
using namespace std;

struct Graph {
    vector<vector<int>> adj;
    vector<int> comp;
    vector<bool> hasVisited;
    int cntr = 0;

    void dfs(int curNode, int col) {
        hasVisited[curNode] = true;
        comp[curNode] = col;
        for (int i: adj[curNode]) {
            if (!hasVisited[i]) {
                dfs(i, col);
            }
        }
    }

    void call() {
        comp.resize(adj.size());
        hasVisited.resize(adj.size());
        for (int i = 0; i < adj.size(); i++) {
            hasVisited[i] = false;
        }
        for (int i = 0; i < adj.size(); i++) {
            if (!hasVisited[i]) {
                dfs(i, cntr);
                cntr++;
            }
        }
    }
};

vector<int> cost;
vector<vector<int>> inp;
Graph g;

struct DSU {
    vector<int> e;

    void init(int N) { e = vector<int>(N, -1); }
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }

    bool sameSet(int a, int b) { return get(a) == get(b); }

    int size(int x) { return -e[get(x)]; }

    bool unite(int x, int y) { // union by size
        x = get(x), y = get(y);
        if (x == y) return 0;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return 1;
    }
};

int cnt = 0;

template<class T>
T kruskal(int N, vector<pair<T, pair<int, int>>> ed) {
    sort(ed.begin(), ed.end());
    T ans = 0;
    DSU D;
    D.init(N + 1); // edges that unite are in MST
    for (auto a: ed) {
        if (D.unite(a.second.first, a.second.second)) {
            ans += a.first;
            cnt++;
        }
    }
    return ans;
}

int main() {
    //freopen("haha", "r", stdin);
    int n;
    cin >> n;
    g.adj.resize(2 * n);
    for (int i = 0; i < n; i++) {
        int co;
        cin >> co;
        cost.push_back(co);
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--, b--, c--, d--;
        inp.push_back({{a, b, c, d}});
        g.adj[a].push_back(b), g.adj[b].push_back(a);
        g.adj[c].push_back(d), g.adj[d].push_back(c);
    }
    g.call();
    vector<pair<int, pair<int, int>>> edge;
    for (int i = 0; i < inp.size(); i++) {
        int a = inp[i][0];
        int b = inp[i][1];
        int d = inp[i][3];
        assert(g.comp[a] == g.comp[b]);
        if (g.comp[a] == g.comp[d]) {
            continue;
        }
        edge.push_back({cost[i], {g.comp[d], g.comp[a]}});
    }
    cout << kruskal(g.cntr, edge);
}
