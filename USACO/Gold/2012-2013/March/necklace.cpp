#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <cstring>
#include <cstdio>
#include <queue>
#include <map>

using namespace std;
string s1, s2;
vector<vector<int>> dp;
const int INF = 1e9;
const int MOD = 1e9 + 7;
const int base = 27;
typedef int64_t ll;

vector<ll> get_hash(string s) {
    vector<ll> hash = {0};
    for (int i = 0; i < s.size(); i++) {
        hash.push_back(hash.back() * base + (s[i] - 'a' + 1));
        hash.back() %= MOD;
    }
    return hash;
}

ll mult(ll x, ll y) {
    return (x * y) % MOD;
}

vector<ll> powr;

ll get(vector<ll> &hash, int l, int r) {
    return (hash[r + 1] - mult(hash[l], powr[r - l + 1]) + MOD) % MOD;
}

int sim(vector<ll> &hs, vector<ll> &ht) {
    int myMax = 0;
    for (int len = 1; len <= min(hs.size() - 1, ht.size() - 1); len++) {
        if (get(ht, 0, len - 1) == get(hs, hs.size() - len - 1, hs.size() - 1 - 1)) {
            myMax = max(myMax, len);
        }
    }
    return myMax;
}

int main() {
    freopen("necklace.in", "r", stdin);
    freopen("necklace.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    powr.push_back(1);
    while (powr.size() != 1e5 + 1) {
        powr.push_back(mult(powr.back(), base));
    }
    cin >> s1 >> s2;
    dp.resize(s1.length() + 1);
    for (int i = 0; i <= s1.length(); i++) {
        dp[i].assign(s2.length() + 1, INF);
    }
    int ans[s2.length() + 1][26];
    for (int j = 0; j <= s2.length(); j++) {
        for (int i = 0; i < 26; i++) {
            ans[j][i] = INF;
        }
    }
    vector<ll> hs2 = get_hash(s2);
    vector<ll> hs = {0};
    for (int j = 0; j < s2.length(); j++) {
        for (char c = 'a'; c <= 'z'; c++) {
            hs.emplace_back(mult(hs.back(), base) + (c - 'a' + 1));
            ans[j][c - 'a'] = sim(hs, hs2);
            hs.pop_back();
        }
        hs.emplace_back(mult(hs.back(), base) + (s2[j] - 'a' + 1));
    }
    dp[0][0] = 0;
    for (int i = 1; i <= s1.length(); i++) {
        dp[i][0] = dp[i - 1][0] + 1;
        for (int j = 0; j < s2.length(); j++) {
            dp[i][ans[j][s1[i - 1] - 'a']] = min(dp[i - 1][j], dp[i][ans[j][s1[i - 1] - 'a']]);
        }
        for (int j = 1; j < s2.length(); j++) {
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
        }
        dp[i][s2.length()] = INF;
    }
    int myMin = INF;
    for (int j = 0; j <= s2.length(); j++) {
        myMin = min(myMin, dp[s1.length()][j]);
    }
    cout << myMin;
}
