#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <map>
#include <queue>
#include <set>

using namespace std;

struct Edge {
    int w = (int) 1e9, to = -1;

    bool operator<(Edge const &other) const {
        return make_pair(w, to) < make_pair(other.w, other.to);
    }
};

vector<vector<int>> new_adj;

struct tree {
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    vector<int> enter;
    vector<int> exit;
    vector<int> parent;
    int cntr = 1;
    int lg2;

    void dfs(int u, int prev) {
        parent[u] = prev;
        cntr++;
        enter[u] = cntr;
        dp[u][0] = prev;
        for (int i = 1; i <= lg2; i++) {
            dp[u][i] = dp[dp[u][i - 1]][i - 1];
        }
        for (int v: adj[u]) {
            if (v != prev) {
                dfs(v, u);
            }
        }
        cntr++;
        exit[u] = cntr;
    }

    bool isAncestor(int u, int v) {
        //is u an ancestor of v
        return (enter[u] <= enter[v] && exit[u] >= exit[v]);
    }

    vector<int> path(int u, int v) {
        bool swapped = false;
        if (isAncestor(u, v)) {
            swap(u, v);
            swapped = true;
        }
        vector<int> ans = {};
        int x = u;
        while (x != v) {
            ans.push_back(x);
            x = parent[x];
        }
        ans.push_back(v);
        if (swapped) {
            reverse(ans.begin(), ans.end());
        }
        return ans;
    }

    int leastCommonAncestor(int u, int v) {
        if (isAncestor(u, v)) {
            return u;
        }
        if (isAncestor(v, u)) {
            return v;
        }
        for (int i = lg2; i >= 0; i--) {
            if (!isAncestor(dp[u][i], v)) {
                u = dp[u][i];
            }
        }
        return dp[u][0];
    }

    void read(int n) {
        lg2 = ceil(log2(n)) + 1;
        enter.resize(n);
        exit.resize(n);
        adj.resize(n);
        dp.resize(n);
        for (int i = 0; i < n; i++) {
            dp[i].resize(lg2 + 1);
            enter[i] = exit[i] = -1;
        }
        parent = enter;
        dfs(0, 0);
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> adj(n);
    int oc[n];
    for (int i = 0; i < n; i++) oc[i] = 0;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back({1, v}), adj[v].push_back({1, u});
    }
    int total_weight = 0;
    vector<Edge> min_e(n);
    min_e[0].w = 0;
    set<Edge> q;
    q.insert({0, 0});
    vector<bool> selected(n, false);
    new_adj.resize(n);
    for (int i = 0; i < n; ++i) {
        int v = q.begin()->to;
        selected[v] = true;
        total_weight += q.begin()->w;
        q.erase(q.begin());

        if (min_e[v].to != -1) {
            new_adj[v].push_back(min_e[v].to);
            new_adj[min_e[v].to].push_back(v);
        }

        for (Edge e : adj[v]) {
            if (!selected[e.to] && e.w < min_e[e.to].w) {
                q.erase({min_e[e.to].w, e.to});
                min_e[e.to] = {e.w, v};
                q.insert({e.w, e.to});
            }
        }
    }
    tree t;
    t.adj = new_adj;
    t.read(n);
    int Q;
    cin >> Q;
    vector<vector<int>> ans;
    while (Q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        oc[u]++, oc[v]++;
        vector<int> vec1 = t.path(u, t.leastCommonAncestor(u, v));
        vector<int> vec2 = t.path(t.leastCommonAncestor(u, v), v);
        vector<int> vec = vec1;
        vec.pop_back();
        for (int i: vec2) vec.push_back(i);
        ans.push_back(vec);
    }
    int added = 0;
    for (int i = 0; i < n; i++) {
        if (oc[i] % 2 == 1) {
            added++;
        }
    }
    if (added != 0) {
        cout << "NO\n";
        cout << added / 2 << endl;
        return 0;
    }
    cout << "YES\n";
    for (auto v: ans) {
        cout << v.size() << endl;
        for (int i: v) {
            cout << i + 1 << " ";
        }
        cout << endl;
    }
}
