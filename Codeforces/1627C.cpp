#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;

void solve () {
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    vector<int> deg(n);
    vector<pair<int,int>> vec;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u), deg[u]++, deg[v]++;
        vec.emplace_back(u, v);
    }
    for (int i = 0; i < n; i++) {
        if (deg[i] >= 3) {
            cout << "-1\n";
            return;
        }
    }
    map<pair<int,int>,int> myMap;
    queue<pair<pair<int,int>,int>> q;
    q.push({{vec[0].first, vec[0].second}, 0});
    while (!q.empty()) {
        pair<int,int> p = q.front().first;
        int val = q.front().second;
        q.pop();
        if (myMap[p]) {
            continue;
        }
        myMap[{p.first, p.second}] = val + 1, myMap[{p.second, p.first}] = val + 1;
        for (int i: adj[p.first]) {
            if (i == p.second) {
                continue;
            }
            q.push({{p.first, i}, !val});
        }
        for (int j: adj[p.second]) {
            if (j == p.first) {
                continue;
            }
            q.push({{p.second, j}, !val});
        }
    }
    for (auto& p: vec) {
        if (myMap[p] == 1) {
            cout << 2 << ' ';
        } else {
            cout << 5 << ' ';
        }
    }
    cout << '\n';
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
