#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bit>
#include <bitset>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;
string s;

bool isSubstring(string s1, string s2) {
    int M = s1.length();
    int N = s2.length();
    for (int i = 0; i <= N - M; i++) {
        int j;
        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;

        if (j == M)
            return true;
    }

    return false;
}

bool isSubstring(int l1, int r1, int l2, int r2) {
    //is [l1, r1] a substring of [l2, r2]
    string str1;
    for (int i = l1; i <= r1; i++) {
        str1 += s[i];
    }
    string str2;
    for (int i = l2; i <= r2; i++) {
        str2 += s[i];
    }
    return isSubstring(str1, str2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, a, b;
    cin >> n >> a >> b;
    cin >> s;
    int dp[n];
    for (int i = 0; i < n; i++) {
        dp[i] = (int) 1e8;
    }
    dp[0] = a;
    for (int i = 1; i < n; i++) {
        if (!isSubstring(i, i, 0, i - 1)) {
            dp[i] = dp[i - 1] + a;
            continue;
        }
        int l = 1;
        int r = i;
        while (l != r) {
            int m = (l + r)/2;
            if (isSubstring(m, i, 0, m - 1)) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        dp[i] = min(dp[i - 1] + a, dp[l - 1] + b);
    }
    cout << dp[n - 1];
}
