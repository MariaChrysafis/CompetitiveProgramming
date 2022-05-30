#include <bits/stdc++.h>

#pragma GCC optimize("O2")
#pragma GCC optimize("avx2")

using namespace std;

using namespace std;template<class T>
class SegmentTree {
public:

    SegmentTree (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, ID);
    }

    void update (int x, T y) {
        x += N - 1;
        val[x] = y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
        }
    }

    T query (int ind, const int l, const int r, int tl, int tr) {
        if (tl >= l && tr <= r) {
            return val[ind];
        }
        if (tr < l || tl > r) {
            return ID;
        }
        return merge(query(2 * ind + 1, l, r, tl, (tl + tr)/2), query(2 * ind + 2, l, r, (tl + tr)/2 + 1, tr));
    }

    T query (int l, int r) {
        return val[0];
    }
private:
    vector<T> val;
    T ID = INT_MAX;
    T merge (T x, T y) {
        return min(x, y);
    }
    int N;
};
struct DisjointSetUnion {
    vector<int> parent, sz;
    void resz (int n) {
        parent.resize(n), sz.assign(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    int find_head (int u) {
        int x = u;
        while (u != parent[u]) {
            u = parent[u];
        }
        return (parent[x] = u);
    }
    bool join (int u, int v) {
        u = find_head(u), v = find_head(v);
        if (u == v) {
            return false;
        }
        if (sz[u] > sz[v]) {
            swap(u, v);
        }
        sz[v] += sz[u], parent[u] = v;
        return true;
    }
};
vector<pair<int,int> >adj[200000]; //(weight, node)
int parent[200000];
int w[200000];
map<pair<int,int>,int> weight;
void dfs (int curNode, int prevNode) {
    parent[curNode] = prevNode;
    w[curNode] = weight[make_pair(curNode, prevNode)];
    for (auto& p: adj[curNode]) {
        if (p.second != prevNode) {
            dfs (p.second, curNode);
        }
    }
}
int colors[200000];
map<int,set<int>> myMap[200000];
set<int> rgb[200000];
int main () {
    freopen("grass.in", "r", stdin);
    freopen("grass.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, K, Q;
    cin >> N >> M >> K >> Q;
    vector<pair<int,pair<int,int> > > edges;
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        edges.push_back(make_pair(w, make_pair(u, v)));
    }
    sort(edges.begin(), edges.end());
    int actual[edges.size()];
    for (int i = 0; i < edges.size(); i++) {
        actual[i] = edges[i].first;
        weight[make_pair(edges[i].second.first, edges[i].second.second)] = weight[make_pair(edges[i].second.second, edges[i].second.first)] = i;
        edges[i].first = i;
    }
    DisjointSetUnion dsu;
    dsu.resz(N);
    SegmentTree<int> st(N + 1);
    for (auto& p: edges) {
        if (dsu.join(p.second.first, p.second.second)) {
            adj[p.second.first].push_back(make_pair(p.first, p.second.second));
            adj[p.second.second].push_back(make_pair(p.first, p.second.first));
        }
    }
    dfs (0, 0);
    for (int i = 0; i < N; i++) {
        cin >> colors[i];
    }
    for (int i = 0; i < N; i++) {
        for (auto& p: adj[i]) {
            if (p.second == parent[i]) {
                continue;
            }
            myMap[i][colors[p.second]].insert(p.first);
        }
    }
    for (int i = 0; i < N; i++) {
        for (auto& p: myMap[i]) {
            if (p.first != colors[i]) {
                rgb[i].insert(*p.second.begin());
            }
        }
    }
    for (int i = 0; i < N; i++) {
        if (!rgb[i].empty()) {
            st.update(i, *rgb[i].begin());
        }
    }
    while (Q--) {
        int u, c;
        cin >> u >> c;
        u--;
        if (u != 0) {
            if (!rgb[parent[u]].empty()) {
                st.update(parent[u], INT_MAX);
            }
            if (colors[parent[u]] != colors[u]) {
                rgb[parent[u]].erase(*myMap[parent[u]][colors[u]].begin());
            }
            if (c != colors[parent[u]] && !myMap[parent[u]][c].empty()) {
                rgb[parent[u]].erase(*myMap[parent[u]][c].begin());
            }
            myMap[parent[u]][colors[u]].erase(w[u]);
            myMap[parent[u]][c].insert(w[u]);
            if (colors[u] != colors[parent[u]] && !myMap[parent[u]][colors[u]].empty()) {
                rgb[parent[u]].insert(*myMap[parent[u]][colors[u]].begin());
            }
            if (c != colors[parent[u]]) {
                rgb[parent[u]].insert(*myMap[parent[u]][c].begin());
            }
            if (!rgb[parent[u]].empty()) {
                st.update(parent[u], *rgb[parent[u]].begin());
            }
        }
        if (!rgb[u].empty()) {
            st.update(u, INT_MAX);
        }
        if (!myMap[u][c].empty()) {
            rgb[u].erase(*myMap[u][c].begin());
        }
        if (!myMap[u][colors[u]].empty()) {
            rgb[u].insert(*myMap[u][colors[u]].begin());
        }
        if (!rgb[u].empty()) {
            st.update(u, *rgb[u].begin());
        }
        colors[u] = c;
        cout << actual[st.query(0, N - 1)] << '\n';
    }
}
