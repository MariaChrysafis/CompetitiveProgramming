#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <set>
#include <chrono>

#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>

#pragma GCC optimize("O3")
using namespace std;
struct Graph {
    vector<vector<int>> adj;
    map<pair<int,int>,bool> myMap;
    vector<bool> col;
    vector<bool> hasVisited;
    int red = 0;
    int blue = 0;
    void dfs(int cur, int color) {
        red += color;
        blue += !color;
        col[cur] = color;
        hasVisited[cur] = true;
        for (int i: adj[cur]) {
            if(hasVisited[i]) {
                continue;
            }
            if(myMap.count({cur, i})) {
                dfs(i, myMap[{cur, i}] ^ col[cur]);
            } else if (myMap.count({i, cur})) {
                dfs(i, myMap[{i, cur}] ^ col[cur]);
            }
        }
    }
};
void solve() {
    Graph g;
    int n, m;
    cin >> n >> m;
    g.adj.resize(n);
    g.col.resize(n);
    g.hasVisited.resize(n);
    for (int i = 0; i < n; i++) {
        g.hasVisited[i] = false;
    }
    bool fine = true;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        string s;
        cin >> s;
        g.adj[a].push_back(b);
        g.adj[b].push_back(a);
        if(g.myMap.count({a, b}) && g.myMap[{a,b}] != (s == "imposter")) {
            fine = false;
        }
        g.myMap[{a,b}] = (s == "imposter");
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if(g.hasVisited[i]) {
            continue;
        }
        g.red = g.blue = 0;
        g.dfs(i, 0);
        ans += max(g.red, g.blue);
    }
    for (int i = 0; i < n; i++) {
        for (int j: g.adj[i]) {
            if (g.myMap.count({i, j})) {
                if ((g.col[i] ^ g.col[j]) != g.myMap[{i, j}]) {
                    fine = false;
                }
            }
        }
    }
    if(!fine) {
        cout << -1 << endl;
        return;
    }
    cout << ans << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
