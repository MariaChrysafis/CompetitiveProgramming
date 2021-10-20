#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
const int MOD = 1e9 + 7;
vector<int> read(int n) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    return v;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> s = read(n);
    vector<int> t = read(n);
    vector<pair<int,int>> v;
    for (int i = 0; i < n; i++) {
        v.emplace_back(s[i], 0);
        v.emplace_back(t[i], 1);
    }
    sort(v.begin(), v.end());
    long long dp[2 * n + 1][n + 2][2];
    for (int i = 0; i < 2 * n + 1; i++) {
        for (int j = 0; j < n + 2; j++) {
            dp[i][j][0] = dp[i][j][1] = 0;
        }
    }
    dp[0][0][1] = 1;
    for (int i = 1; i <= 2 * n; i++) {
        for (int open = 0; open <= n; open++) {
            if (v[i - 1].second == 1) {
                dp[i][open][0] = (dp[i - 1][open + 1][0] * (open + 1)) % MOD;
                dp[i][open][1] = (dp[i - 1][open][1] + dp[i - 1][open + 1][1] * (open + 1)) % MOD;
            } else {
                if (open == 0) {
                    dp[i][open][1] = 0;
                    dp[i][open][0] = (dp[i - 1][open][1] + dp[i - 1][open][0]) % MOD;
                } else {
                    dp[i][open][1] = dp[i - 1][open - 1][1];
                    dp[i][open][0] = (dp[i - 1][open][1] + dp[i - 1][open][0] + dp[i - 1][open - 1][0]) % MOD;
                }
            }
        }
    }
    cout << (dp[2 * n][0][0] + dp[2 * n][0][1]) % MOD << endl;
}
