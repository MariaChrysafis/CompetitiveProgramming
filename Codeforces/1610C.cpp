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
#define ll int64_t
using namespace std;
const int INF = -(int)1e8;
bool valid (vector<pair<int,int>> v, int people) {
    int dp[(int)v.size() + 1][2];
    dp[0][0] = dp[0][1] = 0;
    for (int i = 1; i <= (int)v.size(); i++) {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
        dp[i][1] = min(max(dp[i - 1][0], dp[i - 1][1]), v[i - 1].second) + 1;
        if (dp[i][1] < people - v[i - 1].first) {
            dp[i][1] = INF;
        }
        //cout << dp[i][0] << " " << dp[i][1] << '\n';
    }
    return max(dp[v.size()][0], dp[v.size()][1]) >= people;
}
int solve() {
    int n;
    cin >> n;
    vector<pair<int,int>> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
    }
    int l = 0;
    int r = n;
    while (l < r) {
        int m = (l + r + 1)/2;
        if (valid(v, m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return l;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        cout << solve() << '\n';
    }
}
