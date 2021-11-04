#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <set>
#include <algorithm>
#include <iomanip>
 
using namespace std;
vector<vector<int>> adj;
vector<short int> color;
vector<int> parent;
int st, en;
 
bool dfs(int v) {
    color[v] = 1;
    for (int u : adj[v]) {
        if (color[u] == 0) {
            parent[u] = v;
            if (dfs(u)) {
                return true;
            }
        } else if (color[u] == 1) {
            en = v, st = u;
            return true;
        }
    }
    color[v] = 2;
    return false;
}
 
void find_cycle() {
    int n = adj.size();
    color.assign(n, 0);
    parent.assign(n, -1);
    st = -1;
    for (int v = 0; v < n; v++) {
        if (color[v] == 0 && dfs(v)) {
            break;
        }
    }
    vector<int> cycle;
    cycle.push_back(st);
    for (int v = en; v != st; v = parent[v]) {
        cycle.push_back(v);
    }
    cycle.push_back(st);
    reverse(cycle.begin(), cycle.end());
    cout << cycle.size() << endl;
    for (int v : cycle)
        cout << v + 1 << " ";
    cout << endl;
}
 
int main() {
    int n, m;
    cin >> n >> m;
    adj.resize(n);
    vector<int> inDeg(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        inDeg[v]++;
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (!inDeg[i]) {
            q.push(i);
        }
    }
    vector<int> v;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i: adj[x]) {
            inDeg[i]--;
            if (!inDeg[i]) {
                q.push(i);
            }
        }
        v.push_back(x);
    }
    if (v.size() == n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    find_cycle();
 
}
