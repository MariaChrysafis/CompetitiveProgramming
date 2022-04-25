#include <cmath>
#include <iostream>
#include <set>
#include <vector>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;

class Graph {
public:
    void add_edge (int a, int b) {
        adj[a].push_back(b);
        rev_adj[b].push_back(a);
    }
    Graph (int n) {
        adj.resize(n), rev_adj.resize(n);
    }
    vector<int> order;
    vector<vector<int>> v;
    vector<vector<int>> adj;
    vector<vector<int>> rev_adj;
    vector<bool> hasVisited;
    void dfs1 (int curNode) {
        if (hasVisited[curNode]) return;
        hasVisited[curNode] = true;
        for (int i: adj[curNode]) {
            dfs1 (i);
        }
        order.push_back(curNode);
    }
    void dfs2 (int curNode) {
        if (hasVisited[curNode]) return;
        v.back().push_back(curNode);
        hasVisited[curNode] = true;
        for (int i: rev_adj[curNode]) {
            dfs2(i);
        }
    }
    void read() {
        hasVisited.assign(adj.size(), false);
        for (int i = 0; i < adj.size(); i++) {
            dfs1(i);
        }
        hasVisited.assign(adj.size(), false);
        reverse(order.begin(), order.end());
        for (int i = 0; i < adj.size(); i++) {
            if (!hasVisited[order[i]]) {
                v.emplace_back();
                dfs2(order[i]);
            }
        }
        vector<int> id(adj.size());
        for (int i = 0; i < v.size(); i++) {
            for (int j: v[i]) {
                id[j] = i;
            }
        }
        vector<vector<int>> new_adj(v.size()), new_adj_rev(v.size());
        vector<int> deg; deg.assign(v.size(), 0);
        for (int i = 0; i < adj.size(); i++) {
            for (int j: adj[i]) {
                if (id[i] != id[j]) {
                    new_adj[id[i]].push_back(id[j]);
                    new_adj_rev[id[j]].push_back(id[i]);
                }
            }
        }
        queue<int> q;
        for (int i = 0; i < v.size(); i++) {
            deg[i] = new_adj[i].size();
            if (deg[i] == 0) {
                q.push(i);
            }
        }
        vector<int> nodes;
        while (!q.empty()) {
            int x = q.front();
            nodes.push_back(x);
            q.pop();
            for (int i: new_adj_rev[x]) {
                deg[i]--;
                if (deg[i] == 0) {
                    q.push(i);
                }
            }
        }
        vector<vector<int>> act(v.size());
        for (int i = 0; i < v.size(); i++) {
            act[i] = v[nodes[i]];
        }
        cout << act.size() << '\n';
        reverse(act.begin(), act.end());
        for (int i = 0; i < act.size(); i++) {
            cout << act[i].size() << ' ';
            for (int j: act[i]) {
                cout << j << ' ';
            }
            cout << '\n';
        }
    }
};

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m; cin >> n >> m;
    Graph gr(n);
    while (m--) {
        int u, v; cin >> u >> v;
        gr.add_edge(u, v);
    }
    gr.read();
}
