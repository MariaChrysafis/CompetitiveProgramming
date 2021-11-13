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

#define ll long long

using namespace std;
vector<vector<int>> adj;
vector<ll> sub;
vector<ll> dp;
ll dfs (int curNode, int prevNode) {
    sub[curNode] = 1;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            sub[curNode] += dfs(i, curNode);
        }
    }
    dp[0] += sub[curNode];
    return sub[curNode];
}
void memoize (int curNode, int prevNode) {
    if (curNode != 0) {
        dp[curNode] = dp[prevNode];
        dp[curNode] += adj.size() - 2 * sub[curNode];
    }
    for (int j: adj[curNode]) {
        if (j != prevNode) {
            memoize(j, curNode);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    adj.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    sub.assign(N, 0);
    dp.assign(N, -1);
    dp[0] = 0;
    dfs(0, -1);
    memoize(0, -1);
    ll myMax = 0;
    for (int i = 0; i < N; i++) {
        myMax = max(myMax, dp[i]);
    }
    cout << myMax;

}
