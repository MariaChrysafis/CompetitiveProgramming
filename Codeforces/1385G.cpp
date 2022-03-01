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
class Graph {
    vector<vector<pair<int,int>>> adj;
public:
    vector<int> col;
    vector<int> c = {0, 0};
    vector<int> tot;
    void dfs (int curNode) {
        tot.push_back(curNode);
        for (pair<int,int> p: adj[curNode]) {
            if (col[p.first] != -1) {
                continue;
            }
            col[p.first] = col[curNode] ^ p.second;
            c[col[p.first]]++;
            dfs (p.first);
        }
    }
    void add_edge (int u, int v, int t) {
        adj[u].push_back({v, t}), adj[v].push_back({u, t});
    }
    bool read() {
        for (int i = 0; i < adj.size(); i++) {
            if (col[i] == -1) {
                col[i] = 0;
                c[col[i]]++;
                dfs (i);
                if (c[0] > c[1]) {
                    for (int j: tot) {
                        col[j] = !col[j];
                    }
                }
                c = {0, 0};
                tot.clear();
            }
        }
        for (int i = 0; i < adj.size(); i++) {
            for (pair<int,int> p: adj[i]) {
                if (col[i] != (col[p.first] ^ p.second)) {
                    return false;
                }
            }
        }
        return true;
    }
    Graph (int n) {
        adj.resize(n);
        col.assign(n, -1);
    }
};
void solve () {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    vector<pair<int,int>> oc[n + 1];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        oc[a[i]].emplace_back(i, 0);
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        oc[b[i]].emplace_back(i, 1);
    }
    Graph g(n);
    for (int i = 1; i <= n; i++) {
        if (oc[i].size() != 2) {
            cout << "-1\n";
            return;
        }
        g.add_edge(oc[i][0].first, oc[i][1].first, oc[i][0].second == oc[i][1].second);
    }
    if (!g.read()) {
        cout << "-1\n";
        return;
    }
    vector<int> v1, v0;
    for (int i = 0; i < g.col.size(); i++) {
        if (g.col[i] == 1) {
            v1.push_back(i);
        } else {
            v0.push_back(i);
        }
    }
    if (v1.size() < v0.size()) {
        swap(v1, v0);
    }
    cout << v0.size() << '\n';
    for (int i: v0) {
        cout << i + 1 << ' ';
    }
    cout << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve ();
    }
}
