#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <queue>
#include <algorithm>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;

vector<ll> d, a;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll N, L, K;
    cin >> N >> L >> K;
    d.resize(N), a.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> d[i];
    }
    d.push_back(L);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    ll dp[N + 1][K + 1][2];
    /*
    dp[i][j][bool] ->
     * the minimum cost if we are at position d[i] and we've removed k road signs
     * bool is 0 if we take it and bool is 1 if we do not take it
     */
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            if (i == 0) {
                dp[i][j][1] = 0;
                dp[i][j][0] = 1e9;
                continue;
            }
            dp[i][j][0] = dp[i][j][1] = 1e9;
            for (int prev = 0; prev < i; prev++) {
                //previous taken one
                if (j - (i - prev - 1) >= 0) {
                    dp[i][j][1] = min(dp[i][j][1], dp[prev][j - (i - prev - 1)][1] + abs(d[i] - d[prev]) * a[prev]);
                }
                if (j - (i - prev) >= 0) {
                    dp[i][j][0] = min(dp[i][j][0], dp[prev][j - (i - prev)][1] + abs(d[i] - d[prev]) * a[prev]);
                }
            }
        }
    }
    cout << min(dp[N][K][0], dp[N][K][1]) << '\n';
}
