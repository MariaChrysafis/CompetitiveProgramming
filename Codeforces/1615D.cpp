#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>
#include <iomanip>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;
typedef long long ll;
struct DSU {
    vector<int> parent;
    vector<int> compSize;
    int n;
    void fill(){
        parent.resize(n), compSize.resize(n);
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
struct Graph {
    vector<vector<int>> adj;
    vector<bool> color, hasVisited;
    bool fine = true;
    void dfs (int curNode) {
        hasVisited[curNode] = true;
        for (int i: adj[curNode]) {
            if (!hasVisited[i]) {
                color[i] = !color[curNode];
                dfs(i);
            } else {
                if (color[i] == color[curNode]) {
                    fine = false;
                }
            }
        }
    }
    void read () {
        int n = adj.size();
        color.resize(n), hasVisited.assign(n, false);
        for (int i = 0; i < n; i++) {
            if (!hasVisited[i] && !adj[i].empty()) {
                color[i] = false;
                dfs (i);
            }
        }
    }
};
struct Tree {
    vector<vector<int>> adj;
    vector<int> parent;
    void dfs (int curNode, int prevNode) {
        parent[curNode] = prevNode;;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs(i, curNode);
            }
        }
    }
};
struct Query {
    int x;
    int y;
    bool val;
};
void solve () {
    int N, M;
    cin >> N >> M;
    DSU d;
    d.n = N;
    d.fill();
    vector<Query> vec;
    Tree myTree;
    myTree.adj.resize(N);
    map<pair<int,int>,int> weight;
    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        myTree.adj[u].push_back(v), myTree.adj[v].push_back(u);
        if (w == -1) {
            continue;
        }
        weight[{u, v}] = weight[{v, u}] = w;
        //cout << u << " " < v << " " << w << '\n';
        w = (__builtin_popcount(w)) % 2;
        if (w) {
            vec.push_back({u, v, (bool) w});
        } else {
            //cout << u << " ? " << v << '\n';
            d.join(u, v);
        }
    }
    for (int i = 0; i < M; i++) {
        int u, v, p;
        cin >> u >> v >> p;
        u--, v--;
        if (p) {
            vec.push_back({u, v, (bool) p});
        } else {
            //cout << u + 1 << " ? " << v + 1 << '\n';
            d.join(u, v);
        }
    }
    Graph g;
    g.adj.resize(N);
    for (auto& query: vec) {
        if (query.val) {
            //cout << query.x + 1 << " " << query.y + 1 << '\n';
            query.x = d.find_head(query.x);
            query.y = d.find_head(query.y);
            g.adj[query.x].push_back(query.y);
            g.adj[query.y].push_back(query.x);
            //cout << query.x + 1 << " " << query.y + 1 << '\n';
            //cout << '\n';
        }
    }
    g.read();
    if (!g.fine) {
        cout << "NO\n";
        return;
    }
    myTree.parent.resize(N);
    myTree.dfs(0, -1);
    cout << "YES\n";
    for (int i = 0; i < myTree.adj.size(); i++) {
        for (int j: myTree.adj[i]) {
            if (myTree.parent[i] == j) {
                if (!weight[{i, j}]) {
                    cout << i + 1 << " " << j + 1 << " " << (g.color[d.find_head(i)] ^ g.color[d.find_head(j)]) << '\n';
                } else {
                    cout << i + 1 << " " << j + 1 << " " << weight[{i, j}] << '\n';
                }
            }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
