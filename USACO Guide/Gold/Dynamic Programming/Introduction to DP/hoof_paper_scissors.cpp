#include <cmath>
#include <iostream>
#include <set>
#include <vector>
#include <map>
using namespace std;
int beats (int x, int y) {
    return ((x + 1) % 3 == y);
}
int main() {
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<int> vec(n);
    for (int i = 0; i < vec.size(); i++) {
        char c;
        cin >> c;
        if (c == 'H') vec[i] = 2;
        else if (c == 'P') vec[i] = 1;
        else vec[i] = 0;
    }
    int dp[n + 1][k + 1][3];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j][0] = dp[i][j][1] = dp[i][j][2] = 0;
        }
    }
    dp[0][0][0] = dp[0][0][1] = dp[0][0][2] = 0;
    int myMax = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            for (int move = 0; move < 3; move++) {
                dp[i][j][move] = dp[i - 1][j][move] + beats(move, vec[i - 1]);
                if (j != 0) {
                    for (int d = 0; d < 3; d++) {
                        dp[i][j][move] = max(dp[i - 1][j - 1][d] + beats(move, vec[i - 1]), dp[i][j][move]);
                    }
                }
                if (i == n) {
                    myMax = max(myMax, dp[i][j][move]);
                }
            }
        }
    }
    cout << myMax;
}
