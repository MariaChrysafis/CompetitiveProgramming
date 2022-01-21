#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;
vector<pair<int, int>> vec;
vector<bool> hv;
vector<vector<int>> adj;
vector<int> path;

void euler (int curNode) {
    hv[curNode] = true;
    for (int i = 0; i < adj.size(); i++) {
        if (adj[curNode][i]) {
            adj[curNode][i]--, adj[i][curNode]--;
            euler(i);
        }
    }
    path.push_back(curNode);
}

void solve() {
    hv.clear();
    vec.clear();
    int N, M;
    cin >> N >> M;
    vector<int> deg;
    deg.assign(N + 1, 0);
    adj.resize(N + 1);
    for (int i = 0; i <= N; i++) {
        adj[i].assign(N + 1, 0);
    }
    hv.assign(N, false);
    while (M--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u][v]++, adj[v][u]++;
        deg[u]++, deg[v]++;
    }
    vector<int> take_care;
    for (int i = 0; i < N; i++) {
        if (deg[i] % 2 == 1) {
            take_care.push_back(i);
        }
    }
    for (int i = 0; i < take_care.size(); i++) {
        adj[N][take_care[i]]++, adj[take_care[i]][N]++;
    }
    for (int i = 0; i < N; i++) {
        if (!hv[i]) {
            euler(i);
            for (int j = 0; j < path.size() - 1; j++) {
                vec.emplace_back(path[j], path[j + 1]);
            }
            path.clear();
        }
    }
    cout << N - take_care.size() << '\n';
    for (auto& p: vec) {
        if (p.first == N || p.second == N) continue;
        cout << p.first + 1 << " " << p.second + 1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}
