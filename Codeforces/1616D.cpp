#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

typedef int64_t ll;

int gcd (int a, int b) {
    if (!a || !b) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}

pair<int,int> reduce (int a, int b) {
    int g = gcd(abs(a), abs(b));
    a /= g;
    b /= g;
    if ((b < 0 && a > 0) || (a < 0 && b < 0)) {
        b = -b, a = -a;
    }
    return {a, b};
}

pair<int,int> add (pair<int,int> p1, pair<int,int> p2) {
    return reduce(p1.first * p2.second + p1.second * p2.first, p1.second * p2.second);
}

void solve() {
    int n;
    cin >> n;
    ll arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    ll x;
    cin >> x;
    int dp[n][2][2];
    dp[0][0][0] = 0;
    dp[0][0][1] = 1;
    dp[0][1][0] = 0;
    dp[0][1][1] = 1;
    for (int i = 1; i < n; i++) {
        dp[i][0][0] = max(dp[i - 1][1][0], dp[i - 1][0][0]);
        dp[i][0][1] = max(dp[i - 1][1][0], dp[i - 1][0][0]) + 1;
        dp[i][1][0] = max(dp[i - 1][1][1], dp[i - 1][0][1]);
        if (arr[i] + arr[i - 1] < 2 * x) {
            dp[i][1][1] = 0;
        } else {
            dp[i][1][1] = dp[i - 1][0][1];
            if (i >= 2 && arr[i] + arr[i - 1] + arr[i - 2] >= 3 * x) {
                dp[i][1][1] = max(dp[i][1][1], dp[i - 1][1][1]);
            }
            dp[i][1][1]++;
        }
        //cout << dp[i][0][0] << '\n';
    }
    cout << max(max(dp[n - 1][0][0], dp[n - 1][0][1]), max(dp[n - 1][1][0], dp[n - 1][1][1])) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

}
