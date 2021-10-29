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
using namespace std;
#define ll long long
const int MOD = 1e9 + 7;
int sub (int x, int y) {
    if (x < y) {
        return (x - y + MOD) % MOD;
    } else {
        return (x - y) % MOD;
    }
}
int add (int x, int y) {
    if (x + y < MOD) {
        return (x + y);
    } else {
        return x + y - MOD;
    }
}
int main() {
    freopen("hopscotch.in", "r", stdin);
    freopen("hopscotch.out", "w", stdout);
    ll N, M, K;
    cin >> N >> M >> K;
    signed int dp[N][M][K + 1]; // how much stuff in the nxm rectange which has value K
    signed int cur[M][K + 1];
    signed int prev[M][K + 1];
    signed int ans[N][M]; //ways to go from (0, 0) to (N - 1, M - 1)
    int arr[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
            arr[i][j]--;
            ans[i][j] = 0;
            for (int val = 0; val <= K; val++) {
                dp[i][j][val] = 0;
            }
            cur[i][j] = prev[i][j] = 0;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == 0 && j == 0) {
                ans[i][j] = 1;
            } else if (i == 0 || j == 0) {
                ans[i][j] = 0;
            } else {
                ans[i][j] = 0;
                for (int k = 0; k <= K; k++) {
                    //ans[i][j] += prev[j - 1][k];
                    ans[i][j] = add(ans[i][j], prev[j - 1][k]);
                }
                //ans[i][j] -= prev[j - 1][arr[i][j]];
                ans[i][j] = sub(ans[i][j], prev[j - 1][arr[i][j]]);
            }
            for (int k = 0; k <= K; k++) {
                if (i == 0 || j == 0) {
                    cur[j][k] = (arr[0][0] == k);
                } else {
                    //cur[j][k] = cur[j - 1][k] + prev[j][k] - prev[j - 1][k] + (arr[i][j] == k) * ans[i][j];
                    cur[j][k] = add(cur[j][k], cur[j - 1][k]);
                    cur[j][k] = add(cur[j][k], prev[j][k]);
                    cur[j][k] = sub(cur[j][k], prev[j - 1][k]);
                    cur[j][k] = add(cur[j][k], (arr[i][j] == k) * ans[i][j]);
                }
                dp[i][j][k] += MOD;
                dp[i][j][k] %= MOD;
            }
        }
        for (int j = 0; j < M; j++) {
            for (int k = 0; k <= K; k++) {
                prev[j][k] = cur[j][k];
                cur[j][k] = 0;
            }
        }
    }
    cout << ans[N - 1][M - 1];
}
