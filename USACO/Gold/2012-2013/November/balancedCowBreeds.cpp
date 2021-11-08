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
int conv (char c) {
    if (c == '(') return 1;
    return -1;
}
int main() {
    freopen("bbreeds.in", "r", stdin);
    freopen("bbreeds.out", "w", stdout);
    string s;
    cin >> s;
    vector<int> depth = {0};
    for (int i = 0; i < s.length(); i++) {
        depth.push_back(depth.back() + conv(s[i]));
    }
    int dp[s.length() + 1][s.length() + 1];
    for (int i = 0; i <= s.length(); i++) {
        for (int j = 0; j <= s.length(); j++) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;
    for (int i = 1; i <= s.length(); i++) {
        for (int j = 0; j <= s.length(); j++) {
            if (depth[i] - j < 0) {
                continue;
            }
            //get a holstein
            if (j - conv(s[i - 1]) >= 0) {
                dp[i][j] += dp[i - 1][j - conv(s[i - 1])];
            }
            //get a guernsey
            dp[i][j] += dp[i - 1][j];
            dp[i][j] %= 2012;
            //cout << dp[i][j] << " ";
        }
        //cout << endl;
    }
    cout << dp[s.length()][0];
}
