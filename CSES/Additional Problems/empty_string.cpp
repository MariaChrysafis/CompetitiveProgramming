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
vector<vector<ll>> dp;
vector<vector<ll>> ch;
string s;
const int MOD = 1e9 + 7;
ll memoize (int i, int j) {
    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    if ((j - i) % 2 == 0) {
        return 0;
    }
    if (j - i == 1) {
        return (s[i] == s[j]);
    }
    if (j < i) {
        return 1;
    }
    dp[i][j] = 0;
    if (s[i] == s[i + 1]) {
        dp[i][j] += (memoize(i + 2, j) * (j - i + 1)/2) % MOD;
    }
    if (s[i] == s[j]) {
        dp[i][j] += memoize(i + 1, j - 1);
    }
    dp[i][j] %= MOD;
    for (int k = i + 2; k <= j - 1; k++) {
        if (s[i] != s[k]) {
            continue;
        }
        int sz1 = (k - i + 1)/2;
        int sz = (j - i + 1)/2;
        dp[i][j] += ((memoize(i + 1, k - 1) * memoize(k + 1, j)) % MOD * ch[sz][sz1]) % MOD;
        dp[i][j] %= MOD;
    }
    return dp[i][j];
}
int main() {
    cin >> s;
    dp.resize(s.length());
    ch.resize(s.length() + 1);
    for (int i = 0; i < ch.size(); i++) {
        ch[i].resize(ch.size());
        for (int j = 0; j < ch.size(); j++) {
            ch[i][j] = 0;
        }
    }
    for (int i = 0; i < ch.size(); i++) {
        for (int j = 0; j < ch[i].size(); j++) {
            if (j == 0) {
                ch[i][j] = 1;
                continue;
            }
            if (i < j) {
                ch[i][j] = 0;
                continue;
            }
            ch[i][j] = ch[i - 1][j] + ch[i - 1][j - 1];
            ch[i][j] %= MOD;
        }
    }
    for (int i = 0; i < s.length(); i++) {
        dp[i].resize(s.length());
        for (int j = 0; j < s.length(); j++) {
            dp[i][j] = -1;
        }
    }
    for (int i = 0; i < s.length(); i++) {
        for (int j = 0; j < s.length(); j++) {
            dp[i][j] = memoize(i, j);
        }
    }
    cout << dp[0][s.length() - 1] << endl;
}
