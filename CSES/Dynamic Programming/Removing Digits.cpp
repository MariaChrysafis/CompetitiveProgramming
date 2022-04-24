#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>
#include <climits>
#include <set>
using namespace std;
int main() {
    int n;
    cin >> n;
    int dp[n + 1];
    for (int i = 0; i <= n; i++) {
        dp[i] = INT_MAX;
    }
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        string s = to_string(i);
        set<int> digits;
        for (int j = 0; j < s.length(); j++) {
            digits.insert(s[j] - '0');
        }
        for (int j: digits) {
            if (j != 0) {
                dp[i] = min(dp[i - j] + 1, dp[i]);
            }
        }
    }
    cout << dp[n];
}
