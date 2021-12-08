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
#pragma GCC optimization ("unroll-loops")
 
#define ll long long
using namespace std;
const int MAX = 2e5 + 10;
int n, q;
vector<int> f;
int dp[MAX][30];
int endUp (int curNode, int curDist) { //where will we end up if we take curDist steps from curNode
    if (curDist == 0) {
        return curNode;
    }
    int lg = log2(curDist);
    return endUp(dp[curNode][lg], curDist - (1 << lg));
}
int dist[MAX];
int sz[MAX];
int id[MAX];
int cyc_dist (int u, int v) {
    if (id[u] != id[v]) {
        return -1;
    }
    if (dist[v] >= dist[u]) {
        return dist[v] - dist[u];
    } else {
        return dist[v] - dist[u] + sz[u] - 1;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;
    f.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> f[i]; f[i]--;
    }
    for (int i = 0; i < n; i++) {
        dp[i][0] = f[i];
    }
    for (int j = 1; j < 30; j++) {
        for (int i = 0; i < n; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }
    bool cycle[n]; //these are all the elements which belong to a cycle
    for (int i = 0; i < n; i++) {
        cycle[i] = false;
    }
    for (int i = 0; i < n; i++) {
        cycle[dp[i][29]] = true;
    }
    for (int i = 0; i < n; i++) {
        if (!cycle[i]) {
            continue;
        }
        for (int j = 0; j < 30; j++) {
            cycle[dp[i][j]] = true;
        }
    }
    for (int i = 0; i < n; i++) {
        if (!cycle[i]) {
            continue;
        }
        int curNode = i;
        int curDist = 1;
        vector<int> nodes;
        while (!dist[curNode]) {
            cycle[curNode] = true;
            id[curNode] = i;
            dist[curNode] = curDist++;
            curNode = f[curNode];
            nodes.push_back(curNode);
        }
        for (int j: nodes) {
            sz[j] = curDist;
        }
    }
    for (int i = 0; i < n; i++) {
        if (dist[i]) {
            dist[i]--;
        }
    }
    vector<vector<int>> inv_adj(n);
    for (int i = 0; i < n; i++)  {
        inv_adj[f[i]].push_back(i);
    }
    queue<pair<int,int>> pq;
    for (int i = 0; i < n; i++) {
        if (cycle[i]) {
            pq.push({0, i});
        }
    }
    map<int,bool> hv;
    while (!pq.empty()) {
        int curNode = pq.front().second;
        int curDist = pq.front().first;
        pq.pop();
        if (hv[curNode]) {
            continue;
        }
        hv[curNode] = true;
        if (!cycle[curNode]) dist[curNode] = curDist;
        for (int i: inv_adj[curNode]) {
            pq.push({curDist + 1, i});
        }
    }
    //return 0;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (cycle[u]) {
            if (cycle[v]) {
                cout << cyc_dist(u, v) << '\n';
            } else {
                cout << "-1\n";
            }
        } else {
            if (cycle[v]) {
                int ans = cyc_dist(endUp(u, dist[u]), v);
                if (ans == -1) {
                    cout << "-1\n";
                } else {
                    cout << ans + dist[u] << '\n';
                }
            } else {
                int d = abs(dist[u] - dist[v]);
                if (endUp(u, d) == v) {
                    cout << d << '\n';
                    continue;
                }
                cout << "-1\n";
            }
        }
    }
 
}
