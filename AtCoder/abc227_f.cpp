#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll H, W, K;
    cin >> H >> W >> K;
    ll grid[H][W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> grid[i][j];
        }
    }
    ll myMin = 1e12;
    for (int i1 = 0; i1 < H; i1++) {
        for (int j1 = 0; j1 < W; j1++) {
            //everything greater than grid[i1][j1], we chose
            ll dp[H][W][K + 1];
            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    for (int k = 0; k <= K; k++) {
                        dp[i][j][k] = 1e12;
                    }
                }
            }
            if (grid[0][0] < grid[i1][j1]) {
                dp[0][0][0] = 0;
            } else {
                dp[0][0][1] = grid[0][0];
            }
            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    for (int k = 0; k <= K; k++) {
                        if (i == 0 && j == 0) {
                            continue;
                        }
                        if (i != 0) {
                            if (grid[i][j] <= grid[i1][j1]) {
                                dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k]);
                            }
                            if (grid[i][j] >= grid[i1][j1]){
                                if (k > 0) {
                                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k - 1] + grid[i][j]);
                                }
                            }
                        }
                        if (j != 0) {
                            if (grid[i][j] <= grid[i1][j1]) {
                                dp[i][j][k] = min(dp[i][j][k], dp[i][j - 1][k]);
                            }
                            if (grid[i][j] >= grid[i1][j1]){
                                if (k > 0) {
                                    dp[i][j][k] = min(dp[i][j][k], dp[i][j - 1][k - 1] + grid[i][j]);
                                }
                            }
                        }
                    }
                }
            }
            myMin = min(myMin, dp[H - 1][W - 1][K]);
        }
    }
    cout << myMin;

}
