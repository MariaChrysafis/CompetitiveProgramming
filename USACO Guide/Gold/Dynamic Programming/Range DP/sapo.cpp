#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#define ll long long
#include <map>

using namespace std;
int dp[500][500];
string s;
int memoize (int i, int j) {
    if (i == j) {
        return (dp[i][j] = 1);
    }
    if (j - i == 1) {
        return(dp[i][j] = 2 * (s[i] != s[j]));
    }
    if (dp[i][j] != (int)1e8) {
        return dp[i][j];
    }
    if (s[i] == s[j]) {
        dp[i][j] = min(dp[i][j], memoize(i + 1, j - 1));
    }
    for (int k = i; k <= j - 1; k++) {
        dp[i][j] = min(dp[i][j], memoize(i, k) + memoize(k + 1, j));
    }
    return dp[i][j];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> s;
    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 500; j++) {
            dp[i][j] = (int)1e8;
        }
    }
    int dp[s.length()][s.length()];
    for (int i = 0; i < s.length(); i++) {
        for (int j = i; j < s.length(); j++) {
            if (i == j) {
                dp[i][j] = 1;
                continue;
            }
            if (j - i == 1) {
                dp[i][j] = 2 * (s[i] == s[j]);
                continue;
            }
        }
    }
    cout << memoize(0, s.length() - 1);

}
