#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long ll;
using namespace std;

set<int> adj[200000];

int n, m;

vector<vector<int>> cc;
set<int> s;

void dfs (int curNode) {
    cc.back().push_back(curNode);
    s.erase(curNode);
    int prev = -1;
    while (true) {
        auto it = s.upper_bound(prev);
        if (it == s.end()) {
            break;
        }
        prev = *it;
        if (!adj[curNode].count(prev)) {
            dfs(prev);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    vector<pair<int,int>> vec(m);
    for (int i = 0; i < m; i++) {
        cin >> vec[i].first >> vec[i].second;
        adj[vec[i].first - 1].insert(vec[i].second - 1);
        adj[vec[i].second - 1].insert(vec[i].first - 1);
    }
    for (int i = 0; i < n; i++) {
        s.insert(i);
    }
    for (int i = 0; i < n; i++) {
        if (s.count(i)) {
            cc.emplace_back();
            dfs (i);
        }
    }
    vector<int> sz;
    for (auto & v: cc) {
        sz.push_back(v.size());
    }
    sort(sz.begin(), sz.end());
    cout << sz.size() << '\n';
    for (int i: sz) {
        cout << i << ' ';
    }
}
