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
int64_t answer (vector<int> v, int m) {
    int64_t ans = 0;
    for (int j = 1; j <= v.size(); j++) {
        for (int i = 1; i <= m; i++) {
            bool found = false;
            for (int k = j - 1; (k >= 1 && (i * j)/k <= m); k--) {
                if ((i * j) % k == 0) {
                    found = true;
                    break;
                }
            }
            ans += !found;
        }
    }
    return ans;
}
int main () {
    int64_t n, m;
    cin >> n >> m;
    int64_t ans = 0;
    int64_t tot = 0;
    set<int> prev;
    for (int i = 2; i * i <= n; i++) {
        if (prev.count(i)) continue;
        int64_t powr = 1;
        vector<int> interesting;
        while (true) {
            powr *= i;
            if (powr > n) break;
            interesting.push_back(powr);
            prev.insert(powr);
        }
        if (interesting.size() == 2) {
            ans += m + (m + 1)/2;
            tot += 2;
            continue;
        }
        ans += answer(interesting, m);
        tot += interesting.size();
    }
    cout << ans + m * (n - tot - 1) + 1 << '\n';
}
