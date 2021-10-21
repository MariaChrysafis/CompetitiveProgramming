#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <climits>
#include <vector>

#define ll int

using namespace std;

int main() {
    freopen("wifi.in", "r", stdin);
    freopen("wifi.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, a, b;
    cin >> n >> a >> b;
    a *= 2, b *= 2;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    int dp[n + 1];
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = INT_MAX;
        for (int j = 0; j < i; j++) {
            int ans = dp[j] + a + (b * abs(v[i - 1] - v[j]))/2;
            dp[i] = min(dp[i], ans);
        }
    }
    cout << dp[n]/2;
    if (dp[n] % 2 == 1) cout << ".5";
}
