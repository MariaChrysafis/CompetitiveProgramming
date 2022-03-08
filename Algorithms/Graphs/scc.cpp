/*
Tested on https://judge.yosupo.jp/problem/scc
*/

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
    vector<vector<int>> comp;
    void dfs (int curNode) {
        vis[curNode] = true;
        for (int i: adj[curNode]) {
            if (!vis[i]) {
                dfs (i);
            }
        }
        order.push_back(curNode);
    }
    void rev_dfs (int curNode) {
        comp.back().push_back(curNode);
        vis[curNode] = true;
        for (int i: adj_rev[curNode]) {
            if (!vis[i]) {
                rev_dfs (i);
            }
        }
    }
public:
    Graph (int n) {
        adj.resize(n);
        adj_rev.resize(n);
    }
    void add_edge (int u, int v) {
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }
    vector<vector<int>> read () {
        vis.assign(adj.size(), false);
        for (int i = 0; i < adj.size(); i++) {
            if (!vis[i]) {
                dfs(i);
            }
        }
        vis.assign(adj.size(), false);
        reverse(order.begin(), order.end());
        for (int i: order) {
            if (!vis[i]) {
                comp.emplace_back();
                rev_dfs(i);
            }
        }
        return comp;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    Graph g(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }
    vector<vector<int>> v = g.read();
    cout << v.size() << '\n';
    for (auto& v1: v) {
        cout << v1.size() << " ";
        for (int i: v1) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}
