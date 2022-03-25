#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <limits.h>
#include <queue>

using namespace std;
void solve () {
    int64_t N; cin >> N;
    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    vector<int> depth;
    depth.assign(N, -1);
    queue<pair<int,int>> q;
    q.push({0, 0});
    while (!q.empty()) {
        pair<int,int> p = q.front();
        q.pop();
        if (depth[p.first] != -1) {
            continue;
        }
        depth[p.first] = p.second;
        for (int i: adj[p.first]) {
            q.push({i, p.second + 1});
        }
    }
    for (int i = 0; i < N; i++) {
        if (depth[i] % 2 == 1) {
            cout << adj[i].size() << ' ';
        } else {
            cout << -(int)adj[i].size() << ' ';
        }
    }
    cout << '\n';
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
