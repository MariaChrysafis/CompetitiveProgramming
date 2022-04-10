#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
 
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
vector<vector<int>> adj;
vector<int> color;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, K;
    cin >> N >> M >> K;
    adj.resize(32 * N), color.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> color[i];
        color[i]--;
    }
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        for (int mask_u = 0; mask_u < 32; mask_u++) {
            if (mask_u & (1 << color[u]) && !(mask_u & (1 << color[v]))) {
                adj[mask_u * N + u].push_back((mask_u ^ (1 << color[v])) * N + v);
            }
        }
        for (int mask_v = 0; mask_v < 32; mask_v++) {
            if (mask_v & (1 << color[v]) && !(mask_v & (1 << color[u]))) {
                adj[mask_v * N + v].push_back((mask_v ^ (1 << color[u])) * N + u);
            }
        }
    }
    vector<int64_t> dp;
    dp.assign(32 * N , 0);
    for (int i = 0; i < N; i++) {
        dp[N * (1 << color[i]) + i] = 1;
    }
    for (int bits = 0; bits <= 5; bits++) {
        for (int mask = 0; mask < 32; mask++) {
            if (__builtin_popcount(mask) != bits) {
                continue;
            }
            for (int j = 0; j < N; j++) {
                for (int k: adj[mask * N + j]) {
                    dp[k] += dp[mask * N + j];
                }
            }
        }
    }
    int64_t ans = 0;
    for (int i = 0; i < dp.size(); i++) {
        ans += dp[i];
    }
    cout << ans - N << '\n';
}
