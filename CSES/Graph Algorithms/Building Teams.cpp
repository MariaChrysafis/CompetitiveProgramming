#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <complex>
#include <cmath>
#include <set>
using namespace std;
class Graph {
public:
    vector<vector<int>> adj;
    vector<int> color;
    Graph (int n) {
       adj.resize(n), color.assign(n, -1);
    }
    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
    void dfs (int curNode) {
        for (int i: adj[curNode]) {
            if (color[i] == color[curNode]) {
                cout << "IMPOSSIBLE\n";
                exit(0);
            }
            if (color[i] != -1) continue;
            color[i] = !color[curNode];
            dfs(i);
        }
    }
    void read () {
        for (int i = 0; i < adj.size(); i++) {
            if (color[i] == -1) {
                color[i] = 0;
                dfs(i);
            }
        }
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M; cin >> N >> M;
    Graph gr(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        gr.add_edge(u, v);
    }
    gr.read();
    for (int i = 0; i < gr.color.size(); i++) {
        cout << gr.color[i] + 1 << ' ';
    }
}
