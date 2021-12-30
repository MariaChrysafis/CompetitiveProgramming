#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>

using namespace std;

typedef int64_t ll;

vector<vector<int>> dp(2);
string s[2];

bool memoize (int i, int j) {
    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    dp[i][j] = false;
    if (s[i][j] == '#') {
        if (i >= 1 && memoize(i - 1, j)) {
            return (dp[i][j] = true);
        }
        if (j >= 1 && memoize(i, j - 1)) {
            return (dp[i][j] = true);
        }
        if (i == 0 && memoize(i + 1, j)) {
            return (dp[i][j] = true);
        }
        cout << "No\n";
        exit(0);
    } else {
        dp[i][j] = false;
    }
    return dp[i][j];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> s[0] >> s[1];
    dp[0].assign(s[0].length(), -1);
    dp[1].assign(s[1].length(), -1);
    bool hasSeenHashtag = false;
    for (int j = 0; j < s[0].length(); j++) {
        for (int i = 0; i < 2; i++) {
            if (s[i][j] == '#' && !hasSeenHashtag) {
                hasSeenHashtag = true;
                //cout << i << " " << j << '\n';
                dp[i][j] = true;
                break;
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < s[0].length(); j++) {
            memoize(i, j);
        }
    }
    cout << "Yes\n";
}
