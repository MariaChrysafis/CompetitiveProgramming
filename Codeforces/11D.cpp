#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>

using namespace std;
typedef long long ll;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    ll dp[(1 << N)][N];
    for (int i = 0; i < (1 << N); i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = 0;
        }
    }
    for (int j = 0; j < N; j++) {
        dp[(1 << j)][j] = 1;
    }
    for (int mask = 1; mask < (1 << N); mask++) {
        int st = log2(mask);
        assert(mask & (1 << st));
        for (int j = 0; j < N; j++) {
            //we go from st to j
            if (!(mask & (1 << j))) {
                continue;
            }
            if (st == j) {
                continue;
            }
            for (int k: adj[j]) {
                //we go from st to k
                if (mask & (1 << k)) {
                    assert(mask & (1 << k)); assert(mask & (1 << j));
                    dp[mask][j] += dp[mask - (1 << j)][k];
                }
            }
        }
    }
    ll ans = 0;
    for (int i = 1; i < (1 << N); i++) {
        int st = log2(i);
        for (int j: adj[st]) {
            ans += dp[i][j];
        }
    }
    cout << (ans - M)/2 << '\n';
}
