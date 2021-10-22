#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
long long solve(vector<long long> cows, int k) { //answer if we unlock the first door in cows
    int n = cows.size();
    long long cost[n][n]; //cost[i][j] -> cost to unlock door i and let cows i...j flock to the ith door
    for (int i = 0; i < n; i++) {
        int j = i;
        int cntr = n;
        int dist = 0; //current distance from the ith door
        while (cntr--) {
            if (i == j) {
                cost[i][j] = 0;
            } else {
                cost[i][j] = cost[i][(j - 1 + n) % n] + cows[j] * dist;
            }
            dist++, j++;
            if (j == n) {
                j = 0;
            }
        }
    }
    long long dp[n][k]; //dp[i][j] -> we let free all the cows from 0...i and we unlock j + 1 doors
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            dp[i][j] = INT_MAX;
        }
    }
    for (int i = 1; i < n; i++) {
        dp[i][0] = cost[0][i];
        for (int j = 1; j < k; j++) {
            for (int l = 0; l < i; l++) {
                dp[i][j] = min(dp[i][j], dp[l][j - 1] + cost[l + 1][i]);
            }
        }
    }
    return dp[n - 1][k - 1];
}
int main() {
    freopen("cbarn2.in", "r", stdin);
    freopen("cbarn2.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    vector<long long> cows(n);
    for (int i = 0; i < n; i++) {
        cin >> cows[i];
    }
    long long myMin = INT_MAX;
    for (int i = 0; i < n; i++) {
        rotate(cows.begin(), cows.begin() + 1, cows.end()); //we change our starting position
        myMin = min(solve(cows, k), myMin);
    }
    cout << myMin << endl;
}
