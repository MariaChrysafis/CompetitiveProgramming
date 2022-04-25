#include <cmath>
#include <iostream>
#include <set>
#include <vector>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <bitset>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
int64_t MOD = 1e9 + 7;
int64_t binPow (int64_t x, int64_t y) {
    int64_t res = x;
    int64_t ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans *= res; ans %= MOD;
        }
        res *= res, res %= MOD;
        y /= 2;
    }
    return ans;
}
int64_t inv (int64_t x) {
    return binPow(x, MOD - 2);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int64_t> d(n + 1);
    d[0] = 1, d[1] = 0;
    for (int i = 2; i <= n; i++) {
        d[i] = (i - 1) * (d[i - 1] + d[i - 2]) % MOD;
        d[i] %= MOD;
    }
    cout << d[n];
}
