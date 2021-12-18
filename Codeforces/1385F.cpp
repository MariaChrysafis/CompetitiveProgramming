#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")

typedef long long ll;

using namespace std;

void solve () {
    int n, k;
    cin >> n >> k;
    vector<set<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].insert(v), adj[v].insert(u);
    }
    vector<int> leaves, deg; vector<bool> leaf;
    leaves.assign(n, 0), deg.assign(n, 0), leaf.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j: adj[i]) {
            leaves[i] += (adj[j].size() == 1);
        }
        leaf[i] = (adj[i].size() == 1);
        deg[i] = adj[i].size();
    }
    set<pair<int,int>> s;
    for (int i = 0; i < n; i++) {
        s.insert({leaves[i], i});
    }
    int ans = 0;
    while (!s.empty()) {
        auto it = s.end(); it--;
        int curNode = (*it).second;
        s.erase({leaves[curNode], curNode});
        leaves[curNode] -= k;
        if (leaves[curNode] < 0) {
            break;
        }
        ans++;
        deg[curNode] -= k;
        int cntr = 0;
        auto curIt = adj[curNode].begin();
        vector<int> to_erase;
        while (cntr != k) {
            int newNode = *curIt;
            if (deg[newNode] == 1) {
                deg[newNode]--;
                s.erase({leaves[newNode], newNode});
                to_erase.push_back(newNode);
                cntr++;
            }
            curIt++;
        }
        for (int i: to_erase) {
            adj[curNode].erase(i);
        }
        if (deg[curNode] == 1) {
            int nxt = (*adj[curNode].begin());
            s.erase({leaves[nxt], nxt});
            leaves[nxt]++;
            s.insert({leaves[nxt], nxt});
        }
        s.insert({leaves[curNode], curNode});
    }
    cout << ans << '\n';
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
