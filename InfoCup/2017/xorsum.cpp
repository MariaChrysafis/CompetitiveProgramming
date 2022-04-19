#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <complex>
#include <cmath>
#include <set>
#include <queue>
using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
int64_t res (vector<int>& a, int x) {
    int64_t r = a.size() - 1;
    int64_t ans = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] + a[0] > x) {
            break;
        }
        while (a[r] + a[i] > x) {
            r--;
        }
        ans += r + 1 - (r >= i);
    }
    ans /= 2;
    for (int i = 0; i < a.size(); i++) {
        ans += (2 * a[i] <= x);
    }
    return ans;
}
int64_t res (vector<int>&a, int l, int r) {
    return res(a, r) - res(a, l - 1);
}
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    int64_t ans = 0;
    for (int b = 30; b >= 0; b--) {
        vector<int> v2;
        vector<int> v1;
        for (int i = 0; i < v.size(); i++) {
            if (v[i] & (1 << (b + 1))) {
                v[i] ^= (1 << (b + 1));
                v2.push_back(v[i]);
            } else {
                v1.push_back(v[i]);
            }
        }
        int l = 0, r = 0;
        v.clear();
        while (true) {
            if (l == (int)v1.size() && r == (int)v2.size()) break;
            else if (l == (int)v1.size()) v.push_back(v2[r++]);
            else if (r == (int)v2.size()) v.push_back(v1[l++]);
            else if (v1[l] <= v2[r]) v.push_back(v1[l++]);
            else if (v1[l] > v2[r]) v.push_back(v2[r++]);
        }
        int64_t a = 0;
        a += res(v, (1 << b), (1 << (b + 1)) - 1);
        a += res(v, (1 << b) + (1 << (b + 1)), (1 << (b + 2)) - 1);
        ans += ((int64_t)1 << b) * (a % 2);
    }
    cout << ans;
}
