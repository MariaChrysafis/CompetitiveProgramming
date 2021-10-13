#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <algorithm>
#pragma pack
using namespace std;
int main() {
    freopen("threesum.in", "r", stdin);
    freopen("threesum.out", "w", stdout);
    int n, q;
    cin >> n >> q;
    unsigned int dp[n][n];
    int v[n];
    vector<vector<int>> oc;
    vector<int> rev(2e6 + 10);
    for (int i = 0; i < rev.size(); i++) {
        rev[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        assert(v[i] <= (int)1e6);
        rev[v[i] + (int)1e6] = i;
    }
    oc.resize(n);
    for (int i = 0; i < n; i++) {
        oc[i].resize(n + 1);
        oc[i][0] = 0;
        for (int j = 1; j <= n; j++) {
            oc[i][j] = oc[i][j - 1] + (v[j - 1] == v[i]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (abs(j - i) <= 1 || j < i) continue;
            int ans = 0;
            if (-v[i] - v[j] + (int)1e6 < 0 || -v[i] - v[j] + (int)1e6 >= rev.size()) {
                ans = 0;
            } else {
                int fnd = rev[-v[i] - v[j] + (int)1e6];
                if (fnd == -1) ans = 0;
                else ans = oc[fnd][j] - oc[fnd][i + 1];
            }
            dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1] + ans;
        }
    }
    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << dp[x - 1][y - 1] << '\n';
    }
}
