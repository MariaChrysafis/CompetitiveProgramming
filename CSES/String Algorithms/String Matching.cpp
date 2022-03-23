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
    while (powr.size() != 1e6 + 5) {
        powr.push_back(powr.back() * 31);
        powr.back() %= (int)1e9 + 9;
    }
    ipowr.resize(powr.size());
    for (int i = 0; i < powr.size(); i++) {
        ipowr[i] = inv(powr[i], (int)1e9 + 9);
    }
    string s1, s2; cin >> s1 >> s2;
    Hasher h1;
    h1.resz((int)1e9 + 9, 31, s1);
    Hasher h2;
    h2.resz((int)1e9 + 9, 31, s2);
    int cntr = 0;
    for (int i = 0; i < s1.size(); i++) {
        if (i + s2.size() - 1 >= s1.size()) {
            continue;
        }
        if (h1.query(i, i + s2.size() - 1) == h2.query(0, (int)s2.size() - 1)) {
            cntr++;
        }
    }
    cout << cntr;
}
