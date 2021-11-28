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
const int MOD = 1e9 + 7;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    ll dp[2 * n + 1][n + 1][2];
    for (int j = 0; j <= n; j++) {
        for (int k = 0; k < 2; k++) {
            dp[0][j][k] = dp[1][j][k] = 0ll;
        }
    }
    for (int pref = 2; pref <= 2 * n; pref++) {
        //we've considered pref stuff
        for (int sum = 0; sum <= n; sum++) {
            //we have a cumulative sum of sum
            for (int flag = 0; flag < 2; flag++) {
                if (sum > pref || sum % 2 != pref % 2) {
                    dp[pref][sum][flag] = -1e9;
                    continue;
                }
                if (pref == 0 || pref == 1) {
                    dp[pref][sum][flag] = 0;
                    continue;
                }
                dp[pref][sum][flag] = 0; //[2,0,0]
                if (sum != 0) {
                    dp[pref][sum][flag] += dp[pref - 1][sum - 1][!flag] + flag;
                }
                if (sum + 1 <= pref - 1) {
                    dp[pref][sum][flag] += dp[pref - 1][sum + 1][!flag] + flag;
                }
            }
            dp[pref][sum][1] = max(dp[pref][sum][1], dp[pref][sum][0]);
            dp[pref][sum][0] %= MOD, dp[pref][sum][1] %= MOD;
        }
    }
    cout << max(dp[2 * n][0][0], dp[2 * n][0][1]) << '\n';
}
