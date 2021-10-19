#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <map>
#include <queue>
#include <climits>
#include <set>

using namespace std;
const int MOD = 1e9 + 7;
long long mult (long long x, long long y) {
    return (x * y) % MOD;
}
long long binPow(long long x, long long y) {
    long long ans = 1;
    long long res = x;
    while (y > 0) {
        if (y & 1) {
            ans = mult(res, ans);
        }
        res = mult(res, res);
        y >>= 1;
    }
    return ans;
}
vector<string> spotty, plain;
vector<vector<long long>> pref_spotty, pref_plain;
long long querySpotty(int level, int x, int y) {
    int len = (y - x + 1);
    return (pref_spotty[level][y + 1] - (pref_spotty[level][x] * binPow(5, len)) % MOD + MOD) % MOD;
}
long long queryPlain (int level, int x, int y) {
    int len = y - x + 1;
    return (pref_plain[level][y + 1] - (pref_plain[level][x] * binPow(5, len)) % MOD + MOD) % MOD;
}
bool valid (int l, int r) {
    set<long long> ans;
    for (int i = 0; i < pref_spotty.size(); i++) {
        ans.insert(querySpotty(i, l, r));
    }
    for (int i = 0; i < pref_plain.size(); i++) {
        if (ans.count(queryPlain(i, l, r))) {
            return false;
        }
    }
    return true;
}
int main() {
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);
    map<char,int> convert;
    convert['A'] = 1, convert['C'] = 2, convert['T'] = 3, convert['G'] = 4;
    //cout << convert['A'] << endl;
    int n, m;
    cin >> n >> m;
    spotty.resize(n), plain.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> spotty[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> plain[i];
    }
    pref_spotty.resize(n), pref_plain.resize(n);
    for (int i = 0; i < pref_spotty.size(); i++) {
        pref_spotty[i].resize(m + 1);
        pref_spotty[i][0] = 0;
        for (int j = 1; j <= m; j++) {
            pref_spotty[i][j] = (pref_spotty[i][j - 1] * 5 + convert[spotty[i][j - 1]]) % MOD;
        }
    }
    for (int i = 0; i < pref_plain.size(); i++) {
        pref_plain[i].resize(m + 1);
        pref_plain[i][0] = 0;
        for (int j = 1; j <= m; j++) {
            pref_plain[i][j] = (pref_plain[i][j - 1] * 5 + convert[plain[i][j - 1]]) % MOD;
        }
    }
    int myMin = INT_MAX;
    for (int i = 0; i < m; i++) {
        if (!valid(i, m - 1)) {
            continue;
        }
        int l = i;
        int r = m - 1;
        while (l < r) {
            //cout << l << " " << r << endl;
            int mid = (l + r)/2;
            if (valid(i, mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        //cout << l << " " << i << endl;
        myMin = min(myMin, l - i + 1);
    }
    cout << myMin << endl;
}
