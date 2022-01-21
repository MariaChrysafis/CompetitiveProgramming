#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;
struct Graph {
    vector<vector<int>> adj;
    map<pair<int,int>,int> myMap;
    vector<int> col;
    int cc = 0;
    bool okay = true;
    Graph (int n) {
        col.assign(n, -1);
        adj.resize(n);
    }

    void add_edge (int u, int v, int w) {
        adj[u].push_back(v), adj[v].push_back(u);
        myMap[{u, v}] = myMap[{v, u}] = w;
    }

    void dfs (int curNode) {
        for (int i: adj[curNode]) {
            int nxt = (col[curNode] + myMap[{i, curNode}]) % 2;
            if (col[i] == -1) {
                col[i] = nxt;
                dfs (i);
            } else {
                if (col[i] != nxt) {
                    okay = false;
                }
            }
        }
    }
    void read () {
        for (int i = 0; i < adj.size(); i++) {
            if (col[i] == -1) {
                col[i] = 0;
                dfs(i);
                cc++;
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    Graph g(N);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.add_edge(u - 1, v - 1, !w);
    }
    g.read();
    if (!g.okay) {
        cout << 0;
        return 0;
    }
    ll x = 1;
    while (--g.cc) {
        x *= 2;
        x %= ((int)1e9 + 7);
    }
    cout << x;

}
