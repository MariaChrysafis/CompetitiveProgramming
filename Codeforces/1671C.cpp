#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <complex>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <set>
#include <queue>
using namespace std;
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int64_t n, x;
        cin >> n >> x;
        vector<int64_t> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        sort(v.begin(), v.end());
        vector<int64_t> pref = {0};
        vector<int64_t> tot;
        for (int i = 1; i <= n; i++) {
            pref.push_back(pref.back() + v[i - 1]);
            if (pref.back() > x) break;
            tot.push_back((x - pref.back())/i);
        }
        if (tot.empty()) {
            cout << 0 << '\n';
            continue;
        }
        int64_t ans = tot.size() * (tot.back() + 1);
        for (int i = 1; i < tot.size(); i++) {
            ans += abs(tot[i - 1] - tot[i]) * (i);
        }
        cout << ans << '\n';
    }
}
