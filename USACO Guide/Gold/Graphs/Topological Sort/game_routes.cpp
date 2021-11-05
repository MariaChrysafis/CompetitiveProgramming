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
vector<vector<int>> adj;
vector<ll> dp;
const int MOD = 1e9 + 7;
int memoize (int x) {
    if (dp[x] != -1) {
        return dp[x];
    }
    if (x == dp.size() - 1) {
        return (dp[x] = 1);
    }
    dp[x] = 0;
    for (int i: adj[x]) {
        dp[x] += memoize(i);
        dp[x] %= MOD;
    }
    return dp[x];
}
int main() {
    int N, M;
    cin >> N >> M;
    adj.resize(N);
    dp.assign(N, -1);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[--u].push_back(--v);
    }
    for (int i = 0; i < N; i++) {
        dp[i] = memoize(i);
    }
    cout << dp[0];
}
