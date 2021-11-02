#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <set>
#include <iomanip>
#define ll unsigned long long
using namespace std;
int dist (pair<int,int> p1, pair<int,int> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}
int main() {
    freopen("marathon.in", "r", stdin);
    freopen("marathon.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<pair<int,int>> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first >> arr[i].second;
    }
    ll dp[n][n + 1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = (ll)1e9;
        }
    }
    dp[0][1] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 2; j <= n; j++) {
            for (int l = 0; l < i; l++) {
                dp[i][j] = min(dp[i][j], dp[l][j - 1] + dist(arr[i], arr[l]));
            }
        }
    }
    //cout << dp[2][2] << endl;
    cout << dp[n - 1][n - k] << endl;
}
