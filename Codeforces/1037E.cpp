#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

typedef int64_t ll;
vector<set<int>> adj;
set<pair<int,int>> edges;
vector<int> deg;

void add (int u, int v) {
    adj[u].insert(v);
    adj[v].insert(u);
    edges.insert({u, v});
    edges.insert({v, u});
    deg[u]++;
    deg[v]++;
}

void remove (int u, int v) {
    if (edges.count({u, v})) {
        edges.erase({u, v});
        assert(edges.count({v, u}));
        edges.erase({v, u});
        assert(adj[u].count(v));
        adj[u].erase(v);
        assert(adj[v].count(u));
        adj[v].erase(u);
        deg[u]--;
        deg[v]--;
        assert(deg[u] >= 0 && deg[v] >= 0);
    }
}

void remove (int u) {
    set<int> s = adj[u];
    for (int i: s) {
        remove(u, i);
    }
}

queue<int> q;
vector<bool> hasVisited;
int cur;

void update_queue (int K) {
    while (!q.empty()) {
        int x = q.front();
        //cout << "REMOVE " << x << '\n';
        q.pop();
        if (hasVisited[x]) {
            continue;
        }
        cur--;
        set<int> s = adj[x];
        remove(x);
        hasVisited[x] = true;
        for (int i: s) {
            if (deg[i] < K) {
                q.push(i);
            }
        }
    }
}

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    adj.resize(N);
    deg.assign(N, 0);
    vector<pair<int,int>> inp;
    while (M--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        add(u, v);
        inp.emplace_back(u, v);
    }
    hasVisited.assign(N, false);
    for (int i = 0; i < N; i++) {
        if (deg[i] < K) {
            q.push(i);
        }
    }
    cur = N;
    update_queue(K);
    reverse(inp.begin(), inp.end());
    vector<int> ans;
    for (auto& p: inp) {
        ans.push_back(cur);
        remove(p.first, p.second);
        if (deg[p.first] < K) {
            q.push(p.first);
        }
        if (deg[p.second] < K) {
            q.push(p.second);
        }
        update_queue(K);
        //cout << cur << '\n';
    }
    reverse(ans.begin(), ans.end());
    for (int i: ans) {
        cout << i << '\n';
    }
}
