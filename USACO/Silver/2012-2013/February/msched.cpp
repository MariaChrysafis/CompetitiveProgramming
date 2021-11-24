#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>
#define ll long long
using namespace std;
vector<vector<int>> adj, rev_adj;
vector<int> T;
vector<int> dp;
int memoize (int curNode) {
    if (dp[curNode] != -1) {
        return dp[curNode];
    }
    dp[curNode] = 0;
    for (int i: rev_adj[curNode]) {
        dp[curNode] = max(dp[curNode], memoize(i));
    }
    return (dp[curNode] += T[curNode]);
}
int main() {
    freopen("msched.in", "r", stdin);
    freopen("msched.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    T.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> T[i];
    }
    adj.resize(N), rev_adj.resize(N);
    dp.assign(N, -1);
    adj.resize(N);
    for (int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        rev_adj[y].push_back(x);
    }
    int myMax = 0;
    for (int i = 0; i < N; i++) {
        myMax = max(memoize(i), myMax);
    }
    cout << myMax;
}
