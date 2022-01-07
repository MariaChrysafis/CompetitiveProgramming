#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>

#pragma GCC optimization ("O1")
#pragma GCC optimization ("avx")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

string getLargest(string s1, string s2) {
    string str = "";
    int ind = 0;
    for (int i = 0; i < s1.length(); i++) {
        if (s1[i] == s2[ind]) {
            str += s1[i], ind++;
            if (ind == s2.length()) {
                break;
            }
        }
    }
    return str;
}

string remove(string s, string sub) {
    int ind = 0;
    string ans = "";
    for (int i = 0; i < s.length(); i++) {
        if (ind != sub.length() && s[i] == sub[ind]) {
            ind++;
        } else {
            ans += s[i];
        }
    }
    return ans;
}

void solve(string s, string s2) {
    string s1 = getLargest(s, s2);
    string orig = s2;
    s2 = remove(s2, s1);
    int dp[s.length() + 1][s1.length() + 1];
    while (true) {
        for (int i = 0; i <= s.length(); i++) {
            for (int j = 0; j <= s1.length(); j++) {
                if (i == 0) {
                    if (j == 0) {
                        dp[i][j] = 0;
                        continue;
                    }
                    dp[i][j] = -1e9;
                    continue;
                }
                if (dp[i - 1][j] >= 0 && dp[i - 1][j] != s2.length() && s[i - 1] == s2[dp[i - 1][j]]) {
                    dp[i][j] = dp[i - 1][j] + 1;
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
                if (j >= 1 && s[i - 1] == s1[j - 1]) {
                    dp[i][j] = max(dp[i - 1][j - 1], dp[i][j]);
                }
            }
        }
        if (dp[s.length()][s1.length()] == s2.length()) {
            cout << "YES\n";
            return;
        }
        if (s1.empty()) {
            break;
        }
        s1.pop_back();
        s2 = remove(orig, s1);
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        string s1, s2;
        cin >> s1 >> s2;
        solve(s1, s2);
    }
}
