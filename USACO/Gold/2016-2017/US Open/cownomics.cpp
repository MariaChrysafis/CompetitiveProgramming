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
vector<string> cows[2];
vector<vector<long long>> pref[2];
long long query(bool type, int level, int x, int y) {
    int len = (y - x + 1);
    return (pref[type][level][y + 1] - (pref[type][level][x] * binPow(5, len)) % MOD + MOD) % MOD;
}
bool valid (int l, int r) {
    set<long long> ans;
    for (int i = 0; i < cows[0].size(); i++) {
        ans.insert(query(0, i, l, r));
    }
    for (int i = 0; i < cows[1].size(); i++) {
        if (ans.count(query(1, i, l, r))) {
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
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            string s;
            cin >> s;
            cows[i].push_back(s);
        }
    }
    pref[0].resize(n), pref[1].resize(n);
    for (int dum = 0; dum < 2; dum++) {
        for (int i = 0; i < pref[dum].size(); i++) {
            pref[dum][i].resize(m + 1);
            pref[dum][i][0] = 0;
            for (int j = 1; j <= m; j++) {
                pref[dum][i][j] = (pref[dum][i][j - 1] * 5 + convert[cows[dum][i][j - 1]]) % MOD;
            }
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
        myMin = min(myMin, l - i + 1);
    }
    cout << myMin << endl;
}
