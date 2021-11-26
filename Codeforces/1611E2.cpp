#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;

struct Tree {
    vector<vector<int>> adj;
    vector<int> parent;
    vector<vector<int>> binJump;
    vector<int> depth;

    int jump(int curNode, int jump_size) {
        if (jump_size == 0) {
            return curNode;
        }
        int x = log2(jump_size);
        return jump(binJump[curNode][x], jump_size - (1 << x));
    }

    void fill_binJump() {
        binJump.resize(adj.size());
        for (int i = 0; i < binJump.size(); i++) {
            binJump[i].resize(20);
            binJump[i][0] = parent[i];
            if (parent[i] == -1) binJump[i][0] = i;
        }
        for (int j = 1; j < 20; j++) {
            for (int i = 0; i < adj.size(); i++) {
                binJump[i][j] = binJump[binJump[i][j - 1]][j - 1];
            }
        }
    }

    void fill_parent() {
        depth.assign(adj.size(), false);
        queue<pair<int, int>> q;
        q.push({0, 0});
        vector<bool> hasVisited;
        hasVisited.assign(adj.size(), false);
        hasVisited[0] = true;
        parent.assign(adj.size(), false);
        while (!q.empty()) {
            int node = q.front().first;
            int dist = q.front().second;
            depth[node] = dist;
            q.pop();
            for (int i: adj[node]) {
                if (!hasVisited[i]) {
                    q.push({i, dist + 1});
                    hasVisited[i] = true;
                    parent[i] = node;
                }
            }
        }
    }
};

struct eulerTour {
    vector<vector<int>> adj;
    vector<int> euler, first;

    void pre_euler() {
        first.resize(adj.size());
        dfs(0, -1, 0);
    }

    void dfs(int node, int parent, int h) {
        euler.push_back(node);
        first[node] = euler.size();
        for (int i: adj[node]) {
            if (i != parent) {
                dfs(i, node, h + 1);
            }
        }
        euler.push_back(node);
    }
};

struct segmentTreePoint {
    vector<ll> v;
    vector<ll> vec;
    vector<ll> addLater;

    void upd(int dum, int tl, int tr, int &l, int &r, ll val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            return;
        }
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        upd(dum, tl, mid, l, r, val);
        upd(dum + 1, mid + 1, tr, l, r, val);
    }

    void upd(int l, int r, int val) {
        upd(1, 0, v.size() - 1, l, r, val);
    }

    ll get(int x) {
        int cur = x + v.size();
        ll ans = 0;
        while (true) {
            ans += addLater[cur];
            if (cur == 0) {
                break;
            }
            cur /= 2;
        }
        return ans;
    }

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        vec.resize(v.size() * 2);
        addLater.resize(v.size() * 2);
    }

};

void solve() {
    int N, K;
    cin >> N >> K;
    vector<int> x(K);
    for (int i = 0; i < K; i++) {
        cin >> x[i];
        x[i]--;
    }
    Tree t;
    t.adj.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.adj[u].push_back(v), t.adj[v].push_back(u);
    }
    t.fill_parent();
    t.fill_binJump();
    for (int i = 0; i < K; i++) {
        x[i] = t.jump(x[i], (t.depth[x[i]]) / 2);
    }
    set<int> s;
    for (int i: x) {
        s.insert(i);
    }
    x.clear();
    for (int i: s) {
        x.push_back(i);
    }
    K = x.size();
    eulerTour et;
    et.adj = t.adj;
    et.pre_euler();
    segmentTreePoint stp;
    stp.resz(2 * N + 2);
    vector<int> first(N), last(N);
    for (int i = 0; i < N; i++) {
        first[i] = last[i] = -1;
    }
    for (int i = 0; i < et.euler.size(); i++) {
        if (first[et.euler[i]] == -1) first[et.euler[i]] = i;
        else last[et.euler[i]] = i;
    }
    for (int i = 0; i < x.size(); i++) {
        stp.upd(first[x[i]], last[x[i]], 1);
    }
    for (int i = 1; i < t.adj.size(); i++) {
        if (t.adj[i].size() == 1) {
            if (stp.get(first[i]) == 0) {
                cout << "-1\n";
                return;
            }
        }
    }
    int cntr = 0;
    for (int i = 0; i < x.size(); i++) {
        if (stp.get(first[x[i]]) == 1) {
            cntr++;
        }
    }
    cout << cntr << '\n';
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
