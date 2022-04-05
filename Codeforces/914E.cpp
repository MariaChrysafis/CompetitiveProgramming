#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

using namespace std;
vector<int> total;
int sub[(int) 2e5];
int sz;
vector<int> adj[(int) 2e5];
vector<bool> hasVisited;
int val[(1 << 20)], tot[(1 << 20)];
vector<int64_t> dp, ans;
vector<int> p_xor, we, vis;
int centroid;
void dfs1(int curNode, int prevNode) {
    sub[curNode] = 1;
    for (int i: adj[curNode]) if (!hasVisited[i] && i != prevNode) dfs1(i, curNode), sub[curNode] += sub[i];
    sz = sub[curNode];
}
int get_centroid(int curNode, int prevNode) {
    for (int i: adj[curNode]) if (!hasVisited[i] && i != prevNode && sub[i] >= sz / 2) return get_centroid(i, curNode);
    return curNode;
}
void dfs(int curNode, int prevNode, int x) {
    val[x]++, vis.push_back(curNode), p_xor[curNode] = x, tot[x]++;
    for (int k: total) dp[curNode] += tot[p_xor[curNode] ^ we[centroid] ^ k] - val[p_xor[curNode] ^ we[centroid] ^ k];
    for (int i: adj[curNode]) if (!hasVisited[i] && i != prevNode) dfs(i, curNode, x ^ we[i]);
}
int64_t accumulate(int curNode, int prevNode) {
    for (int i: adj[curNode]) if (i != prevNode && !hasVisited[i]) dp[curNode] += accumulate(i, curNode);
    return dp[curNode];
}
void solve(int curNode) {
    dfs1(curNode, curNode);
    if (sz == 1) {
        hasVisited[curNode] = true;
        return;
    }
    centroid = get_centroid(curNode, curNode);
    hasVisited[centroid] = true;
    vector<int> v;
    for (int i: adj[centroid]) {
        if (!hasVisited[i]) {
            dfs(i, i, we[i]);
            for (int x: vis) {
                dp[centroid] += (__builtin_popcount(p_xor[x] ^ we[centroid]) <= 1), dp[x] += (
                        __builtin_popcount(p_xor[x] ^ we[centroid]) <= 1);
                for (int k: total) dp[centroid] += tot[p_xor[x] ^ we[centroid] ^ k] - val[p_xor[x] ^ we[centroid] ^ k];
                v.push_back(x);
            }
            for (int x: vis) val[p_xor[x]] = 0;
            vis.clear();
        }
    }
    for (int v1: v) {
        tot[p_xor[v1]] = 0;
    }
    for (int i = adj[centroid].size() - 1; i >= 0; i--) {
        if (!hasVisited[adj[centroid][i]]) {
            dfs(adj[centroid][i], adj[centroid][i], we[adj[centroid][i]]);
            for (int x: vis) val[p_xor[x]] = 0;
            vis.clear();
        }
    }
    for (int v1: v) tot[p_xor[v1]] = 0;
    for (int i: adj[centroid]) accumulate(i, i);
    for (int j: v) ans[j] += dp[j], dp[j] = 0;
    ans[centroid] += dp[centroid];
    for (int i: adj[centroid]) if (!hasVisited[i]) solve(i);
}
void add_edge(int u, int v) {
    adj[u].push_back(v), adj[v].push_back(u);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    total.push_back(0);
    for (int i = 0; i < 20; i++) total.push_back((1 << i));
    int N;
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        add_edge(u, v);
    }
    hasVisited.assign(N, false), we.resize(N), ans.resize(N), p_xor.resize(N), dp.assign(N, 0);
    for (int i = 0; i < (1 << 20); i++) val[i] = tot[i] = 0;
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++) we[i] = (1 << (s[i] - 'a'));
    solve(0);
    for (int64_t i: ans) cout << i + 1 << ' ';
}
