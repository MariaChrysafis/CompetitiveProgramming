#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;
bool okay (vector<vector<int>> &adj, int x, bool b) {
    int val[(int)adj.size()];
    for (int i = 0; i < (int)adj.size(); i++) {
        val[i] = adj[x][i] ^ b;
    }
    for (int i = 0; i < adj.size(); i++) {
        for (int j = 0; j < adj.size(); j++) {
            if (adj[i][j] != (val[i] ^ val[j])) {
                return false;
            }
        }
    }
    return true;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int m;
    cin >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        adj[i].assign(n, 1);
        adj[i][i] = 0;
    }
    while (m--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u][v] = adj[v][u] = 0;
    }
    if (okay(adj, 0, false) || okay(adj, 0, true)) {
        cout << "DA\n";
    } else {
        cout << "NE\n";
    }
}
