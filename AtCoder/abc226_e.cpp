#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
using namespace std;
const int MOD = 998244353;
vector<vector<int>> adj;
vector<bool> hasVisited;
vector<int> nodes;
void dfs (int curNode) {
    if (hasVisited[curNode]) {
        return;
    }
    nodes.push_back(curNode);
    hasVisited[curNode] = true;
    for (int i: adj[curNode]) {
        dfs(i);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m; //[number of nodes, number of edges]
    adj.resize(n);
    hasVisited.assign(n, false);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[--u].push_back(--v), adj[v].push_back(u);
    }
    int cntr = 0;
    for (int i = 0; i < n; i++) {
        if (hasVisited[i]) {
            continue;
        }
        nodes.clear();
        dfs(i);
        int edges = 0;
        for (int j: nodes) {
            edges += adj[j].size();
        }
        edges /= 2;
        if (edges == nodes.size()) {
            cntr++;
            continue;
        }
        cout << 0;
        return 0;
        //cout << edges << " " << nodes.size() << endl;
        cntr++;
    }
    long long x = 1;
    for (int i = 0; i < cntr; i++) {
        x *= 2;
        x %= MOD;
    }
    cout << x;
}
