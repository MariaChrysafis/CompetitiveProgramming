#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <bitset>
#include <stack>
#include <cstdlib>
#include <queue>
#include <stdint.h>
#include <vector>
#include <cassert>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <limits.h>

using namespace std;

const int MX = (1 << 20);

const int MOD = 1e9 + 7;

int64_t binPow (int64_t x, int64_t y) {
    int64_t res = x; int64_t ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res, res %= MOD;
        y /= 2;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    vector<int64_t> dp(MX); //dp[i] -> how many sequences have bitwise and which is a supermask of i (i.e. all elements in the sequence are supermasks of i)
    dp.assign(MX, 0);
    for (int i = 0; i < N; i++) {
        dp[arr[i]]++;
    }
    for (int i = 0; i < log2(MX); i++) {
        for (int j = 0; j < MX; j++) {
            if (!(j & (1 << i))) {
                dp[j] += dp[j ^ (1 << i)];
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < MX; i++) {
        if (__builtin_popcount(i) % 2 == 0) {
            ans += binPow(2, dp[i]), ans %= MOD;
        } else {
            ans += (MOD - binPow(2, dp[i])) % MOD; ans %= MOD;
        }
    }
    cout << ans << '\n';
}
