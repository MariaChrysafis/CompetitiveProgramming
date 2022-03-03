#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#include <stack>

using namespace std;
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long ll;

const int MAXN = 5e5;

class DisjointSetUnion {
public:
    vector<int> parent;
    vector<int> compSize;

    int find_head(int u) {
        if (u == parent[u]) {
            return u;
        }
        return find_head(parent[u]);
    }

    void join(int u, int v) {
        u = find_head(u), v = find_head(v);
        if (u == v) {
            return;
        }
        if (compSize[u] > compSize[v]) {
            swap(u, v);
        }
        compSize[v] += compSize[u];
        compSize[u] = 0;
        parent[v] = u;
    }

    bool comp(int u, int v) {
        return find_head(u) == find_head(v);
    }

    DisjointSetUnion(int n) {
        parent.resize(n), compSize.assign(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
};

class Graph {
public:
    int n; // number of nodes
    vector<vector<int>> adj; // adjacency list of graph
    map<pair<int,int>,int> myMap;

    void add_edge (int u, int v) {
        if (u == v) {
            return;
        }
        myMap[{u,v}]++; myMap[{v, u}]++;
        if (myMap[{u, v}] >= 2) {
            return;
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited;
    vector<int> tin, low;
    set<pair<int,int>> br;
    int timer = 0;
    Graph (int n) {
        this->n = n;
        adj.resize(n);
    }
    void dfs(int v, int p = -1) {
        visited[v] = true;
        tin[v] = low[v] = timer++;
        for (int to : adj[v]) {
            if (to == p) continue;
            if (visited[to]) {
                low[v] = min(low[v], tin[to]);
            } else {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] > tin[v])
                    br.insert({v, to});
            }
        }
    }

    void find_bridges() {
        timer = 0;
        visited.assign(n, false);
        //return;
        tin.assign(n, -1);
        low.assign(n, -1);
        for (int i = 0; i < n; ++i) {
            if (!visited[i])
                dfs(i);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    map<int,vector<pair<int,int>>> myMap;
    map<pair<int,int>,int> id;
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        id[{u, v}] = id[{v, u}] = i;
        myMap[w].push_back({u, v});
    }
    DisjointSetUnion dsu(N);
    string ans[M];
    for (auto& q: myMap) {
        map<int,int> key; int cntr = 1;
        for (pair<int,int> p: q.second) {
            pair<int,int> orig = p;
            p.first = dsu.find_head(p.first);
            p.second = dsu.find_head(p.second);
            if (p.first == p.second) {
                ans[id[orig]] = "none";
                continue;
            }
            if (!key.count(p.first)) {
                key[p.first] = cntr;
                cntr++;
            }
            if (!key.count(p.second)) {
                key[p.second] = cntr;
                cntr++;
            }
        }
        Graph gr(cntr);
        for (pair<int,int> p: q.second) {
            gr.add_edge(key[dsu.find_head(p.first)], key[dsu.find_head(p.second)]);
        }
        gr.find_bridges();
        for (pair<int,int> p: q.second) {
            pair<int,int> orig = p;
            p.first = key[dsu.find_head(p.first)];
            p.second = key[dsu.find_head(p.second)];
            if (p.first == p.second) continue;
            if ((gr.br.count(p) || gr.br.count({p.second,p.first})) && gr.myMap[p] == 1) {
                ans[id[orig]] = "any";
            }
        }
        for (pair<int,int> p: q.second) {
            dsu.join(p.first, p.second);
        }
    }
    for (string &s: ans) {
        if (s.empty()) {
            cout << "at least one\n";
            continue;
        }
        cout << s << '\n';
    }
}
