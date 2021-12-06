#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#define ll long long
using namespace std;

struct Graph {
    vector<vector<int>> adj;
    vector<int> color;
    bool fine = true;
    ll oc[3] = {0, 0, 0};
    void dfs (int curNode, int col) {
        if (color[curNode] != 0) {
            if (color[curNode] != col) {
                fine = false;
            }
            return;
        }
        color[curNode] = col;
        oc[col]++;
        for (int i: adj[curNode]) {
            dfs(i, col % 2 + 1);
        }
    }
    ll read() {
        ll ans = 0;
        color.assign(adj.size(), 0);
        for (int i = 0; i < adj.size(); i++) {
            if (color[i] == 0) {
                dfs(i, 0);
                ans += oc[1] * (oc[1] - 1)/2 + oc[2] * (oc[2] - 1)/2;
                oc[0] = oc[1] = oc[2] = 0;
            }
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, m;
    cin >> n >> m;
    Graph g; g.adj.resize(n);
    int maxDeg = 0;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g.adj[u].push_back(v), g.adj[v].push_back(u);
        maxDeg = max({(int)g.adj[u].size(), (int)g.adj[v].size(), maxDeg});
    }
    if (maxDeg == 0) {
        cout << "3 ";
        cout << n * (n - 1) * (n - 2)/6;
        return 0;
    }
    if (maxDeg == 1) {
        cout << 2 << ' ' << (n - 2) * m;
        return 0;
    }
    ll ans = g.read();
    if (!g.fine) {
        cout << "0 1";
        return 0;
    }
    cout << 1 << " " << ans << endl;
}
