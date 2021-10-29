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
int dist (int x, int y) {
    return abs(x - y);
}
const ll INF = 1e12;
int main() {
    freopen("cowrun.in", "r", stdin);
    freopen("cowrun.out", "w", stdout);
    int n;
    cin >> n;
    vector<ll> pos, neg;
    pos = {0};
    neg = {0};
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        if (x > 0) {
            pos.push_back(x);
        } else if (x < 0){
            neg.push_back(x);
        }
    }
    sort(pos.begin(), pos.end());
    sort(neg.begin(), neg.end());
    reverse(neg.begin(), neg.end());
    ll dp[pos.size()][neg.size()][2];
    for (int i = 0; i < pos.size(); i++) {
        for (int j = 0; j < neg.size(); j++) {
            if (i == 0 && j == 0) {
                dp[i][j][0] = dp[i][j][1] = 0;
                continue;
            }
            ll mult = (pos.size() + neg.size() - i - j - 1);
            dp[i][j][0] = INF;
            if (i >= 1) dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j][1] + mult * dist(pos[i], neg[j]));
            if (i >= 1) dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j][0] + mult * dist(pos[i], pos[i - 1]));
            dp[i][j][1] = INF;
            if (j >= 1) dp[i][j][1] = min(dp[i][j][1], dp[i][j - 1][1] + mult * dist(neg[j], neg[j - 1]));
            if (j >= 1) dp[i][j][1] = min(dp[i][j][1], dp[i][j - 1][0] + mult * dist(pos[i], neg[j]));
        }
    }
    cout << min(dp[pos.size() - 1][neg.size() - 1][0], dp[pos.size() - 1][neg.size() - 1][1]);
}
