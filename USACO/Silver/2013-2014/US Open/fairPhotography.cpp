#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>

#pragma GCC optimization ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")


typedef long long ll;
const int MOD = 1e9 + 7;
using namespace std;

int main() {
    freopen("fairphoto.in", "r", stdin);
    freopen("fairphoto.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<pair<ll,char>> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i].first >> vec[i].second;
    }
    sort(vec.begin(), vec.end());
    vector<ll> pref;
    pref.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1];
        if (vec[i - 1].second == 'W') pref[i]++;
        else pref[i]--;
    }
    ll suf[n + 1][2];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 2; j++) {
            suf[i][j] = -1e9;
        }
    }
    suf[n][n % 2] = pref[n];
    for (int i = n - 1; i >= 0; i--) {
        suf[i][i % 2] = max(suf[i][i % 2], pref[i]);
        suf[i][0] = max(suf[i][0], suf[i + 1][0]);
        suf[i][1] = max(suf[i][1], suf[i + 1][1]);
    }
    //cout << suf[n][!(n % 2)] << '\n';
    ll myMax = 0;
    for (int i = 0; i < n; i++) {
        int l, r, sl, sr;
        sl = i + 1;
        sr = (n - 1);
        l = sl, r = sr;
        while (l < r) {
            int m = (l + r + 1)/2;
            if (suf[m + 1][(i % 2)] >= pref[i]) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        if (l != r || suf[l + 1][(i % 2)] < pref[i]) {
            continue;
        }
        assert(suf[l + 1][(i % 2)] >= pref[i]);
        //cout << l << " " << pref[i] << " " << suf[l + 1][(i % 2)] << " " << pref[i] << '\n';
        myMax = max(vec[l].first - vec[i].first, myMax);
    }
    cout << myMax;
}
