#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <bitset>
#include <stack>
#include <cstdlib>
#include <queue>
#include <stdint.h>
#include <vector>
#include <cassert>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <limits.h>
 
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
 
using namespace std;
 
struct Domino {
    pair<int, int> from, to;
    int64_t cost;
 
    bool operator<(const Domino &d1) const {
        if (this->cost != d1.cost) return (this->cost > d1.cost);
        if (this->from != d1.from) return (this->from < d1.from);
        if (this->to != d1.to) return (this->to < d1.to);
        return false;
    }
};
 
class Graph {
public:
    vector<int64_t> weight;
    vector<vector<int>> adj;
    vector<int> dp;
 
    void add_edge(int u, int v) {
        adj[u][v] = adj[v][u] = 1;
    }
 
    Graph(int n) {
        adj.resize(n);
        for (int i = 0; i < n; i++) {
            adj[i].assign(n, 0);
        }
    }
 
    void solve(int k, bool b) {
        dp.assign((1 << (int) adj.size()), 0);
        for (int i = 1; i < dp.size(); i++) {
            if (__builtin_popcount(i) > k) {
                continue;
            }
            if (__builtin_popcount(i) == 1) {
                dp[i] = weight[log2(i)];
                continue;
            }
            int mx = log2(i);
            int mn = log2(i & -i);
            if (!adj[mx][mn] || !dp[i - (1 << mx)] || !dp[i - (1 << mn)]) {
                continue;
            }
            dp[i] = dp[i - (1 << (int)log2(i))] + weight[(int)log2(i)];
        }
        if (b) return;
        for (int i = 1; i < dp.size(); i++) {
            int x = i;
            while (x != 0) {
                dp[i] = max(dp[i], dp[i - (1 << __builtin_ctzll(x))]);
                x = x & (x - 1);
            }
        }
    }
};
 
int main() {
    //freopen("balancing.in", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    scanf("%d%d", &n, &m);
    int64_t grid[n][n];
    int64_t sm = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lld", &grid[i][j]);
            sm += grid[i][j];
        }
    }
    vector<Domino> dominoes;
    vector<pair<int, int>> pos;
    pos.emplace_back(1, 0);
    pos.emplace_back(0, 1);
    for (int i = 0; i < n; i++) {
        for (auto &p: pos) {
            if (i + p.first < 0 || i + p.first == n) continue;
            for (int j = 0; j < n; j++) {
                if (j + p.second < 0 || j + p.second == n) continue;
                dominoes.push_back({{i, j}, {i + p.first, j + p.second}, grid[i][j] + grid[i + p.first][j + p.second]});
            }
        }
        nth_element(dominoes.begin(), dominoes.begin() + max(7 * (m - 1) + 1, 7), dominoes.end());
        while (dominoes.size() > max(7 * (m - 1) + 1, 7)) {
            dominoes.pop_back();
        }
    }
    vector<pair<int64_t, pair<Domino, Domino>>> edges;
    for (auto &d1: dominoes) {
        for (auto &d2: dominoes) {
            set<pair<int, int>> s;
            s.insert(d1.from), s.insert(d1.to), s.insert(d2.from), s.insert(d2.to);
            if (s.size() != 4) continue;
            edges.push_back({d1.cost + d2.cost, {d1, d2}});
        }
    }
    set<Domino> mySet;
    for (auto &p: edges) {
        mySet.insert(p.second.first), mySet.insert(p.second.second);
    }
    map<Domino, int> myMap;
    int cntr = 0;
    vector<int64_t> weights;
    for (Domino d: mySet) {
        weights.push_back(d.cost);
        myMap[d] = cntr++;
    }
    int sz = floor((double)cntr/(double)1.8);
    Graph gr(cntr), gr1(sz), gr2(cntr - sz);
    gr.weight = weights;
    for (int i = 0; i < sz; i++) gr1.weight.push_back(weights[i]);
    for (int i = sz; i < cntr; i++) gr2.weight.push_back(weights[i]);
    for (auto &e: edges) {
        gr.add_edge(myMap[e.second.first], myMap[e.second.second]);
        if (myMap[e.second.first] < sz && myMap[e.second.second] < sz)
            gr1.add_edge(myMap[e.second.second], myMap[e.second.first]);
        if (myMap[e.second.first] >= sz && myMap[e.second.second] >= sz)
            gr2.add_edge(myMap[e.second.second] - sz, myMap[e.second.first] - sz);
 
    }
    int64_t myMax = 0;
    vector<int> cnt[m + 1];
    for (int i = 1; i < (1 << gr1.adj.size()); i++) {
        if (__builtin_popcount(i) <= m) {
            cnt[__builtin_popcount(i)].push_back(i);
        }
    }
    for (int pc = 1; pc <= m; pc++) {
        gr2.solve(m - pc, false);
        for (int i: cnt[pc]) {
            vector<int> nodes;
            for (int j = 0; j < gr1.adj.size(); j++) {
                if (i & (1 << j)) {
                    nodes.push_back(j);
                }
            }
            int tot = 0;
            for (int j = 0; j < gr2.adj.size(); j++) {
                bool fine = true;
                for (int k: nodes) {
                    if (!gr.adj[j + sz][k]) {
                        fine = false;
                        break;
                    }
                }
                if (fine) {
                    tot += (1 << j);
                }
            }
            bool fine = true;
            int total = 0;
            for (int x: nodes) {
                total += gr1.weight[x];
                for (int y: nodes) {
                    if (x == y) continue;
                    if (!gr1.adj[x][y]) {
                        fine = false;
                    }
                }
            }
            if (!fine) {
                continue;
            }
            myMax = max((int64_t)gr2.dp[tot] + (int64_t)total, myMax);
        }
    }
    cout << sm - myMax;
}
