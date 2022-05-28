#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include <set>

using namespace std;

const int MOD = 1e9 + 7;

struct DisjointSetUnion {
    vector<int> parent, sz;

    void resz(int n) {
        parent.resize(n), sz.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i, sz[i] = 1;
        }
    }

    int find_head(int x) {
        while (parent[x] != x) {
            x = parent[x];
        }
        return x;
    }

    void join(int u, int v) {
        u = find_head(u), v = find_head(v);
        if (u == v) {
            return;
        }
        if (sz[u] > sz[v]) {
            swap(u, v);
        }
        sz[v] += sz[u], parent[u] = v;
    }
};

vector<bool> hasVisited;

long long dfs (vector<vector<int>>& adj, int curNode) {
    if (hasVisited[curNode]) return 1;
    hasVisited[curNode] = true;
    long long prod = 1;
    for (int i: adj[curNode]) {
        prod *= dfs (adj, i);
        prod %= MOD;
    }
    return (prod + 1) % MOD;
}

int main() {
    freopen("cave.in", "r", stdin);
    freopen("cave.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    hasVisited.resize(n * m);
    vector<string> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<vector<pair<int, int>>> vec(n);
    for (int i = 0; i < n - 1; i++) {
        int l = 1;
        int r = -1;
        for (int j = 1; j < m; j++) {
            if (arr[i][j] == '#') {
                if (l <= r && arr[i][j - 1] == '.') {
                    vec[i].push_back(make_pair(l, r));
                }
            } else {
                if (arr[i][j - 1] == '#') {
                    l = j;
                }
                r = j;
            }
        }
    }
    DisjointSetUnion dsu, dsu1;
    dsu.resz(n * m), dsu1.resz(n * m);
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == '.') {
                for (int dx = 0; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 0; dy++) {
                        if (abs(dx) + abs(dy) == 1 && i + dx >= 0 && i + dx < n && j + dy >= 0 && j + dy < m && arr[i + dx][j + dy] == '.') {
                            dsu.join(m * i + j, m * (i + dx) + j + dy);
                        }
                    }
                }
            }
        }
        for (int j = 0; j < vec[i].size(); j++) {
            for (int k = j + 1; k < vec[i].size(); k++) {
                if (dsu.find_head(i * m + vec[i][j].first) == dsu.find_head(i * m + vec[i][k].first)) {
                    dsu1.join(i * m + vec[i][j].first,i * m + vec[i][k].first );
                }
            }
        }
    }
    vector<vector<int>> adj(n * m);
    for (int i = 1; i < vec.size(); i++) {
        for (auto &p: vec[i]) {
            for (auto &q: vec[i - 1]) {
                if (p.first <= q.second && p.second >= q.first) {
                    adj[dsu1.find_head((i - 1) * m + q.first)].push_back(dsu1.find_head(i * m + p.first));
                }
            }
        }
    }
    long long ans = 1;
    for (int i = 0; i < n; i++) {
        for (auto& p: vec[i]) {
            if (dsu.sz[dsu.find_head(m * i + p.first)] == p.second - p.first + 1) {
                ans *= 2;
                ans %= MOD;
            }
        }
    }
    for (int i = 0; i < n * m; i++) {
        if (!hasVisited[i] && !adj[i].empty()) {
            ans *= dfs(adj, i);
            ans %= MOD;
        }
    }
    cout << ans;
}
