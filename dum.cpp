#include <bits/stdc++.h>
using namespace std;
class Graph {
    vector<vector<int> > adj;
    vector<vector<int> > new_adj;
    vector<bool> hasVisited;
    vector<pair<int,int> > edges;
    vector<int> parent;
    vector<int> sub;
    vector<int> pre, post;
    int cntr = 0;
    void dfs (int curNode) {
        hasVisited[curNode] = true;
        pre[curNode] = cntr++;
        for (int i: adj[curNode]) {
            if (!hasVisited[i]) {
                new_adj[i].push_back(curNode), new_adj[curNode].push_back(i);
                parent[i] = curNode;
                depth[i] = depth[curNode] + 1;
                dfs (i);
            }
        }
        post[curNode] = cntr++;
    }
public:
vector<int> depth;
    void add_edge (int u, int v) {
        edges.push_back(make_pair(u, v));
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
    bool isAncestor (int u, int v) {
        return (pre[u] <= pre[v] && post[u] >= post[v]);
    }
    vector<pair<int,int> > read() {
        pre.resize((int)adj.size()), post.resize((int)adj.size());
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
        vector<pair<int,int> > roads;
        for (int i = 1; i < (int)adj.size(); i++) {
            if (sub[i] == 0) {
                roads.push_back(make_pair(i, parent[i]));
            }
        }
        return roads;
    }
};
class DisjointSetUnion {
    public: 
    vector<vector<int> > nodes;
    vector<int> parent;
    int find_head (int u) {
        while (u != parent[u]) {
            u = parent[u];
        }
        return u;
    }
    void join (int u, int v) {
        u = find_head(u), v = find_head(v);
        if (u == v) {
            assert(false);
            return;
        }
        if (nodes[u].size() > nodes[v].size()) {
            swap(u, v);
        }
        for (int i: nodes[u]) {
            nodes[v].push_back(i);
        }
        nodes[u].clear();
        parent[u] = v;
    }
    DisjointSetUnion (int n) {
        nodes.resize(n);
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            nodes[i].push_back(i);
            parent[i] = i;
        }
    }
};
int main() {
    int n, m;
    cin >> n >> m;
    Graph gr(n);
    vector<int> deg;
    deg.assign(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        gr.add_edge (u, v);
    }
    vector<pair<int,int> > roads = gr.read();
    DisjointSetUnion dsu(n);
    //set<int> r;
    for (auto& p: roads) {
        dsu.join(p.first, p.second);
        deg[p.first]++, deg[p.second]++;
        //cout << p.first + 1 << " ? " << p.second + 1 << '\n';
        //r.insert(p.first), r.insert(p.second);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (gr.isAncestor(i, j) && dsu.find_head(i) != dsu.find_head(j) && deg[i] && deg[j]) {
                //cout << i + 1 << " <-> " << j + 1 << " " << dsu.find_head(i) + 1 << " " << dsu.find_head(j) + 1 << '\n';
                dsu.join(i, j);
                deg[i]++, deg[j]++;
            }
        }
    }
    int ans = 0;
    for (int i: deg) {
        ans += (i == 1);
    }
    cout << (ans + 1)/2;
}
