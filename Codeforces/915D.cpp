#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef int64_t ll;

const static int MAX = 501;

struct Graph {
    vector<vector<int>> adj;
    vector<char> color;
    vector<int> parent;
    int cycle_start, cycle_end;

    bool dfs(int v) {
        color[v] = 1;
        for (int u : adj[v]) {
            if (color[u] == 0) {
                parent[u] = v;
                if (dfs(u))
                    return true;
            } else if (color[u] == 1) {
                cycle_end = v;
                cycle_start = u;
                return true;
            }
        }
        color[v] = 2;
        return false;
    }

    vector<int> find_cycle() {
        int n = adj.size();
        color.assign(n, 0);
        parent.assign(n, -1);
        cycle_start = -1;

        for (int v = 0; v < n; v++) {
            if (color[v] == 0 && dfs(v))
                break;
        }

        if (cycle_start == -1) {
            return {};
        } else {
            vector<int> cycle;
            cycle.push_back(cycle_start);
            for (int v = cycle_end; v != cycle_start; v = parent[v])
                cycle.push_back(v);
            cycle.push_back(cycle_start);
            reverse(cycle.begin(), cycle.end());
            return cycle;
        }
    }
};

vector<vector<int>> remove(vector<vector<int>> adj, int u, int v) {
    vector<vector<int>> vec(adj.size());
    for (int i = 0; i < adj.size(); i++) {
        for (int j: adj[i]) {
            if (!(i == u && j == v)) {
                vec[i].push_back(j);
            }
        }
    }
    return vec;
}

bool isCyclic(vector<vector<int>> adj) {
    int n = adj.size();
    priority_queue<int> pq;
    vector<int> deg;
    vector<bool> flag;
    vector<int> v;
    deg.assign(n, 0), flag.assign(n, false);
    for (int i = 0; i < adj.size(); i++) {
        for (int j: adj[i]) {
            deg[j]++;
        }
    }
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            pq.push(i);
        }
    }
    while (!pq.empty()) {
        while (flag[pq.top()] == true) {
            pq.pop();
        }
        int i = pq.top();
        pq.pop();
        if (deg[i] == 0 && flag[i] == false) {
            flag[i] = true;
            v.push_back(i);
            for (int j: adj[i]) {
                deg[j]--;
                if (deg[j] == 0) {
                    pq.push(j);
                }
            }
        }
    }
    return (v.size() == adj.size());
}

int main() {
    int N, M;
    cin >> N >> M;
    Graph g;
    g.adj.resize(N);
    while (M--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g.adj[u].push_back(v);
    }
    vector<int> v = g.find_cycle();
    if (v.empty()) {
        cout << "YES\n";
        return 0;
    }
    for (int i = 1; i < v.size(); i++) {
        //v[i - 1] -> v[i]
        if (isCyclic(remove(g.adj, v[i - 1], v[i]))) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";
}
