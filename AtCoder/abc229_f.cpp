#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<ll> A(N + 1);
    vector<ll> B(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> A[i]; //from 0 to i
    }
    for (int i = 1; i <= N; i++) {
        cin >> B[i]; //from i to (i + 1) % N
    }
    vector<vector<vector<ll>>> dp;
    dp.assign(N + 1, {{(ll)1e15, (ll)1e15}, {(ll)1e15, (ll)1e15}});
    dp[0][1][1] = dp[0][0][1] = 1e15;
    dp[1][0][0] = A[1];
    dp[1][1][1] = 0;
    dp[1][0][1] = 1e15;
    dp[1][1][0] = 1e15;
    for (int i = 2; i <= N; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][!k] + !k * A[i]);
                dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k] + B[i - 1] + !k * A[i]);

            }
        }
    }
    dp[N][0][0] += B[N];
    dp[N][1][1] += B[N];
    cout << min(min(dp[N][0][1], dp[N][1][0]), min(dp[N][1][1], dp[N][0][0]));
}
