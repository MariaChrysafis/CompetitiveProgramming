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
class Graph {
public:
    Graph (int N) {
        adj.resize(N);
    }
    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
    void dfs (int curNode) {
        assert(col[curNode] != -1);
        for (int i: adj[curNode]) {
            if (col[i] == -1) {
                col[i] = !col[curNode];
//                cout << "COLOR " << i << " " << !col[curNode] << '\n';
                dfs (i);
            } else if (col[i] == col[curNode]) {
                cout << "NO\n";
                exit(0);
            }
        }
    }
    void color () {
        col.assign(adj.size(), -1);
        for (int i = 0; i < adj.size(); i++)  {
            if (col[i] == -1) {
//                cout << "COLORF " << i << " " << col[i] << '\n';
                col[i] = 0;
                dfs (i);
            }
        }
    }
    vector<vector<int>> adj;
    vector<int> col;
};
class Topo {
public:
    Topo (int n) {
        adj.resize(n);
        deg.resize(n);
    }
    void add_edge (int u, int v) {
        deg[v]++;
        adj[u].push_back(v);
    }
    vector<int> tsort () {
        queue<int> q;
        for (int i = 0; i < deg.size(); i++) {
            if (deg[i] == 0) {
                q.push(i);
            }
        }
        vector<int> v;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            v.push_back(x);
            for (int i: adj[x]) {
                deg[i]--;
                if (deg[i] == 0) {
                    q.push(i);
                }
            }
        }
        //reverse(v.begin(), v.end());
        if (v.size() != deg.size()) {
            //cout << "YES\n";
            cout << "NO\n";
            exit(0);
        }
        return v;
    }
    vector<vector<int>> adj;
    vector<int> deg;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    Graph g(N);
    Topo ts(N);
    vector<pair<int,int>> to_add, to_add1;
    for (int i = 0; i < M; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        x--, y--;
        if (t == 2) {
            g.add_edge(x, y);
            to_add.emplace_back(x, y);
        } else if (t == 1) {
            g.add_edge(x, y);
            to_add1.emplace_back(x, y);
        }
    }
    g.color();
    for (auto& p: to_add) {
        if (g.col[p.first] != g.col[p.second]) {
            //cout << "YE\n";
            if (g.col[p.first] == 1) {
//                cout << p.first << "->" << p.second << '\n';
                ts.add_edge(p.first, p.second);
            } else {
//                cout << p.second << "->" << p.first << '\n';
                ts.add_edge(p.second, p.first);
            }
        }
    }
    for (auto& p: to_add1) {
        if (g.col[p.first] != g.col[p.second]) {
            //cout << "YE\n";
            if (g.col[p.first] == 0) {
//                cout << p.first << "->" << p.second << '\n';
                ts.add_edge(p.first, p.second);
            } else {
//                cout << p.second << "->" << p.first << '\n';
                ts.add_edge(p.second, p.first);
            }
        }
    }
    vector<int> v = ts.tsort();
    for (int i: v) {
        //cout << i << ' ';
    }
    cout << '\n';
    int id[N];
    for (int i = 0; i < v.size(); i++) {
        id[v[i]] = i;
    }
    cout << "YES\n";
    for (int i = 0; i < N; i++) {
        if (g.col[i] == 0) {
            cout << "L ";
        } else {
            cout << "R ";
        }
        cout << id[i] << '\n';
    }
}
