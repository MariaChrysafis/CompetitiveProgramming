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
#define ll long long
using namespace std;
vector<int> a;
vector<vector<int>> adj;
int dp[201][201];
int n, k;
int memoize (int curNode, int minDepth, int prevNode) {
    if (minDepth >= 201) {
        return 0;
    }
    //minDepth is the maximum distance from the root
    if (dp[curNode][minDepth] != -1) {
        return dp[curNode][minDepth];
    }
    if (minDepth == 0) {
        dp[curNode][minDepth] = 0;
        for (int i: adj[curNode]) {
            if (i == prevNode) continue;
            dp[curNode][minDepth] += memoize(i, k - 1, curNode);
        }
        dp[curNode][minDepth] += a[curNode];
    } else {
        for (int i: adj[curNode]) {
            if (i == prevNode) continue;
            int ans = memoize(i, minDepth - 1, curNode);
            for (int j: adj[curNode]) {
                if (i == j || j == prevNode) continue;
                ans += memoize(j, max(k - minDepth - 1, minDepth - 1), curNode);
            }
            dp[curNode][minDepth] = max(dp[curNode][minDepth], ans);
        }
    }
    dp[curNode][minDepth] = max(dp[curNode][minDepth], memoize(curNode, minDepth + 1, prevNode));
    return dp[curNode][minDepth];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> k;
    k++; //everything must be >= k
    a.resize(n), adj.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = -1;
        }
    }
    int myMax = 0;
    for (int j = 0; j <= n; j++) {
        memoize(0, j, -1);
        myMax = max(myMax, dp[0][j]);
    }
    cout << myMax;
}
