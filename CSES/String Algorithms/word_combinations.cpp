#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>
using namespace std;
 
int64_t binPow (int64_t x, int64_t y, int64_t MOD) {
    x %= MOD;
    int64_t res = x;
    int64_t ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res, res %= MOD;
        y /= 2;
    }
    return ans;
}
int64_t inv (int64_t x, int64_t MOD) {
    return binPow(x, MOD - 2, MOD);
}
vector<int64_t> powr = {1};
vector<int64_t> ipowr = {1};
struct Hasher {
    void resz (int mod, int base, string str) {
        int n = str.size();
        this->sz = n;
        this->MOD = mod, this->BASE = base;
        this->pref.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            pref[i] = (pref[i - 1] + (powr[n - i] * (str[i - 1] - 'a' + 1)) % MOD) % MOD;
            pref[i] %= MOD;
        }
    }
    int sz;
    int MOD;
    int BASE;
    vector<int64_t> pref;
    int64_t query (int l, int r) {
        return (ipowr[sz - r - 1] * (pref[r + 1] - pref[l] + MOD) % MOD) % MOD;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (powr.size() != 1e5 + 5) {
        powr.push_back(powr.back() * 31);
        powr.back() %= (int)1e9 + 9;
    }
    ipowr.resize(powr.size());
    for (int i = 0; i < powr.size(); i++) {
        ipowr[i] = inv(powr[i], (int)1e9 + 9);
    }
    string s;
    cin >> s;
    int N;
    cin >> N;
    vector<int64_t> pref(s.length() + 1);
    pref[0] = 0;
    for (int j = 1; j < pref.size(); j++) {
        pref[j] = pref[j - 1] + (powr[(int)s.length() - j] * (int64_t)(s[j - 1] - 'a' + 1)) % ((int)1e9 + 9);
        pref[j] %= (int)1e9 + 9;
    }
    pair<int,int> v[N];
    for (int i = 0; i < N; i++) {
        string str; cin >> str;
        int64_t ans = 0;
        for (int j = 1; j <= str.length(); j++) {
            ans += (powr[(int)str.length() - j] * (int64_t)(str[j - 1] - 'a' + 1)) % ((int)1e9 + 9);
            ans %= (int)1e9 + 9;
        }
        v[i].first = str.length(), v[i].second = ans;
    }
    vector<int64_t> dp;
    dp.assign(s.length() + 1, 0);
    dp[0] = 1;
    const int MOD = 1e9 + 9;
    for (int i = 1; i < dp.size(); i++) {
        for (auto& p: v) {
            if (p.first > i) {
                continue;
            }
            if ((ipowr[(int)s.length() - (i - 1) - 1] * (pref[i - 1 + 1] - pref[i - p.first] + MOD) % MOD) % MOD == p.second) {
                dp[i] += dp[i - p.first];
                dp[i] %= (int)1e9 + 7;
            }
        }
    }
    cout << dp[dp.size() - 1];
}
