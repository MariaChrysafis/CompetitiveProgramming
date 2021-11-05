#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <ctime>
#include <set>
#include <algorithm>
#include <iomanip>
#define ll long long
using namespace std;
vector<vector<ll>> dp;
vector<vector<ll>> adj;
const int MOD = 1e9 + 7;
ll memoize (int curNode, int prevNode, int color) {
    if (dp[curNode][color] != -1) {
        return dp[curNode][color];
    }
    dp[curNode][color] = 1;
    for (int i: adj[curNode]) {
        if (i == prevNode) {
            continue;
        }
        ll sub = 0;
        for (int j = 0; j < 3; j++) {
            sub += memoize(i, curNode, j);
        }
        sub -= memoize(i, curNode, color);
        dp[curNode][color] *= sub % MOD;
        dp[curNode][color] %= MOD;
    }
    return dp[curNode][color];
}
int main() {
    freopen("barnpainting.in", "r", stdin);
    freopen("barnpainting.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    vector<int> inDegree;
    inDegree.assign(n, 0);
    adj.resize(n);
    dp.assign(n, {-1, -1, -1});
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[--u].push_back(--v);
        adj[v].push_back(u);
        inDegree[v]++;
    }
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        dp[u].assign({0, 0, 0});
        dp[u][v] = -1;
    }
    cout << (memoize(0, -1, 0) + memoize(0, -1, 1) + memoize(0, -1, 2)) % MOD;
}
