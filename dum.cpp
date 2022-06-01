#include <bits/stdc++.h>
 
using namespace std;

struct dsu{
    vector<int> parent;
    vector<int> compSize;
    int n;
    int cc;
    void fill(){
        parent.resize(n), compSize.resize(n);
        cc = n - 1;
        for(int i = 0; i < n; i++){
            parent[i] = i, compSize[i] = 1;
        }
    }
    int find_head(int x){
        if(x == parent[x]){
            return x;
        }
        return find_head(parent[x]);
    }
    void join(int x, int y){
        x = find_head(x);
        y = find_head(y);
        if(x == y){
            return;
        }
        cc--;
        if(compSize[x] > compSize[y]){
            swap(x,y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x]; 
    }
    bool comp(int x, int y){
        return (find_head(x) == find_head(y));
    }
};

class Graph {
    vector<vector<int> > adj;
    vector<vector<int> > new_adj;
    vector<bool> hasVisited;
    vector<pair<int,int> > edges;
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
        dsu ds;
        ds.n = (int)adj.size();
        ds.fill();
        vector<pair<int,int> > roads;
        vector<int> deg;
        deg.assign(adj.size(), 0);
        for (int i = 1; i < (int)adj.size(); i++) {
            if (sub[i] == 0) {
                roads.push_back(make_pair(i, parent[i]));
                deg[roads.back().first]++, deg[roads.back().second]++;
            }
        }
        for (auto& p: roads) {
            ds.join(p.first, p.second);
        }
        vector<int> cnt; cnt.assign(adj.size(), 0);
        for (int i = 0; i < adj.size(); i++) {
            if (deg[i] == 1) {
                cnt[ds.find_head(i)]++;
            }
        }
        int ans = 0;
        for (int i: cnt) {
            ans += i;
        }
        for (int i: deg) {
            if (i == 0) {
                ds.cc--;
            }
        }
        cout << (ans - ds.cc + 1)/2 << '\n';
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
