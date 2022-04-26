#include <iostream>
#include <vector>
 
using namespace std;
 
class Graph {
    vector<vector<int>> adj;
    vector<vector<int>> new_adj;
    vector<bool> hasVisited;
    vector<pair<int,int>> edges;
    vector<int> parent;
    vector<int> sub;
    vector<int> depth;
    void dfs (int curNode) {
        hasVisited[curNode] = true;
        for (int i: adj[curNode]) {
            if (!hasVisited[i]) {
                new_adj[i].push_back(curNode), new_adj[curNode].push_back(i);
                parent[i] = curNode;
                depth[i] = depth[curNode] + 1;
                dfs (i);
            }
        }
    }
public:
    void add_edge (int u, int v) {
        edges.emplace_back(u, v);
        adj[u].push_back(v), adj[v].push_back(u);
    }
    Graph (int n) {
        new_adj.resize(n), adj.resize(n), hasVisited.assign(n, false), parent.assign(n, -1), sub.resize(n), depth.resize(n);
    }
    void fill (int curNode, int prevNode) {
        for (int i: new_adj[curNode]) {
            if (i != prevNode) {
                fill (i, curNode);
                sub[curNode] += sub[i];
            }
        }
    }
    void read() {
        depth[0] = 0;
        dfs (0); 
        for (auto& p: edges) {
            if (parent[p.first] == p.second || parent[p.second] == p.first) {
                continue;
            }
            if (depth[p.first] > depth[p.second]) {
                swap(p.first, p.second);
            }
            sub[p.first] += -1;
            sub[p.second] += 1;
        }
        fill (0, 0);
        vector<pair<int,int>> roads;
        for (int i = 1; i < (int)adj.size(); i++) {
            if (sub[i] == 0) {
                roads.emplace_back(i + 1, parent[i] + 1);
            }
        }
        cout << roads.size() << '\n';
        for (auto& p: roads) {
            cout << p.first << " " << p.second << '\n';
        }
    }
};
 
int main() {
    int n, m;
    cin >> n >> m;
    Graph gr(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        gr.add_edge(u - 1, v - 1);
    }
    gr.read();
}
