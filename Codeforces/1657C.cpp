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
            pref[i] = (pref[i - 1] + (powr[n - i] * (str[i - 1] - '(' + 1)) % MOD) % MOD;
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
    ipowr[0] = 1; ipowr[1] = inv(powr[1], 1e9 + 9);
    for (int i = 2; i < powr.size(); i++) {
        ipowr[i] = (ipowr[i - 1] * ipowr[1]) % ((int)1e9 + 9);
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        Hasher h1;
        Hasher h2;
        h1.resz((int)1e9 + 9, 31, s);
        reverse(s.begin(), s.end());
        h2.resz((int)1e9 + 9, 31, s);
        reverse(s.begin(), s.end());
        int j = 0;
        int i = 0;
        int cntr = 0;
        while (i < s.length() && j < s.length()) {
            //cout << i << " " << j << '\n';
            if (i == j) {
                j++;
                continue;
            }
            if (abs(i - j) == 1) {
                if ((s[i] == s[j]) || (s[i] == '(' && s[j] == ')')) {
                    i = j;
                    i++, j++;
                    cntr++;
                    continue;
                }
            }
            if (h1.query(i, j) == h2.query((int)s.length() - j - 1, (int)s.length() - i - 1)) {
                //cout << "PAL\n";
                i = j;
                i++, j++;
                cntr++;
                continue;
            }
            j++;
        }
        //cout << i << " " << j << '\n';
        cout << cntr << " " << j - i << '\n';
    }
}
