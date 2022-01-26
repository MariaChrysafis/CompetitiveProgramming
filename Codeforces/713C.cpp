#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <climits>
#include <cstring>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>
#include <random>
#include <array>
#include <chrono>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    int64_t arr[N];
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        arr[i] -= i;
        //cout << arr[i] << ' ';
    }
    //cout << '\n';
    int64_t sarr[N];
    for (int i = 0; i < N; i++) {
        sarr[i] = arr[i];
    }
    sort (sarr, sarr + N);
    int64_t dp[N][N];
    int64_t dpM[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dpM[i][j] = LLONG_MAX;
        }
    }
    for (int j = 0; j < N; j++) {
        dp[0][j] = abs(sarr[j] - arr[0]);
        if (j != 0) dpM[0][j] = dpM[0][j - 1];
        dpM[0][j] = min(dpM[0][j], dp[0][j]);
    }
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = abs(arr[i] - sarr[j]);
            int64_t mn = dpM[i - 1][j];
            dp[i][j] += mn;
            if (j != 0) dpM[i][j] = dpM[i][j - 1];
            dpM[i][j] = min(dpM[i][j], dp[i][j]);
        }
    }
    int64_t ans = LLONG_MAX;
    for (int j = 0; j < N; j++) {
        //cout << dp[N - 1][j] << ' ';
        ans = min(ans, dp[N - 1][j]);
    }
    cout << ans;
}
